/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file : touchscreen_k64f.c
 * @brief : Adaptação da biblioteca SPFD5408_TouchScreen para FRDM-K64F
 * Usa KSDK para GPIO e ADC. Integre ao main.c chamando get_touch_point().
 * @note : VERSÃO CORRIGIDA - Pausa e restaura o ADC1 (DMA) do osciloscópio.
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "touchscreen_k64f.h"
#include "fsl_adc16.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/* Private defines ----------------------------------------------------------*/
#define NUMSAMPLES 2 // Oversampling (2 = double-sampling, valid se iguais)

// ==========================================================
// CORRIGIDO: Canal do ADC1 usado pelo osciloscópio (main.c)
// Deve ser o mesmo que ADC_USER_CHANNEL em main.c
// ==========================================================
#define OSC_ADC_CHANNEL 6U

static gpio_pin_config_t output_config = { kGPIO_DigitalOutput, 0 };
static gpio_pin_config_t input_config = { kGPIO_DigitalInput, 0 };

#define RXPLATE 300U // Resistência de pull-up

/**
 * @brief Altera a resolução do ADC de forma otimizada via manipulação direta de registrador.
 * @param base Ponteiro para a base do periférico ADC (ADC0 ou ADC1).
 * @param resolution A resolução desejada, usando as enumerações do KSDK.
 */
static inline void ADC16_SetResolution_Fast(ADC_Type *base, adc16_resolution_t resolution)
{
    // 1. Lê o valor atual do registrador de configuração 1.
    uint32_t config = base->CFG1;

    // 2. Limpa apenas os bits do campo MODE (bits 2 e 3) usando uma máscara.
    // ADC_CFG1_MODE_MASK é definido no SDK como (3U << 2U)
    config &= ~ADC_CFG1_MODE_MASK;

    // 3. Define os novos bits de resolução no valor lido.
    // O valor de 'resolution' corresponde diretamente ao valor do campo MODE.
    config |= ADC_CFG1_MODE(resolution);

    // 4. Escreve o novo valor de volta ao registrador.
    base->CFG1 = config;
}

/* Função auxiliar: Lê ADC (escala para 0-1023 como analogRead) */
// =================================================================
// FUNÇÃO CRÍTICA CORRIGIDA
// "Pausa" e "Restaura" o ADC1 se ele estiver em uso pelo DMA
// =================================================================
static int16_t adc_read(ADC_Type *base, uint32_t channel) {

    // 1. Configura a resolução desejada (10 bits para tudo)
    ADC16_SetResolution_Fast(base, kADC16_ResolutionSE10Bit);

    adc16_channel_config_t adc_channel_config = {
        .channelNumber = channel,
        .enableInterruptOnConversionCompleted = false,
        .enableDifferentialConversion = false
    };

    // --- Seção de Pausa (início) ---
    if (base == ADC1) {
        // Proteção contra a race condition da ISR do DMA
        DisableIRQ(DMA0_IRQn);

        // 2. PAUSE o DMA e o modo contínuo
        ADC16_EnableDMA(base, false);
        base->SC3 &= ~ADC_SC3_ADCO_MASK; // Desabilita modo contínuo
    }

    // 3. Realize a leitura do touch (para ADC0 ou ADC1)
    ADC16_SetChannelConfig(base, 0, &adc_channel_config);
    while (!(ADC16_GetChannelStatusFlags(base, 0) & kADC16_ChannelConversionDoneFlag)) {}
    int16_t result = (int16_t)ADC16_GetChannelConversionValue(base, 0);

    // ==========================================================
    // CORREÇÃO CRÍTICA DE ORDEM
    // --- Seção de Retomada (início) ---
    // ==========================================================
    if (base == ADC1) {

        // 4. Reative o modo contínuo e o DMA *ANTES* de setar o canal
        base->SC3 |= ADC_SC3_ADCO_MASK; // Reativa modo contínuo
        ADC16_EnableDMA(base, true);

        // 5. Reconfigure o canal para o OSCILOSCÓPIO (Canal 6)
        // ESTA CHAMADA AGORA ATUA COMO O "TRIGGER" DE SOFTWARE
        // PARA REINICIAR A CADEIA DE CONVERSÃO CONTÍNUA.
        adc_channel_config.channelNumber = OSC_ADC_CHANNEL;
        ADC16_SetChannelConfig(base, 0, &adc_channel_config);

        // 6. Libere a ISR do DMA
        EnableIRQ(DMA0_IRQn);
    }

    return result;
}

