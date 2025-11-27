# Guia de Instalação do Aplicativo

Este guia fornece instruções para instalação, execução e configuração do app de comunicação com o osciloscópio.

---

## 1. Requisitos

- Sistema operacional: Windows / Linux / macOS
- Dependências:
  - Python 3.x (ou linguagem usada no app)
  - Bibliotecas listadas em `requirements.txt`
- Porta de comunicação:
  - USB/Serial/Bluetooth conforme configuração

---

## 2. Instalação

### **1. Clone o repositório**

```bash
git clone https://github.com/seu-repositorio/osciloscopio.git
cd osciloscopio/app
```

### **2. Instale as dependências**

```bash
pip install -r requirements.txt
```

Ou equivalente para sua plataforma.

### **3. Execução**

Para iniciar o aplicativo:

```bash
python app.py
```

O app abrirá a interface gráfica automaticamente.

### **4. Seleção da Porta de Comunicação**

- Abra o menu de configurações.

- Selecione a porta onde o microcontrolador está conectado.

- Defina a taxa de transmissão conforme o firmware (por exemplo: 115200 baud).

- Clique em Conectar.

### **5. Testando a Comunicação**

Após conectar:

- O app exibirá mensagens de status.

- Caso dados estejam chegando corretamente, a forma de onda aparecerá na tela.

- Há um modo "simulação" para testar sem hardware.

### **6. Problemas Comuns**

| Problema                 | Solução                            |
| ------------------------ | ---------------------------------- |
| Não aparece porta serial | Reinstale driver USB–Serial        |
| Forma de onda travando   | Reduza taxa de atualização gráfica |
| Perda de pacotes         | Confirme baud rate no firmware/app |

### **7. Conclusão**

Após concluir a instalação, o app está pronto para uso com o hardware integrado.
Para mais informações consulte o relatório de integração ou os documentos de arquitetura.
---
