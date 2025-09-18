# Diagrama de Blocos – Osciloscópio Portátil

```mermaid
flowchart LR
    A[Sinal de Entrada] --> B[Condicionamento de Sinal]
    B --> C[ADC - Microcontrolador]
    C --> D[Firmware de Processamento]
    D --> E[Tela Touchscreen]
    D --> F[Comunicação com PC]
    G[Bateria] --> H[Circuito de Carregamento USB]
    H --> I[Alimentação do Sistema]
    I --> B
    I --> C
    I --> E