/* Insert sort para oversampling >2 */
#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size) {
    uint8_t j;
    int save;

    for (int i = 1; i < size; i++) {
        save = array[i];
        for (j = i; j >= 1 && save < array[j - 1]; j--) {
            array[j] = array[j - 1];
        }
        array[j] = save;
    }
}
#endif

/* Equivalente a TouchScreen::getPoint() - VERSÃO CORRIGIDA */
TSPoint get_touch_point(void)
{
    int x, y, z;
    int samples[NUMSAMPLES];
    uint8_t valid = 1;

    // Configurações de pino reutilizáveis
    gpio_pin_config_t output_config = {kGPIO_DigitalOutput, 0U};
    gpio_pin_config_t input_config = {kGPIO_DigitalInput, 0U};

    /*
     =================================================
     * 1) Leitura da Coordenada X
     * Lógica:
     * - XP: Output, HIGH
     * - XM: Output, LOW
     * - YP: Analog Input (para leitura)
     * - YM: Input (alta impedância)
     =================================================
    */
    // Configura YP como entrada analógica para a leitura
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_PinDisabledOrAnalog);

    // Configura YM como GPIO de entrada (alta impedância)
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YM_GPIO, YM_PIN, &input_config);

    // Configura XP e XM como saídas para criar o gradiente de tensão
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinWrite(XP_GPIO, XP_PIN, 1); // XP em HIGH

    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinWrite(XM_GPIO, XM_PIN, 0); // XM em LOW

    // Realiza a amostragem (Usa ADC0)
    for (uint8_t i = 0; i < NUMSAMPLES; i++) {
        samples[i] = adc_read(ADC0, YP_ADC_CHAN);
    }

#if NUMSAMPLES > 2
    insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
    // A lógica de validação original não foi implementada, vamos adicionar
    if (abs(samples[0] - samples[1]) > 10) { valid = 0; }
#endif
    x = 1023 - samples[NUMSAMPLES / 2];

    /*
     =================================================
     * 2) Leitura da Coordenada Y
     * Lógica:
     * - YP: Output, HIGH
     * - YM: Output, LOW
     * - XM: Analog Input (para leitura)
     * - XP: Input (alta impedância)
     =================================================
    */
    // Configura XM como entrada analógica para a leitura
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_PinDisabledOrAnalog);

    // Configura XP como GPIO de entrada (alta impedância)
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &input_config);

    // Configura YP e YM como saídas
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinWrite(YP_GPIO, YP_PIN, 1); // YP em HIGH

    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);
    GPIO_PinWrite(YM_GPIO, YM_PIN, 0); // YM em LOW

    // Realiza a amostragem (Usa ADC1, vai pausar/retomar o DMA)
    for (uint8_t i = 0; i < NUMSAMPLES; i++) {
        samples[i] = adc_read(ADC1, XM_ADC_CHAN);
    }

#if NUMSAMPLES > 2
    insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
    if (abs(samples[0] - samples[1]) > 10) { valid = 0; }
