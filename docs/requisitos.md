# Relatório de Requisitos – Osciloscópio Portátil

## Funcionalidades – Categorizadas
### Hardware
- Microcontrolador principal com ADC de alta taxa de amostragem.
- Bateria recarregável com carregamento via USB.
- Tela touch para visualização de sinais.
- Circuito de condicionamento de sinal.
- Porta de comunicação (USB/serial/wireless).

### Software
- Firmware para aquisição e processamento de sinais.
- Visualização de formas de onda na tela.
- Comunicação com aplicativo no PC.
- Funções básicas: ajuste de escala, trigger, tempo/div.

### Comunicação
- Definição de protocolo de comunicação entre as placas.
- Troca de dados entre osciloscópio e PC.
- Medição e monitoramento de bateria via firmware.

### Case
- Estrutura portátil e robusta.
- Proteção contra impactos leves.
- Facilidade de manuseio.

## Restrições
- Baixo custo de desenvolvimento.
- Autonomia mínima de bateria.
- Compatibilidade entre módulos.
- Tempo de resposta adequado para análise de sinais.

## Pesquisa e Integração
- Avaliação de microcontroladores (STM32, ESP32, etc.).
- Protocolos de comunicação (USB, UART, Wi-Fi, Bluetooth).
- Touch screens compatíveis com microcontroladores.
- Baterias Li-ion/LiPo e circuitos de carregamento.

## Justificativas de Escolhas
- Microcontrolador STM32 (potência de processamento + ADC rápido).
- Touchscreen resistivo ou capacitivo (interface intuitiva).
- Carregamento USB tipo C (facilidade e padrão atual).
- Bateria LiPo (alta densidade energética e compacta).

## Orçamento Preliminar
- Microcontrolador: ~R$ ?
- Touchscreen: ~R$ ?  
- Bateria LiPo: ~R$ ? 
- Circuito de carregamento USB: ~R$ ? 
- Componentes diversos: ~R$ ? 
**Total estimado:** ~R$ ?  

## Consumo Energético (inicial)
- Microcontrolador: ~100 mA  
- Tela Touch: ~150 mA  
- Outros periféricos: ~50 mA  
**Consumo total estimado:** ~300 mA @ 5V → autonomia prevista ~6 h com bateria 2000 mAh.
