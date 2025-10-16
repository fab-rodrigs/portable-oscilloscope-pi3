# Relatório Técnico do Firmware: Osciloscópio Digital com LVGL na FRDM-K64F

**Versão:** 1.0
**Data:** 16 de outubro de 2025

---

## 1. Resumo

Este documento detalha a arquitetura e a implementação final do firmware para um protótipo de osciloscópio digital na plataforma NXP FRDM-K64F. O sistema utiliza um display TFT com interface paralela, um touchscreen resistivo e a biblioteca gráfica LVGL para renderizar a interface do usuário. O firmware realiza a aquisição contínua de um sinal analógico via ADC com resolução de 16 bits e, simultaneamente, gerencia a entrada do usuário através do touchscreen, que requer leituras do ADC com resolução de 10 bits. A implementação final alcançou a integração funcional de todos os componentes, mas revelou um significativo gargalo de performance relacionado à reconfiguração dinâmica do periférico ADC.

---

## 2. Ambiente de Desenvolvimento

### 2.1. Hardware
* **Placa de Desenvolvimento:** NXP FRDM-K64F (MK64FN1M0VLL12)
* **Display:** TFT LCD 320x240 pixels com controlador ILI9341 e interface paralela de 8 bits.
* **Touchscreen:** Painel de toque resistivo de 4 fios.
* **Sinal de Entrada (Osciloscópio):** Pino `PTC10` (ADC1_SE6b).

### 2.2. Software
* **IDE:** NXP MCUXpresso IDE
* **SDK:** MCUXpresso SDK para a FRDM-K64F
* **Linguagem:** C
* **Biblioteca Gráfica:** LVGL v8.x

---

## 3. Arquitetura e Detalhes de Implementação

### 3.1. Driver do Display TFT
A comunicação com o display é realizada via "bit-banging" otimizado, utilizando acesso direto aos registradores de hardware (`PSOR` e `PCOR`) para manipular os pinos de dados distribuídos entre os PORTs A, B e C, garantindo a máxima velocidade de transferência possível sem um barramento externo.

### 3.2. Driver do Touchscreen
O driver lê os valores analógicos dos eixos do touchscreen, mapeia-os para as coordenadas da tela e os reporta à LVGL através do callback `touchpad_read_cb`. Este módulo depende de leituras do ADC com resolução de 10 bits para funcionar corretamente.

### 3.3. Módulo de Aquisição de Dados (ADC) e Conflito de Configuração

#### 3.3.1. Objetivo
O sistema exige a operação do ADC em dois modos distintos:
1.  **Modo Osciloscópio:** Leitura contínua do sinal de entrada no `ADC1` com **16 bits de resolução** para máxima precisão.
2.  **Modo Touchscreen:** Leituras intermitentes nos `ADC0` e `ADC1` com **10 bits de resolução** para interpretar as coordenadas do toque.

#### 3.3.2. Implementação e Desafio
A configuração inicial do sistema, gerada via MCUXpresso Peripherals e reforçada pela calibração em `main()`, ajusta o `ADC1` para 16 bits.

No entanto, a API do KSDK fornecida para esta plataforma **não possui uma função leve** (como `ADC16_SetResolution()`) para alterar dinamicamente apenas a resolução do ADC. A única maneira de alternar a resolução é reinicializar completamente o periférico chamando a função `ADC16_Init()`.

Consequentemente, a implementação resultou no seguinte fluxo:
* O loop principal em `main.c` assume que o `ADC1` está configurado para 16 bits.
* Sempre que a LVGL solicita uma leitura de toque (`touchpad_read_cb`), a função `adc_read()` no driver do touchscreen **reinicializa forçadamente** o ADC para 10 bits para realizar sua medição.

Este método, embora funcional, cria um conflito de estado e é a principal fonte de problemas de performance no sistema.

### 3.4. Interface Gráfica e Lógica da Aplicação
A UI, construída com widgets da LVGL, exibe o gráfico do osciloscópio e os controles. A lógica do sistema foi aprimorada significativamente ao substituir os atrasos manuais (`Delay_ms`) e a chamada de `lv_tick_inc` no loop principal por uma abordagem baseada em interrupção de hardware.

* **Gerenciamento de Tempo da LVGL:** Foi configurado o **SysTick**, um timer padrão do ARM Cortex-M, para gerar uma interrupção a cada 1 milissegundo. A rotina de serviço de interrupção (`SysTick_Handler`) chama `lv_tick_inc(1)`, fornecendo à LVGL uma base de tempo precisa e confiável, independente da carga de processamento no loop principal. Isso libera o `while(1)` para focar exclusivamente na lógica da aplicação e na chamada do `lv_task_handler()`.

---

## 4. Otimizações e Desafios de Performance

### 4.1. Otimizações Bem-sucedidas
* **Double Buffering (LVGL):** A alocação de dois buffers de desenho (`buf1`, `buf2`) de `320x48` pixels permitiu que a CPU renderize a UI em um buffer enquanto o outro está sendo transferido para o display, melhorando drasticamente a fluidez.
* **Otimização do Compilador:** O projeto foi configurado para compilação com nível de otimização `-O2`, gerando um código de máquina mais rápido e eficiente.
* **Timer de Hardware (SysTick):** A migração do "tick" da LVGL para uma interrupção de hardware tornou o sistema mais responsivo e o gerenciamento de tempo mais robusto.

### 4.2. Principal Gargalo de Performance Identificado
O principal desafio que impede a alta performance do sistema é a **reinicialização contínua do ADC**. A chamada da função `ADC16_Init()` dentro do driver do touchscreen é uma operação pesada que consome um tempo de CPU significativo a cada evento de toque. Isso causa:
* **Lentidão perceptível** e falta de responsividade na interface sempre que o touchscreen é lido.
* Possibilidade de **leituras incorretas** no osciloscópio se uma interrupção ou troca de contexto ocorrer no momento errado, embora o risco seja minimizado pela natureza síncrona do loop.

---

## 5. Conclusão e Próximos Passos

O firmware integra com sucesso todos os componentes de hardware e software, validando a arquitetura geral. As otimizações de buffer e do tick da LVGL foram eficazes, mas a performance final do sistema é severamente limitada pela necessidade de reconfigurar o ADC em tempo de execução, devido a uma limitação da API do SDK.

As seguintes ações são recomendadas para futuras versões:

1.  **Otimizar a Reconfiguração do ADC:** A prioridade máxima é encontrar uma alternativa à chamada de `ADC16_Init()`. As opções incluem:
    * **Manipulação Direta de Registradores:** Analisar o datasheet do microcontrolador para identificar os registradores específicos que controlam a resolução do ADC e modificá-los diretamente, contornando a API do SDK.
    * **Verificação de SDKs Alternativos:** Investigar se versões mais recentes ou diferentes do SDK para o K64F oferecem uma API mais flexível para o ADC.

2.  **Migrar Driver do Display para FlexBus:** Para ganhos de performance na renderização gráfica, substituir o driver de "bit-banging" por uma implementação que utilize o periférico de barramento externo **FlexBus**.

3.  **Implementar Funcionalidades de Osciloscópio:** Adicionar lógicas de trigger, cursores de medição e cálculos de parâmetros de sinal (Vpp, frequência, etc.).
