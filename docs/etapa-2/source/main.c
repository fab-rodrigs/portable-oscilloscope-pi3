/**
 ******************************************************************************
 * @file    : main.c
 * @brief   : Programa principal para o osciloscópio de toque na FRDM-K64F.
 * @version : 2.5 (Final - Integrado com Ferramentas MCUXpresso)
 * @note    : Utiliza a inicialização do ADC gerada pela ferramenta em peripherals.c,
 * adiciona a calibração no main() e remove funções redundantes.
 * Configurado para 16 bits de resolução.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adc16.h"

#include "lvgl.h"
#include "tft.h"
#include "touchscreen_k64f.h"
#include "user_setting.h"

/* Definições ----------------------------------------------------------------*/
// As macros do ADC (ADC1_PERIPHERAL, etc.) são providas por "peripherals.h"
#define ADC_CHANNEL_GROUP 0U
#define ADC_USER_CHANNEL  6U // PTC10 é ADC1_SE6b

#define OSC_GRID_HDIV_COUNT 8
#define OSC_GRID_VDIV_COUNT 10
#define OSC_X_POINT_COUNT 100

typedef struct {
    lv_coord_t min;
    lv_coord_t max;
} scale_setting_t;

static const scale_setting_t scales[] = {
    {-120, 120}, {-240, 240}, { -60,  60}
};
#define NUM_SCALES (sizeof(scales) / sizeof(scale_setting_t))


/* Protótipos ---------------------------------------------------------------*/
void KSDK_GPIO_Init(void);
static void Delay_ms(uint32_t ms);
void UI_Create(void);
void LCD_SetWriteDir(void);
static void scale_button_event_handler(lv_event_t * e);
static void touchpad_read_cb(lv_indev_drv_t * drv, lv_indev_data_t * data);
long map(long x, long in_min, long in_max, long out_min, long out_max);


/* Variáveis Globais ---------------------------------------------------------*/
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[320 * 48];
static lv_color_t buf2[320 * 48];
static lv_disp_drv_t disp_drv;

lv_obj_t *chart;
lv_chart_series_t *ser;
lv_obj_t *info_label;
static int current_scale_index = 0;
lv_obj_t *scale_button_label;
static adc16_channel_config_t adc16ChannelConfig;


/* Funções Auxiliares ------------------------------------------------------*/
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void Delay_ms(uint32_t ms) { SDK_DelayAtLeastUs(ms * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); }

void LCD_SetWriteDir(void)
{
    gpio_pin_config_t output_config = {kGPIO_DigitalOutput, 0U};
    GPIO_PinInit(D0_GPIO, D0_PIN, &output_config); GPIO_PinInit(D1_GPIO, D1_PIN, &output_config);
    GPIO_PinInit(D2_GPIO, D2_PIN, &output_config); GPIO_PinInit(D3_GPIO, D3_PIN, &output_config);
    GPIO_PinInit(D4_GPIO, D4_PIN, &output_config); GPIO_PinInit(D5_GPIO, D5_PIN, &output_config);
    GPIO_PinInit(D6_GPIO, D6_PIN, &output_config); GPIO_PinInit(D7_GPIO, D7_PIN, &output_config);
}


/* Funções de Interface e Callbacks ----------------------------------------*/
static void touchpad_read_cb(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    const int X_MIN_HW = 40;  const int X_MAX_HW = 289;
    const int Y_MIN_HW = 55;  const int Y_MAX_HW = 222;
    TSPoint p = get_touch_point();
    LCD_SetWriteDir();
    if (p.z > 10) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = map(p.x, X_MIN_HW, X_MAX_HW, 0, 319);
        data->point.y = map(p.y, Y_MAX_HW, Y_MIN_HW, 0, 239);
        if(data->point.x < 0) data->point.x = 0; if(data->point.x > 319) data->point.x = 319;
        if(data->point.y < 0) data->point.y = 0; if(data->point.y > 239) data->point.y = 239;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

static void scale_button_event_handler(lv_event_t * e)
{
    current_scale_index = (current_scale_index + 1) % NUM_SCALES;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, scales[current_scale_index].min, scales[current_scale_index].max);
    char btn_text[20];
    sprintf(btn_text, "Scale\n+/- %d", scales[current_scale_index].max);
    lv_label_set_text(scale_button_label, btn_text);
}