#endif
    y = 1023 - samples[NUMSAMPLES / 2];

    /*
     =================================================
     * 3) Leitura de Z (Pressão)
     * Lógica:
     * - XP: Output, LOW
     * - YM: Output, HIGH
     * - YP: Analog Input
     * - XM: Analog Input
     =================================================
    */
    // Configura XP como OUTPUT LOW
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinWrite(XP_GPIO, XP_PIN, 0);

    // Configura YM como OUTPUT HIGH
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);
    GPIO_PinWrite(YM_GPIO, YM_PIN, 1);

    // Configura YP e XM como entradas analógicas para medir a diferença de tensão
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_PinDisabledOrAnalog);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_PinDisabledOrAnalog);

    // Usa ADC1 (pausa/retoma) e ADC0
    int z1 = adc_read(ADC1, XM_ADC_CHAN);
    int z2 = adc_read(ADC0, YP_ADC_CHAN);

    if (RXPLATE != 0) {
        float rtouch = z2;
        rtouch /= z1;
        rtouch -= 1;
        rtouch *= x;
        rtouch *= RXPLATE;
        rtouch /= 1024;
        z = (int16_t)rtouch;
        z = abs(1023 - z);
    } else {
        z = 1023 - abs((z2 - z1));
    }

    // Se qualquer uma das leituras (X ou Y) foi instável, a pressão é 0
    if (!valid) {
        z = 0;
        x = 0;
        y = 0;
    }

    /* === Restaura os pinos do LCD para o estado de saída padrão === */
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);

    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);

    // A biblioteca original inverte a coordenada Y

    x = x * 320 / 1023;
    y = y * 240 / 1023;
    //z = z * 100 / 1023;

    TSPoint p = {x, y, z};

    return p;
}
/* Equivalente a TouchScreen::readTouchX() */
int read_touch_x(void) {
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &input_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &input_config);
    GPIO_PinWrite(YP_GPIO, YP_PIN, 0);
    GPIO_PinWrite(YM_GPIO, YM_PIN, 0);

    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinWrite(XP_GPIO, XP_PIN, 1);
    GPIO_PinWrite(XM_GPIO, XM_PIN, 0);

    int x = (1023 - adc_read(ADC0, YP_ADC_CHAN));

    // Restore pins
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);

    return x;
}

/* Equivalente a TouchScreen::readTouchY() */
int read_touch_y(void) {
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &input_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &input_config);
    GPIO_PinWrite(XP_GPIO, XP_PIN, 0);
    GPIO_PinWrite(XM_GPIO, XM_PIN, 0);

    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);
    GPIO_PinWrite(YP_GPIO, YP_PIN, 1);
    GPIO_PinWrite(YM_GPIO, YM_PIN, 0);

    int y = (1023 - adc_read(ADC1, XM_ADC_CHAN));

    // Restore pins
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);

    return y;
}

/* Equivalente a TouchScreen::pressure() */
uint16_t get_pressure(void) {
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinWrite(XP_GPIO, XP_PIN, 0);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);
    GPIO_PinWrite(YM_GPIO, YM_PIN, 1);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_PinDisabledOrAnalog);
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_PinDisabledOrAnalog);
    GPIO_PinInit(XM_GPIO, XM_PIN, &input_config);
    GPIO_PinInit(YP_GPIO, YP_PIN, &input_config);

    int z1 = adc_read(ADC1, XM_ADC_CHAN);
    int z2 = adc_read(ADC0, YP_ADC_CHAN);

    // Restore pins
    PORT_SetPinMux(YP_PORT, YP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XM_PORT, XM_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(XP_PORT, XP_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(YM_PORT, YM_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(YP_GPIO, YP_PIN, &output_config);
    GPIO_PinInit(XM_GPIO, XM_PIN, &output_config);
    GPIO_PinInit(XP_GPIO, XP_PIN, &output_config);
    GPIO_PinInit(YM_GPIO, YM_PIN, &output_config);

    if (RXPLATE != 0) {
        float rtouch = z2;
        rtouch /= z1;
        rtouch -= 1;
        rtouch *= read_touch_x();
        rtouch *= RXPLATE;
        rtouch /= 1024;
        return (uint16_t)rtouch;
    } else {
        return (uint16_t)(1023 - (z2 - z1));
    }
}

/* Inicialização (chame no KSDK_GPIO_Init() após clocks) */
// ==========================================================
// CORRIGIDO: Inicializa APENAS o ADC0
// ==========================================================
void touchscreen_init(void) {
    adc16_config_t adc_config;
    ADC16_GetDefaultConfig(&adc_config);
    adc_config.clockSource = kADC16_ClockSourceAlt0;
    adc_config.clockDivider = kADC16_ClockDivider4;     // MÁXIMA VELOCIDADE
    adc_config.resolution = kADC16_ResolutionSE10Bit;
    adc_config.enableHighSpeed = true;                 // CRÍTICO
    adc_config.enableLowPower = false;
    adc_config.longSampleMode = kADC16_LongSampleDisabled;

    // Configura APENAS o ADC0, que é exclusivo do touch.
    ADC16_Init(ADC0, &adc_config);
    ADC16_EnableHardwareTrigger(ADC0, false);

    // NÃO INICIALIZE O ADC1 AQUI. O main.c é o "dono" do ADC1.
    // ADC16_Init(ADC1, &adc_config);
    // ADC16_EnableHardwareTrigger(ADC1, false);
}
