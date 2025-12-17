# Documentação Técnica do Osciloscópio Portátil

## Introdução

Este documento descreve as especificações técnicas e o funcionamento de um osciloscópio portátil projetado para medições de sinais elétricos de forma compacta e autônoma. O dispositivo é alimentado por bateria recarregável e integra um microcontrolador **FRDM-K64F** para processamento de sinais. Ele possui um display **TFT LCD** com touch screen para visualização e interação, além de capacidade de envio de dados via serial para um software complementar em um computador conectado.

O osciloscópio é ideal para aplicações educacionais, de prototipagem e de campo, onde a portabilidade é essencial. Ele suporta condicionamento de sinal analógico, amostragem via ADC e exibição de métricas chave do sinal.

---

## Especificações Técnicas

### Hardware Principal

- **Microcontrolador:** FRDM-K64F (baseado em ARM Cortex-M4).  
- **Display:** TFT LCD de 2.4 polegadas com touch screen para interface de usuário.  
- **Alimentação:** Bateria recarregável de **4.2 V**, com carregamento via porta **micro-USB** localizada na parte superior do dispositivo.  
- **Indicador de Bateria:** Percentual de nível de bateria exibido na tela, medido através de um canal ADC.  
- **Entrada de Sinal:** Placa analógica dedicada para condicionamento do sinal antes da entrada no ADC do microcontrolador.

### Amostragem

- **Taxa de amostragem:** **350 kHz**.  
- **Configuração:** definida via **PIT (Periodic Interrupt Timer)** que aciona o ADC integrado ao **DMA (Direct Memory Access)**.  
- **Buffer de memória:** **1000 amostras**, operando em modo **ping-pong** para captura contínua de dados.

### Saída de Dados

- Envio de dados brutos capturados pelo ADC via comunicação serial (USB/serial) para um computador conectado.

---

## Limitações de Sinal de Entrada

- **Frequência Máxima:** 100 kHz.  
- **Tensão DC:** máxima de **+30 V**, mínima de **−30 V**.  
- **Tensão AC:** máxima de **+15 V**, mínima de **−16 V**.

Essas limitações garantem a integridade do hardware e a precisão das medições, evitando sobrecarga no circuito de condicionamento ou no ADC.

---

## Controles e Chaves

O dispositivo possui **4 chaves físicas** para configuração e operação:

### Chave ON/OFF
- Localizada na parte superior das outras chaves, posicionada deitada.  
- **Esquerda:** Liga o dispositivo.  
- **Direita:** Desliga o dispositivo.

### Chave Superior (Atenuação de Divisão)
- Configura a atenuação para adequação do sinal ao ADC (limitação de hardware).  
- **Para cima:** Atenuação de **5**.  
- **Para baixo:** Atenuação de **2**.

### Chave do Meio (Atenuação de Escala)
- Permite trabalhar com tensões maiores ou menores.  
- **Para cima:** Atenuação de **10x** (recomendada para tensões > 3 V ou < −3 V).  
- **Para baixo:** Atenuação de **1x**.

### Chave Inferior (Acoplamento)
- Seleciona o modo de acoplamento do sinal.  
- **Para cima:** **AC** (Alternada).  
- **Para baixo:** **DC** (Contínua).

Essas chaves permitem ao usuário adaptar o dispositivo a diferentes tipos de sinais sem necessidade de configurações digitais complexas.

---

## Funcionalidades

### Captura e Processamento de Sinal

- O sinal de entrada é condicionado pela placa analógica para se adequar à faixa de operação do ADC.  
- O **DMA** gerencia a transferência de dados para o buffer de **1000 amostras** em modo ping-pong, permitindo captura contínua sem perda de dados.  
- A taxa de amostragem de **350 kHz** é fixa e controlada pelo **PIT**.

### Exibição no Display

O display TFT LCD de 2.4" com touch screen exibe:

- Forma de onda do sinal capturado.  
- Métricas do sinal:
  - **Tensão pico a pico (Vpp)**.  
  - **Tensão média (Vavg)**.  
  - **Tensão RMS (Vrms)**.  
  - **Frequência do sinal (Hz)**.  
- Configurações atuais:
  - Atenuação de divisão (2 ou 5).  
  - Atenuação de escala (1x ou 10x).  
- Indicador percentual de bateria.

O touch screen permite interações básicas, como navegação em menus ou ajustes finos (se implementados no firmware).

### Integração com Software Externo

- **Envio de Dados:** Dados brutos do ADC são enviados via serial para um computador conectado ao microcontrolador.  
- **Software Complementar (no computador):**
  - Replica a imagem do osciloscópio (forma de onda e métricas).  
  - Realiza cálculos mais complexos (ex.: análises avançadas de sinal, transformadas, etc.).  
  - Permite salvar os dados capturados em arquivos para análise posterior.

---

## Arquitetura do Sistema

### Fluxo de Dados

1. Sinal de entrada é recebido e condicionado pela placa analógica.  
2. Chaves seletoras ajustam atenuação e acoplamento.  
3. PIT aciona o ADC via DMA para amostragem a **350 kHz**.  
4. Dados são armazenados no buffer ping-pong de **1000 amostras**.  
5. Processamento local no **FRDM-K64F** para exibição no display (métricas básicas).  
6. Envio serial de dados brutos para software no PC para processamento avançado e salvamento.

---

## Considerações de Uso e Manutenção

- **Carregamento:** Use a porta micro-USB para recarregar a bateria de 4.2 V. Monitore o indicador de bateria para evitar desligamentos inesperados.  
- **Segurança:** Respeite as limitações de tensão e frequência para evitar danos ao hardware. Sempre configure as chaves de atenuação apropriadamente antes de aplicar sinais.  
- **Firmware e Software:** O firmware no FRDM-K64F gerencia a amostragem e exibição. O software no PC deve ser compatível com a comunicação serial (detalhes de protocolo não especificados aqui; consulte o código-fonte).  
- **Manutenção:** Verifique periodicamente a bateria e conexões. Evite exposição a umidade ou temperaturas extremas. Substitua bateria por componente equivalente aprovado quando necessário.

---

## Contribuições e Atualizações

Esta documentação pode ser atualizada conforme evoluções no projeto. Contribuições são bem-vindas via **pull requests** no repositório GitHub. Para mais detalhes sobre o código-fonte, consulte os arquivos no repositório.

---

**Última atualização:** Dezembro 2025.