void UI_Create(void)
{
    chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, 250, 180);
    lv_obj_align(chart, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, scales[0].min, scales[0].max);
    lv_chart_set_point_count(chart, OSC_X_POINT_COUNT);
    lv_chart_set_div_line_count(chart, OSC_GRID_HDIV_COUNT, OSC_GRID_VDIV_COUNT);
    ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_line_width(chart, 2, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(chart, lv_color_hex(0x1E1E1E), 0);
    lv_obj_t *scale_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(scale_btn, 50, 40);
    lv_obj_align(scale_btn, LV_ALIGN_TOP_LEFT, 5, 10);
    lv_obj_add_event_cb(scale_btn, scale_button_event_handler, LV_EVENT_CLICKED, NULL);
    scale_button_label = lv_label_create(scale_btn);
    char btn_text[20];
    sprintf(btn_text, "Scale\n+/- %d", scales[0].max);
    lv_label_set_text(scale_button_label, btn_text);
    lv_obj_center(scale_button_label);
    info_label = lv_label_create(lv_scr_act());
    lv_obj_set_width(info_label, 320);
    lv_obj_align(info_label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_align(info_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(info_label, lv_color_white(), 0);
    lv_label_set_text(info_label, "Iniciando...");
}

/* Inicialização de Hardware ------------------------------------------------*/
void KSDK_GPIO_Init(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); CLOCK_EnableClock(kCLOCK_PortB); CLOCK_EnableClock(kCLOCK_PortC);
    gpio_pin_config_t output_config = {kGPIO_DigitalOutput, 0U};
    PORT_SetPinMux(PORTC, RESET_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTB, RD_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, WR_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTB, CD_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, CS_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(RESET_GPIO, RESET_PIN, &output_config); GPIO_PinInit(RD_GPIO, RD_PIN, &output_config);
    GPIO_PinInit(WR_GPIO, WR_PIN, &output_config); GPIO_PinInit(CD_GPIO, CD_PIN, &output_config);
    GPIO_PinInit(CS_GPIO, CS_PIN, &output_config);
    PORT_SetPinMux(PORTC, D0_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTC, D1_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, D2_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTA, D3_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, D4_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTA, D5_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, D6_PIN, kPORT_MuxAsGpio); PORT_SetPinMux(PORTC, D7_PIN, kPORT_MuxAsGpio);
    LCD_SetWriteDir();
    GPIO_PinWrite(CS_GPIO, CS_PIN, 1); GPIO_PinWrite(WR_GPIO, WR_PIN, 1); GPIO_PinWrite(RD_GPIO, RD_PIN, 1);
    GPIO_PinWrite(CD_GPIO, CD_PIN, 1); GPIO_PinWrite(RESET_GPIO, RESET_PIN, 1);
}

/* Função Principal --------------------------------------------------------*/
int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    // KSDK_GPIO_Init pode ser parcialmente redundante se os pinos do LCD já foram
    // configurados em BOARD_InitBootPins. Verifique se ainda é necessário.
    KSDK_GPIO_Init();

    // --- Passos adicionais para o ADC após a inicialização automática ---
    // 1. Realiza a autocalibração para maior precisão.
    ADC16_DoAutoCalibration(ADC1_PERIPHERAL);

    // 2. Prepara a estrutura de configuração do canal para uso no loop.
    adc16ChannelConfig.channelNumber = ADC_USER_CHANNEL;
    adc16ChannelConfig.enableInterruptOnConversionCompleted = false;
    adc16ChannelConfig.enableDifferentialConversion = false;
    // --------------------------------------------------------------------

    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, 320 * 48);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;
    disp_drv.flush_cb = tft_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read_cb;
    lv_indev_drv_register(&indev_drv);

    Display_init(3);
    touchscreen_init();
    Delay_ms(100);

    UI_Create();

    char info_text[50];
    uint32_t adcValue = 0;

    while (1)
    {
        const uint32_t loop_delay_ms = 1;

        // --- Altera resolução para 16 Bits ---
        adc16_config_t adc_touch_config;
        ADC16_GetDefaultConfig(&adc_touch_config);
        adc_touch_config.resolution = kADC16_ResolutionSE16Bit;
        ADC16_Init(ADC1, &adc_touch_config);
        ADC16_EnableHardwareTrigger(ADC1, false);
        // --- Leitura do ADC ---
        ADC16_SetChannelConfig(ADC1_PERIPHERAL, ADC_CHANNEL_GROUP, &adc16ChannelConfig);

        while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC1_PERIPHERAL, ADC_CHANNEL_GROUP)))
        {
        }

        adcValue = ADC16_GetChannelConversionValue(ADC1_PERIPHERAL, ADC_CHANNEL_GROUP);
        //adcValue+=16384;

        // Mapeia o valor (0-65535) para a escala do gráfico
        int16_t chart_value = map(adcValue, 0, 65535, scales[current_scale_index].min, scales[current_scale_index].max);
        lv_chart_set_next_value(chart, ser, chart_value);
        lv_chart_refresh(chart);

        sprintf(info_text, "ADC A5 (PTC10): %lu", adcValue);
        lv_label_set_text(info_label, info_text);

        // --- Gerenciador da LVGL ---
        lv_task_handler();
        lv_tick_inc(loop_delay_ms);
        //Delay_ms(loop_delay_ms);
    }
}
