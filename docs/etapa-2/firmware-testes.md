# Relatório Técnico do Firmware: Osciloscópio Digital com LVGL na FRDM-K64F

**Versão:** 3.0
**Data:** 16 de outubro de 2025

---

## 1. Resumo

Este documento detalha a arquitetura, implementação e otimização final do firmware para um protótipo de osciloscópio digital na plataforma NXP FRDM-K64F. O sistema integra com sucesso um display TFT com interface paralela, um touchscreen resistivo e a biblioteca gráfica LVGL para renderizar uma interface de usuário responsiva. O principal desafio técnico do projeto, gerenciar a necessidade de duas resoluções de ADC distintas (16 bits para o osciloscópio e 10 bits para o touchscreen), foi solucionado através da **manipulação direta de registradores de hardware**. Esta abordagem contornou as limitações da API do SDK e eliminou um gargalo crítico de performance. O firmware resultante é funcional, eficiente e serve como uma base robusta para futuras expansões.

---

## 2. Ambiente de Desenvolvimento

### 2.1. Hardware
* **Placa de Desenvolvimento:** NXP FRDM-K64F (MK64FN1M0VLL12)
* **Display:** TFT LCD 320x240 pixels com controlador ILI9341 e interface paralela de 8 bits
* **Touchscreen:** Painel de toque resistivo de 4 fios
* **Sinal de Entrada (Osciloscópio):** Pino `PTC10` (ADC1_SE6b)

### 2.2. Software
* **IDE:** NXP MCUXpresso IDE
* **SDK:** MCUXpresso SDK para a FRDM-K64F
* **Linguagem:** C
* **Biblioteca Gráfica:** LVGL v8.x

---

## 3. Arquitetura e Detalhes de Implementação

### 3.1. Driver do Display TFT
A comunicação com o display é realizada via "bit-banging" otimizado. A abordagem utiliza acesso direto aos registradores de hardware (`PSOR` e `PCOR`) para manipular os pinos de dados distribuídos entre os PORTs GPIO, garantindo a máxima velocidade de transferência possível sem um barramento externo.

### 3.2. Módulo de Aquisição de Dados e Otimização de Resolução Dinâmica

#### 3.2.1. Desafio
O sistema exigia a operação do ADC em dois modos distintos: 16 bits para o osciloscópio e 10 bits para o touchscreen. A API do KSDK não oferecia uma função leve para alternar a resolução, forçando o uso da função `ADC16_Init()`, que se mostrou um gargalo de performance inaceitável ao ser chamada repetidamente.

#### 3.2.2. Solução: Manipulação Direta de Registradores
A solução foi implementar uma função `static inline`, `ADC16_SetResolution_Fast()`, no arquivo `touchscreen_k64f.c`. Esta função modifica diretamente o registrador responsável pela configuração do ADC.

* **Registrador Alvo:** `ADCx_CFG1`
* **Campo de Bits:** `MODE` (bits 2 e 3)

A função `ADC16_SetResolution_Fast` lê o valor atual do registrador, limpa apenas os bits do campo `MODE` e, em seguida, define os novos bits de acordo com a resolução desejada. Esta operação é executada em pouquíssimos ciclos de clock.

#### 3.2.3. Fluxo de Execução Coordenado
O fluxo de controle foi orquestrado para garantir que cada módulo opere com a resolução correta:
1.  **Driver do Touchscreen (`touchscreen_k64f.c`):** Antes de cada leitura de coordenada, a função `adc_read` chama `ADC16_SetResolution_Fast(base, kADC16_ResolutionSE10Bit)` para configurar o ADC para 10 bits. Imediatamente após a leitura do ADC1, a resolução é restaurada para 16 bits com a mesma função.
2.  **Loop Principal (`main.c`):** O loop `while(1)` foi limpo de qualquer código de reconfiguração do ADC. Ele agora opera sob a premissa de que o `ADC1` está sempre configurado para 16 bits, estado que é garantido pela restauração feita no driver do touchscreen.

Esta arquitetura resolveu completamente o conflito de configuração e o problema de performance.

### 3.3. Interface Gráfica e Lógica da Aplicação
A interface do usuário é renderizada pela LVGL e inclui um gráfico para a forma de onda, um rótulo para o valor ADC e um botão para alterar a escala. O gerenciamento de tempo da biblioteca é tratado de forma robusta e eficiente por uma interrupção de hardware.

* **Gerenciamento de Tempo (SysTick):** O timer SysTick do ARM Cortex-M foi configurado para gerar uma interrupção a cada 1 milissegundo. A rotina de serviço de interrupção (`SysTick_Handler`) chama `lv_tick_inc(1)`, fornecendo à LVGL uma base de tempo precisa e desacoplando-a da lógica do loop principal.

---

## 4. Otimizações de Performance Implementadas

O firmware alcançou uma performance fluida e responsiva através de um conjunto de otimizações críticas:

1.  **Resolução Dinâmica do ADC via Registradores:** A principal otimização, que eliminou a latência na interface, foi a substituição da chamada `ADC16_Init()` pela manipulação direta do registrador `ADCx_CFG1`.
2.  **Double Buffering (LVGL):** A alocação de dois buffers de desenho (`buf1`, `buf2`) de `320x48` pixels permite que a CPU renderize a UI em um buffer enquanto o outro está sendo transferido para o display, garantindo atualizações de tela sem tearing.
3.  **Timer de Hardware (SysTick):** A migração do "tick" da LVGL para uma interrupção de hardware tornou o sistema mais reativo e o gerenciamento de tempo mais confiável.
4.  **Otimização do Compilador:** O projeto foi configurado para ser compilado com nível de otimização `-O2`, gerando um código de máquina mais eficiente.

---

## 5. Instruções de Compilação e Implantação

1.  Importar o projeto no MCUXpresso IDE.
2.  Verificar se o SDK para a FRDM-K64F está corretamente associado.
3.  Assegurar que o nível de otimização do compilador está definido como `-O2` ou superior para performance ideal.
4.  Conectar a placa FRDM-K64F via USB e iniciar uma sessão de depuração para transferir o firmware.

---

## 6. Conclusão e Próximos Passos

O firmware final atinge com sucesso todos os objetivos propostos, demonstrando uma solução de engenharia eficaz para um desafio complexo de hardware em um sistema embarcado. A performance do sistema é robusta, e a arquitetura é modular e extensível.

Com o principal gargalo de performance resolvido, os próximos passos podem focar na expansão das funcionalidades do aplicativo:

* **Migrar Driver do Display para FlexBus:** Para o próximo nível de performance gráfica, substituir o driver de "bit-banging" por uma implementação que utilize o periférico de barramento externo **FlexBus**, permitindo transferências de dados via DMA e liberando a CPU.
* **Implementar Funcionalidades de Osciloscópio:** Adicionar lógicas de trigger (borda de subida/descida, nível), cursores de medição e cálculos automáticos de Vpp, Vrms e frequência do sinal.
* **Refinar a Interface do Usuário:** Adicionar menus, configurações de salvamento e mais opções de visualização utilizando os recursos da LVGL.
