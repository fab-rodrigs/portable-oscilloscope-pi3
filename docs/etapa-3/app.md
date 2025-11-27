## 📤 Como o Microcontrolador Envia os Dados (Firmware → Python)

O aplicativo em Python depende do formato de transmissão gerado pelo firmware do microcontrolador. Abaixo está a lógica utilizada para preparar e enviar os dados via UART:

### 🔧 Alinhamento do buffer

O firmware captura amostras via ADC usando DMA. Depois, alinha o buffer com base na posição do *trigger*:

```c
for (int i = 0; i < DMA_BUFFER_SIZE; i++) {
    int source_index = (trigger_index - g_trigger_x_pos + i + DMA_BUFFER_SIZE) % DMA_BUFFER_SIZE;
    aligned_buffer[i] = local_buffer[source_index];
}
```

Esse bloco:

- Reorganiza o buffer circular.
- Garante que os dados enviados comecem exatamente no ponto do trigger.
- Mantém o comportamento clássico de um osciloscópio.

---

### 📦 Conversão dos valores para texto

Para transmitir os valores por UART sem usar `sprintf` (que é lento), o código gera manualmente uma string para cada amostra:

```c
static char uart_tx_buf[16];

for (int i = 0; i < DMA_BUFFER_SIZE; i++) {
    uint16_t val = aligned_buffer[i] & 0x3FF;

    // Conversão manual para string (mais rápido que sprintf)
    char *p = uart_tx_buf + sizeof(uart_tx_buf) - 1;
    *p = '\0';
    do {
        *--p = '0' + (val % 10);
        val /= 10;
    } while (val);
    *--p = ',';

    UART_WriteBlocking(UART0, (uint8_t*)p, strlen(p));
}
```

Cada valor é enviado no formato:

```
,123
,456
,789
...
```

Ou seja:

- **Sempre começa com uma vírgula**.
- Em seguida vem o número já convertido para ASCII.
- Não tem espaço entre valores.

Esse formato reduz overhead e facilita o parsing no Python.

---

### 🔚 Finalização do frame

Ao final do envio de todas as amostras, o firmware finaliza com um `\n`:

```c
UART_WriteBlocking(UART0, (uint8_t*)"\n", 2);
```

Isso sinaliza ao aplicativo Python que um *frame completo* foi transmitido.

---

## 🔗 Ligação com o Aplicativo Python

O app em Python faz o processamento inverso dessa formatação:

```python
raw = ser.readline().decode(errors="ignore").strip()
partes = raw.split(",")[1:]
dados = [int(x) for x in partes if x.isdigit()]
```

O funcionamento é:

1. `readline()` lê até o `\n` enviado pelo microcontrolador.
2. `split(",")` divide os valores transmitidos.
3. O primeiro item é vazio (por causa da vírgula inicial), então é ignorado com `[1:]`.
4. Cada trecho é convertido para inteiro, reconstruindo o vetor de amostras ADC.

Assim, o formato:

```
,512,520,530,480,460,440,...
```

é convertido diretamente para:

```python
[512, 520, 530, 480, 460, 440, ...]
```

Sem perda de dados e com baixo custo computacional.

---

## 🧩 Resumo da Interação Firmware ↔ App

**Firmware (C)**  
→ Reorganiza as amostras pelo trigger  
→ Converte números manualmente para texto  
→ Envia formato `,valor` repetido  
→ Finaliza com `\n`

**App Python**  
→ Lê um frame completo por linha  
→ Remove a vírgula inicial  
→ Extrai os números  
→ Plota em tempo real  
→ Ajusta eixo X automaticamente  

Essa integração garante baixo atraso, alta taxa de amostragem e visualização fluida no “osciloscópio” do app.

