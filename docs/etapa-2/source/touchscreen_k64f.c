/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file : touchscreen_k64f.c
  * @brief : Adaptação da biblioteca SPFD5408_TouchScreen para FRDM-K64F
  *         Usa KSDK para GPIO e ADC. Integre ao main.c chamando get_touch_point().
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "touchscreen_k64f.h"
#include "fsl_adc16.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/* Private defines ----------------------------------------------------------*/
#define NUMSAMPLES 2  // Oversampling (2 = double-sampling, valid se iguais)

static gpio_pin_config_t output_config = { kGPIO_DigitalOutput, 0 };
static gpio_pin_config_t input_config = { kGPIO_DigitalInput, 0 };

#define RXPLATE 300U  // Resistência de pull-up

// In touchscreen_k64f.c

/* Função auxiliar: Lê ADC (escala para 0-1023 como analogRead) */
static int16_t adc_read(ADC_Type *base, uint32_t channel) {
    // ==========================================================
    //  SOLUÇÃO COMPATÍVEL: Reconfigura o ADC para 10 bits
    // ==========================================================
    adc16_config_t adc_touch_config;
    ADC16_GetDefaultConfig(&adc_touch_config);
    adc_touch_config.resolution = kADC16_ResolutionSE10Bit;
    ADC16_Init(base, &adc_touch_config);
    ADC16_EnableHardwareTrigger(base, false); // Garante o trigger por software

    adc16_channel_config_t adc_channel_config = {
        .channelNumber = channel,
        .enableInterruptOnConversionCompleted = false,
        .enableDifferentialConversion = false
    };

    ADC16_SetChannelConfig(base, 0, &adc_channel_config);
    while (!(ADC16_GetChannelStatusFlags(base, 0) & kADC16_ChannelConversionDoneFlag)) {}

    // O valor já estará na faixa 0-1023
    return (int16_t)ADC16_GetChannelConversionValue(base, 0);
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
    gpio_pin_config_t input_config  = {kGPIO_DigitalInput, 0U};

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

    // Realiza a amostragem
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

    // Realiza a amostragem
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
    z = z * 100 / 1023;

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
void touchscreen_init(void) {
    adc16_config_t adc_config;
    ADC16_GetDefaultConfig(&adc_config);
    adc_config.resolution = kADC16_ResolutionSE10Bit; // Use single-ended 10-bit
    ADC16_Init(ADC0, &adc_config);
    ADC16_EnableHardwareTrigger(ADC0, false);
    ADC16_Init(ADC1, &adc_config);
    ADC16_EnableHardwareTrigger(ADC1, false);
}
