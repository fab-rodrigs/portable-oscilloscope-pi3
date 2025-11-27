# Código Fonte do Aplicativo

O aplicativo desenvolvido nesta etapa tem como objetivo realizar a comunicação com o osciloscópio embarcado, receber os dados provenientes do microcontrolador e apresentá-los ao usuário de forma gráfica e intuitiva.

## Funcionalidades Principais

- Comunicação com o microcontrolador (serial/USB/Bluetooth, conforme arquitetura).
- Recebimento contínuo dos pacotes de amostragem.
- Renderização em tempo real da forma de onda.
- Funções básicas de osciloscópio:
  - Ajuste de escala vertical e horizontal
  - Trigger simples
  - Pausar/continuar captura
  - Limpar buffer
- Filtros digitais opcionais.
- Interface modular para futura expansão.

## Estrutura do Código

O código foi organizado em módulos:

- `comms/` → gerenciamento da comunicação.
- `parser/` → interpretação dos pacotes recebidos.
- `oscilloscope/` → lógica de exibição e processamento.
- `ui/` → interface com o usuário.
- `utils/` → funções auxiliares.

Essa organização permite fácil manutenção e adição de novas funcionalidades.

## Execução

As instruções de instalação e execução estão no arquivo **guia-instalacao.md**.
