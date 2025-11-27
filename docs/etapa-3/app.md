# Aplicativo de Comunicação e Visualização do Osciloscópio

Este documento descreve o funcionamento do aplicativo em Python utilizado para comunicação com o microcontrolador e exibição dos dados em forma de gráfico, simulando o comportamento básico de um osciloscópio em tempo real.

O código completo do aplicativo está disponível no repositório em:

➡️ **`src/oscilloscope_app_code.py`**

---

## 📌 Objetivo do Aplicativo

O app tem como finalidade:

- Estabelecer comunicação serial com o microcontrolador.
- Ler continuamente os dados enviados pelo firmware.
- Interpretar os valores ADC recebidos da porta serial.
- Plotar os dados em tempo real usando **matplotlib**, funcionando como um osciloscópio simples.

O aplicativo foi projetado para operar em conjunto com o firmware do microcontrolador, que transmite amostras de sinal no formato:

```
,67,72,44,18,...
```

Cada linha representa um frame de dados lido pelo ADC.

---

## 🛠️ Tecnologias Utilizadas

- **Python 3**
- **PySerial** — leitura da porta serial.
- **Matplotlib** — renderização gráfica em tempo real.
- **NumPy** — manipulação eficiente de arrays.

---

## 🔌 Comunicação Serial

A conexão com o dispositivo é aberta da seguinte forma:

```python
PORTA = "COM10"
BAUD = 1000000
ser = serial.Serial(PORTA, BAUD, timeout=1)
```

- **PORTA**: depende do sistema operacional (COMx no Windows, /dev/ttyUSBx no Linux).
- **BAUD**: 1.000.000 bps, definido pelo firmware.
- **timeout**: evita travamentos caso um frame não seja recebido.

---

## 📈 Plotagem em Tempo Real

O gráfico funciona no modo *interactive* (plt.ion), permitindo atualização contínua:

```python
plt.ion()
fig, ax = plt.subplots()
linha_plot, = ax.plot([], [])
ax.set_ylim(0, 1023)      # faixa do ADC
ax.set_xlim(0, 500)
```

A aplicação assume inicialmente um máximo de 500 pontos por quadro, mas ajusta automaticamente ao receber novos tamanhos de vetor.

---

## 🔍 Processamento dos Dados

Os dados chegam no formato:

```
,67,72,44,18
```

Por isso, o código:

1. Remove a vírgula inicial.
2. Divide a string pelo separador `,`.
3. Converte cada entrada para inteiro.

```python
partes = raw.split(",")[1:]
dados = [int(x) for x in partes if x.isdigit()]
```

Somente valores numéricos válidos são plotados.

---

## 🔄 Loop Principal

O app roda continuamente até que seja interrompido pelo usuário (Ctrl+C):

```python
while True:
    raw = ser.readline().decode(errors="ignore").strip()

    if not raw:
        continue

    partes = raw.split(",")[1:]
    dados = [int(x) for x in partes if x.isdigit()]

    if len(dados) == 0:
        continue

    linha_plot.set_ydata(dados)
    linha_plot.set_xdata(np.arange(len(dados)))
    ax.set_xlim(0, len(dados))

    plt.pause(0.001)
```

Esse mecanismo permite:

- Atualização muito rápida.
- Baixa latência.
- Visualização contínua dos sinais.

---

## 🧪 Execução

Para rodar o aplicativo:

```bash
python oscilloscope_app_code.py
```

Certifique-se de:

- Ter instalado `pyserial` e `matplotlib`.
- Ajustar a porta serial no início do arquivo.

---

## 📝 Considerações Finais

Este aplicativo fornece as funcionalidades básicas de um osciloscópio digital simples:

- Leitura sequencial do ADC.
- Plotagem contínua.
- Interpretação automática dos frames.

Ele serviu como base para futuras expansões, como:

- Ferramentas de medição (amplitude, frequência, RMS).
- Modos de trigger.
- Armazenamento de sinais.
- Zoom e escala automática.

Para detalhes adicionais da arquitetura, consulte o documento:

➡️ **`docs/etapa-3/diagrama_arquitetura.md`**

