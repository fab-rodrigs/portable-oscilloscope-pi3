/**
 ******************************************************************************
 * @file : main.c
 * @brief : Osciloscópio de toque na FRDM-K64F com DMA Ping-Pong
 * @version : 8.8 (Marcador de 0V segue o Offset Vertical)
 * @note :
 * - ADC1 em 10 bits, trigger por software, modo contínuo
 * - DMA Ping-Pong via registradores (100 amostras)
 * - Touchscreen usa ADC0/ADC1 (pausando e retomando o DMA)
 * - Cálculos de Vpp, Vmed, Vrms (com formatação manual)
 * - Lógica de Trigger por Software (Modo Auto/Normal, Borda)
 *
 * - MODIFICAÇÕES DESTA VERSÃO:
 * - adc_init() corrigida (Calibra/Reconfigura).
 * - Medição de Fs (CYC) na ISR do DMA.
 * - Cálculo de Frequência (Freq) do sinal.
 * - Arrastar metade esquerda (x < 160) ajusta o offset vertical (Y Pos).
 * - Arrastar metade direita (x >= 160) ajusta o nível de trigger.
 * - O marcador de 0V (zero_level_label) agora se move com o offset.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include <stdint.h>
#include <string.h>
#include <math.h> // Para sqrt()
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adc16.h"
#include "tft.h"
#include "touchscreen_k64f.h" // Garanta que este .h foi corrigido para retornar valores raw
#include "user_setting.h"
#include "fsl_uart.h"
#include "UART0.h"

/* Definições ----------------------------------------------------------------*/
#define ADC_CHANNEL_GROUP 0U
#define ADC_USER_CHANNEL 6U // PTC10 = ADC1_SE6b
#define OSC_GRID_HDIV_COUNT 8
#define OSC_GRID_VDIV_COUNT 10
#define OSC_X_POINT_COUNT 1000
#define DMA_BUFFER_SIZE OSC_X_POINT_COUNT

// Constantes de calibração
#define V_REF 3.3 // Tensão de referência do ADC
#define ADC_MAX_COUNTS 1023.0 // 10-bit
// GPIOs de controle da sonda (PORTD)
#define CTRL_GPIO GPIOD
#define CTRL_PORT PORTD
#define AC_DC_PIN 1U // PTD1: 1=AC, 0=DC
#define ATTEN_10X_PIN 2U // PTD2: 1=10x ufficiale, 0=1x
#define DIV_2_PIN 3U // PTD3: 1=/2, 0=/5
// Escalas do gráfico (em pixels, centralizado em 0V)
typedef struct {
    lv_coord_t min;
    lv_coord_t max;
} scale_setting_t;
static const scale_setting_t scales[] = {
    {-120, 120}, // ±1V
    {-240, 240}, // ±2V (tela cheia)
    { -60, 60} // ±0.5V
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
void dma_init(void);
void adc_init(void);
void PIT_Init(int fs);
static void update_probe_state(void);
// Protótipos para handlers de trigger
static void run_stop_event_handler(lv_event_t * e);
static void menu_button_event_handler(lv_event_t * e);
static void trigger_mode_event_handler(lv_event_t * e);
static void trigger_edge_event_handler(lv_event_t * e);
static void update_trigger_menu_visibility(void);
static void chart_press_event_handler(lv_event_t * e);
static void coupling_event_handler(lv_event_t * e);
/* Variáveis Globais ---------------------------------------------------------*/
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[320 * 48];
static lv_color_t buf2[320 * 48];
static lv_disp_drv_t disp_drv;
lv_obj_t *chart;
lv_chart_series_t *ser;
lv_obj_t *info_CH1_label;
lv_obj_t *info_label;
lv_obj_t *probe_label;
lv_obj_t *freq_CH1_label;
static int current_scale_index = 0;
lv_obj_t *scale_button_label;
static adc16_channel_config_t adc16ChannelConfig;
// Buffers DMA Ping-Pong
volatile uint32_t dma_buffer_ping[DMA_BUFFER_SIZE];
volatile uint32_t dma_buffer_pong[DMA_BUFFER_SIZE];
volatile uint32_t *active_dma_buffer = dma_buffer_ping;
volatile uint32_t *ready_dma_buffer = dma_buffer_pong;
volatile bool data_ready_flag = false;
volatile bool g_is_running = true; // Inicia rodando
volatile bool data_sent = false;
// Estados reais da sonda (lidos de PTD1/2/3)
volatile bool g_is_dc_coupling = false;
volatile bool g_is_1x_atten = false;
volatile float g_divider_ratio = 5.0f;
volatile float g_total_gain = 5.0f; // 1x5, 10x5, 1x2 ou 10x2
// Configurações de Trigger
typedef enum { RISING_EDGE, FALLING_EDGE } trigger_edge_t;
typedef enum { TRIGGER_AUTO, TRIGGER_NORMAL } trigger_mode_t;
volatile trigger_mode_t g_trigger_mode = TRIGGER_AUTO;
volatile trigger_edge_t g_trigger_edge = RISING_EDGE;
volatile int32_t g_trigger_level = 0; // Nível de trigger (em contas de ADC, 0V)
const int g_trigger_x_pos = 10; // Posição X do trigger na tela (10% do início)
// Ponteiros globais para os botões e o label de nível
lv_obj_t *run_stop_btn;
lv_obj_t *run_stop_label;
lv_obj_t *menu_btn;
lv_obj_t *trig_mode_btn;
lv_obj_t *trig_edge_btn;
lv_obj_t *trigger_mode_label;
lv_obj_t *trigger_edge_label;
lv_obj_t *trigger_level_marker;
lv_obj_t *zero_level_label;
lv_obj_t *debug_coord_label;
// --- MODIFICAÇÃO: Variáveis para Medição de Fs ---
volatile uint32_t g_cycle_count = 0;
volatile uint32_t last_cyccnt = 0;
// --- MODIFICAÇÃO (v8.7): Variáveis de Offset Vertical ---
volatile int32_t g_vertical_offset = 0; // Offset em contagens ADC
static lv_coord_t drag_start_y = 0;
static int32_t offset_at_drag_start = 0;
// -----------------------------------------------------
// --- MODIFICAÇÃO: Variável de Estilo para Fonte Pequena ---
static lv_style_t style_small_font;
/* Funções Auxiliares --------------------------------------------------------*/
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    if (in_min == in_max) {
        return out_min;
    }
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
static void Delay_ms(uint32_t ms) {
    SDK_DelayAtLeastUs(ms * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}
void LCD_SetWriteDir(void) {
    gpio_pin_config_t output_config = {kGPIO_DigitalOutput, 0U};
    GPIO_PinInit(D0_GPIO, D0_PIN, &output_config); GPIO_PinInit(D1_GPIO, D1_PIN, &output_config);
    GPIO_PinInit(D2_GPIO, D2_PIN, &output_config); GPIO_PinInit(D3_GPIO, D3_PIN, &output_config);
    GPIO_PinInit(D4_GPIO, D4_PIN, &output_config); GPIO_PinInit(D5_GPIO, D5_PIN, &output_config);
    GPIO_PinInit(D6_GPIO, D6_PIN, &output_config); GPIO_PinInit(D7_GPIO, D7_PIN, &output_config);
}
/* ADC + DMA -----------------------------------------------------------------*/
void adc_init(void) {
    CLOCK_EnableClock(kCLOCK_Adc1);

    adc16_config_t cfg;
    ADC16_GetDefaultConfig(&cfg);

    // Calibração
    cfg.clockSource = kADC16_ClockSourceAlt1;
    cfg.clockDivider = kADC16_ClockDivider8;
    cfg.resolution = kADC16_ResolutionSE10Bit;
    cfg.enableHighSpeed = false;

    ADC16_Init(ADC1_PERIPHERAL, &cfg);
    ADC16_DoAutoCalibration(ADC1_PERIPHERAL);

    // Alta velocidade
    ADC16_GetDefaultConfig(&cfg);
    cfg.clockSource = kADC16_ClockSourceAlt1;
    cfg.clockDivider = kADC16_ClockDivider4;
    cfg.resolution = kADC16_ResolutionSE10Bit;
    cfg.enableHighSpeed = true;
    cfg.enableContinuousConversion = false;

    ADC16_Init(ADC1_PERIPHERAL, &cfg);

    // **IMPORTANTE** → Trigger por software
    ADC16_EnableHardwareTrigger(ADC1_PERIPHERAL, false);

    // Ativa DMA
    ADC1->SC2 |= ADC_SC2_DMAEN_MASK;
}
/* PIT -----------------------------------------------------------------------*/
void PIT_Init(int fs)
{
    CLOCK_EnableClock(kCLOCK_Pit0);

    PIT->MCR = 0x00; // Enable PIT

    PIT->CHANNEL[0].LDVAL = (SystemCoreClock / fs) - 1; // 60 kHz
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

    EnableIRQ(PIT0_IRQn);
}

void dma_init(void) {
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;

    DMAMUX0->CHCFG[0] = 0;
    DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(41);

    DMA0->TCD[0].SADDR = (uint32_t)&(ADC1->R[0]);
    DMA0->TCD[0].DADDR = (uint32_t)active_dma_buffer;
    DMA0->TCD[0].ATTR = DMA_ATTR_SSIZE(2) | DMA_ATTR_DSIZE(2);
    DMA0->TCD[0].SOFF = 0;
    DMA0->TCD[0].DOFF = 4;
    DMA0->TCD[0].NBYTES_MLNO = 4;
    DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(DMA_BUFFER_SIZE);
    DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(DMA_BUFFER_SIZE);
    DMA0->TCD[0].SLAST = 0;
    DMA0->TCD[0].DLAST_SGA = 0;
    DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK | DMA_CSR_DREQ_MASK;

    EnableIRQ(DMA0_IRQn);
    DMA0->ERQ = DMA_ERQ_ERQ0_MASK;
}
/* Interface LVGL ------------------------------------------------------------*/
static void touchpad_read_cb(lv_indev_drv_t * drv, lv_indev_data_t * data) {
    // Calibração do Touchscreen (AJUSTE AQUI SE NECESSÁRIO)
    const int X_MIN_HW = 40, X_MAX_HW = 289;
    const int Y_MIN_HW = 25, Y_MAX_HW = 217;
    TSPoint p = get_touch_point();
    LCD_SetWriteDir();
    char debug_buf[50];
    if (p.z > 50) {
        data->state = LV_INDEV_STATE_PR;

        data->point.x = map(p.x, X_MAX_HW, X_MIN_HW, 0, 319);
        data->point.y = map(p.y, Y_MIN_HW, Y_MAX_HW, 0, 239); // Y é invertido

        if (data->point.x < 0) data->point.x = 0; if (data->point.x > 319) data->point.x = 319;
        if (data->point.y < 0) data->point.y = 0; if (data->point.y > 239) data->point.y = 239;

        sprintf(debug_buf, "Raw: %d,%d\nMap: %d,%d", p.x, p.y, data->point.x, data->point.y);
        lv_label_set_text(debug_coord_label, debug_buf);
    } else {
        data->state = LV_INDEV_STATE_REL;
        lv_label_set_text(debug_coord_label, "Raw: ---\nMap: ---");
    }
}
static void scale_button_event_handler(lv_event_t * e) {
    current_scale_index = (current_scale_index + 1) % NUM_SCALES;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y,
                       scales[current_scale_index].min,
                       scales[current_scale_index].max);
    char btn_text[20];
    sprintf(btn_text, "Scale\n+/- %d", scales[current_scale_index].max);
    lv_label_set_text(scale_button_label, btn_text);
}
// ==========================================================
// Handlers dos Botões
// ==========================================================
static void run_stop_event_handler(lv_event_t * e) {
    g_is_running = !g_is_running; // Alterna o estado
    if (g_is_running) {
        lv_label_set_text(run_stop_label, LV_SYMBOL_STOP " Stop"); // Mostra "Stop"
        lv_obj_set_style_text_color(run_stop_label, lv_palette_main(LV_PALETTE_RED), 0); // Cor vermelha
    } else {
        lv_label_set_text(run_stop_label, LV_SYMBOL_PLAY " Run"); // Mostra "Play"
        lv_obj_set_style_text_color(run_stop_label, lv_palette_main(LV_PALETTE_GREEN), 0); // Cor verde
    }
}
static void update_trigger_menu_visibility(void) {
    if (g_trigger_mode == TRIGGER_NORMAL) {
        // Modo normal: Mostra sub-menu
        lv_obj_clear_flag(trig_edge_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(trigger_level_marker, LV_OBJ_FLAG_HIDDEN);
        // Sincroniza a posição do marcador com o valor atual
        lv_coord_t screen_y = map(g_trigger_level, 1023, 0, 0, 239);
        lv_obj_set_y(trigger_level_marker, screen_y);
    } else {
        // Modo auto: Esconde sub-menu
        lv_obj_add_flag(trig_edge_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(trigger_level_marker, LV_OBJ_FLAG_HIDDEN);
    }
}
static void menu_button_event_handler(lv_event_t * e) {
    // Esconde "Menu"
    lv_obj_add_flag(menu_btn, LV_OBJ_FLAG_HIDDEN);
    // Mostra "Trig Mode" e "Coupling"
    lv_obj_clear_flag(trig_mode_btn, LV_OBJ_FLAG_HIDDEN);
    // Mostra os sub-menus de trigger SE o modo for "Normal"
    update_trigger_menu_visibility();
}
static void trigger_mode_event_handler(lv_event_t * e) {
    // Esconde "Trig Mode" e "Coupling"
    lv_obj_add_flag(trig_mode_btn, LV_OBJ_FLAG_HIDDEN);
    // Mostra "Menu"
    lv_obj_clear_flag(menu_btn, LV_OBJ_FLAG_HIDDEN);
    // Alterna o modo
    if (g_trigger_mode == TRIGGER_AUTO) {
        g_trigger_mode = TRIGGER_NORMAL;
        lv_label_set_text(trigger_mode_label, "Trigger\nNormal");
    } else {
        g_trigger_mode = TRIGGER_AUTO;
        lv_label_set_text(trigger_mode_label, "Trigger\nAuto");
    }
    // Atualiza a visibilidade do sub-menu (Borda/Nível) com base no NOVO modo
    update_trigger_menu_visibility();
}
static void trigger_edge_event_handler(lv_event_t * e) {
    if (g_trigger_edge == RISING_EDGE) {
        g_trigger_edge = FALLING_EDGE;
        lv_label_set_text(trigger_edge_label, "Edge:\nFall");
    } else {
        g_trigger_edge = RISING_EDGE;
        lv_label_set_text(trigger_edge_label, "Edge:\nRise");
    }
}
// --- MODIFICAÇÃO (v8.7): Handler de toque no gráfico atualizado ---
// Event handler para toque direto no gráfico
static void chart_press_event_handler(lv_event_t * e) {
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_point_t point;
    lv_indev_get_point(indev, &point);
    lv_event_code_t code = lv_event_get_code(e);
    if (point.x < 160) {
        // --- METADE ESQUERDA: Ajuste de Offset ---
        if (code == LV_EVENT_PRESSED) {
            // Salva o ponto inicial do arraste
            drag_start_y = point.y;
            offset_at_drag_start = g_vertical_offset;
        } else if (code == LV_EVENT_PRESSING) {
            // Calcula o delta em pixels
            lv_coord_t y_delta = point.y - drag_start_y;
            // Converte delta de pixels para delta de ADC
            // 240 pixels = 1024 contagens. Y é invertido (arrastar para baixo = Y positivo).
            int32_t adc_delta = map(y_delta, 0, 239, 0, 1023); // (delta_y / 239) * -1023
            // Aplica o novo offset
            g_vertical_offset = offset_at_drag_start + adc_delta;
            // Limita (clamp) o offset para não sair da tela
            // (Permite offset de -512 a +512, que é meia tela)
            if (g_vertical_offset > 512) g_vertical_offset = 512;
            if (g_vertical_offset < -512) g_vertical_offset = -512;
        }
    }else {
        // --- METADE DIREITA: Ajuste de Trigger ---
        if (g_trigger_mode != TRIGGER_NORMAL) return;
        lv_coord_t chart_y = point.y - lv_obj_get_y(chart);
        if (chart_y < 0) chart_y = 0;
        if (chart_y > 239) chart_y = 239;
        // Converte Y da tela para valor centrado (ex: -120 a 120)
        int32_t centered_value = map(chart_y, 0, 239, 1023, 0);
        // Converte para valor ADC bruto com offset
        g_trigger_level = centered_value + 512;
        // Clamp
        if (g_trigger_level < 0) g_trigger_level = 0;
        if (g_trigger_level > 1023) g_trigger_level = 1023;
        lv_obj_set_y(trigger_level_marker, chart_y);
    }
}
void UI_Create(void) {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFFFF), 0);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    // ==========================================================
    // --- MODIFICAÇÃO: Criar estilo de fonte pequena ---
    // ==========================================================
    lv_style_init(&style_small_font);
    // Use lv_font_montserrat_12, _14, ou outra de sua preferência
    lv_style_set_text_font(&style_small_font, &lv_font_montserrat_12);
    // ==========================================================
    chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, 320, 240);
    lv_obj_align(chart, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, scales[0].min, scales[0].max);
    lv_chart_set_point_count(chart, OSC_X_POINT_COUNT);
    lv_chart_set_div_line_count(chart, OSC_GRID_HDIV_COUNT, OSC_GRID_VDIV_COUNT);
    ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_line_width(chart, 2, LV_PART_ITEMS);
    lv_obj_set_style_border_width(chart, 0, 0);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(chart, LV_OPA_TRANSP, 0);
    // Remove o padding interno do gráfico
    lv_obj_set_style_pad_all(chart, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(chart, 0, LV_PART_MAIN);
    // Adiciona o event handler de clique/arraste ao gráfico
    lv_obj_add_event_cb(chart, chart_press_event_handler, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(chart, chart_press_event_handler, LV_EVENT_PRESSING, NULL);
    // ==========================================================
    // Marcador de Nível de Trigger (Linha)
    // Criado DEPOIS do chart, mas ANTES dos botões.
    // ==========================================================
    trigger_level_marker = lv_label_create(lv_scr_act());
    lv_obj_set_size(trigger_level_marker, 50, 50);
    lv_label_set_text(trigger_level_marker, LV_SYMBOL_LEFT " T");
    lv_obj_set_style_text_align(trigger_level_marker, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(trigger_level_marker, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_obj_align(trigger_level_marker, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_coord_t initial_y = map(g_trigger_level, 1023, 0, 0, 239);
    lv_obj_set_y(trigger_level_marker, initial_y);
    lv_obj_set_style_transform_angle(trigger_level_marker, 1800, 0); // Gira 180 graus
    // --- Botão Scale ---
    lv_obj_t *scale_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(scale_btn, 50, 40);
    lv_obj_align(scale_btn, LV_ALIGN_TOP_LEFT, 5, 10);
    lv_obj_add_event_cb(scale_btn, scale_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(scale_btn, lv_color_white(), 0); // Fundo branco
    scale_button_label = lv_label_create(scale_btn);
    lv_obj_add_style(scale_button_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_obj_set_style_text_color(scale_button_label, lv_color_black(), 0); // Letra preta
    char btn_text[20];
    sprintf(btn_text, "Scale\n+/- %d", scales[0].max);
    lv_label_set_text(scale_button_label, btn_text);
    lv_obj_center(scale_button_label);
    lv_obj_move_foreground(scale_btn); // Move o botão (e seu label) para frente
    info_CH1_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(info_CH1_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_obj_set_width(info_CH1_label, 100);
    lv_obj_align(info_CH1_label, LV_ALIGN_BOTTOM_LEFT, 5, -10);
    lv_obj_set_style_text_align(info_CH1_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_color(info_CH1_label, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_label_set_text(info_CH1_label, "Iniciando...");
    lv_obj_move_foreground(info_CH1_label);
    info_label = lv_label_create(lv_scr_act());
lv_obj_add_style(info_label, &style_small_font, 0); // MODIFICAÇÃO
lv_obj_set_width(info_label, 100);
lv_obj_align(info_label, LV_ALIGN_BOTTOM_LEFT, 100, -25);
lv_obj_set_style_text_align(info_label, LV_TEXT_ALIGN_LEFT, 0);
lv_obj_set_style_text_color(info_label, lv_palette_main(LV_PALETTE_GREEN), 0);
lv_label_set_text(info_label, "Iniciando...");
lv_obj_move_foreground(info_label);
probe_label = lv_label_create(lv_scr_act());
lv_obj_add_style(probe_label, &style_small_font, 0); // MODIFICAÇÃO
lv_obj_set_width(probe_label, 150);
lv_obj_align(probe_label, LV_ALIGN_BOTTOM_LEFT, 100, -10);
lv_obj_set_style_text_align(probe_label, LV_TEXT_ALIGN_LEFT, 0);
lv_obj_set_style_text_color(probe_label, lv_palette_main(LV_PALETTE_GREEN), 0);
lv_label_set_text(probe_label, "Iniciando...");
lv_obj_move_foreground(probe_label);
    // ==========================================================
    // Criação dos Controles Principais (Lado Direito)
    // ==========================================================
    // --- Botão Run/Stop ---
    run_stop_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(run_stop_btn, 50, 30);
    lv_obj_align(run_stop_btn, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_add_event_cb(run_stop_btn, run_stop_event_handler, LV_EVENT_CLICKED, NULL);
    // Torna o background do botão transparente e remove a borda
    lv_obj_set_style_bg_opa(run_stop_btn, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(run_stop_btn, 0, 0);
    lv_obj_set_style_shadow_width(run_stop_btn, 0, 0);
    run_stop_label = lv_label_create(run_stop_btn);
    lv_obj_add_style(run_stop_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_label_set_text(run_stop_label, LV_SYMBOL_STOP " Stop"); // Inicia rodando
    lv_obj_center(run_stop_label);
    lv_obj_move_foreground(run_stop_btn);
    // Define a cor inicial do símbolo (vermelha porque está rodando)
    lv_obj_set_style_text_color(run_stop_label, lv_palette_main(LV_PALETTE_RED), 0);
    // --- Botão de Menu Principal ---
    menu_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(menu_btn, 70, 30);
    lv_obj_align(menu_btn, LV_ALIGN_TOP_RIGHT, -5, 10);
    lv_obj_add_event_cb(menu_btn, menu_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(menu_btn, lv_color_white(), 0); // Fundo branco
    lv_obj_t *menu_label = lv_label_create(menu_btn);
    lv_obj_add_style(menu_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_obj_set_style_text_color(menu_label, lv_color_black(), 0); // Letra preta
    lv_label_set_text(menu_label, LV_SYMBOL_BARS " Menu");
    lv_obj_center(menu_label);
    lv_obj_move_foreground(menu_btn);
    // --- Botão Trigger Mode (Auto/Normal) ---
    trig_mode_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(trig_mode_btn, 70, 30);
    lv_obj_align(trig_mode_btn, LV_ALIGN_TOP_RIGHT, -5, 10);
    lv_obj_add_event_cb(trig_mode_btn, trigger_mode_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(trig_mode_btn, lv_color_white(), 0); // Fundo branco
    trigger_mode_label = lv_label_create(trig_mode_btn);
    lv_obj_add_style(trigger_mode_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_obj_set_style_text_color(trigger_mode_label, lv_color_black(), 0); // Letra preta
    lv_label_set_text(trigger_mode_label, "Trigger\nAuto");
    lv_obj_center(trigger_mode_label);
    lv_obj_move_foreground(trig_mode_btn);
    // --- Botão Trigger Edge (Rise/Fall) ---
    trig_edge_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(trig_edge_btn, 50, 40);
    lv_obj_align_to(trig_edge_btn, scale_btn, LV_ALIGN_OUT_RIGHT_BOTTOM, 5, 0);
    lv_obj_add_event_cb(trig_edge_btn, trigger_edge_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(trig_edge_btn, lv_color_white(), 0); // Fundo branco
    trigger_edge_label = lv_label_create(trig_edge_btn);
    lv_obj_add_style(trigger_edge_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_obj_set_style_text_color(trigger_edge_label, lv_color_black(), 0); // Letra preta
    lv_label_set_text(trigger_edge_label, "Edge:\nRise");
    lv_obj_center(trigger_edge_label);
    lv_obj_move_foreground(trig_edge_btn);
    // ==========================================================
    // Esconde todos os menus de trigger no início
    // ==========================================================
    lv_obj_add_flag(trig_mode_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(trig_edge_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(trigger_level_marker, LV_OBJ_FLAG_HIDDEN);
    // --- MODIFICAÇÃO (v8.8): Corrigir alinhamento e Posição Y inicial ---
    zero_level_label = lv_label_create(lv_scr_act());
    lv_label_set_text(zero_level_label, LV_SYMBOL_PLAY);
    lv_obj_set_style_text_color(zero_level_label, lv_color_hex(0x00FFFF), 0);
    lv_obj_set_style_text_align(zero_level_label, LV_TEXT_ALIGN_LEFT, 0);
    // Alinha ao Topo-Esquerda (X=5, Y=0) e depois define o Y correto
    lv_obj_align(zero_level_label, LV_ALIGN_TOP_LEFT, 0, 0);
    // Mapeia o 0V inicial (512 + 0 offset) para a posição Y
    lv_coord_t initial_zero_y = map(25 - g_vertical_offset, 1023, 0, 0, 239);
    lv_obj_set_y(zero_level_label, initial_zero_y);
    // -----------------------------------------------------------------
    // ==========================================================
    // Label de depuração de Toque
    // ==========================================================
    debug_coord_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(debug_coord_label, &style_small_font, 0); // MODIFICAÇÃO
    lv_label_set_text(debug_coord_label, "Raw: ---\nMap: ---");
    lv_obj_set_style_text_color(debug_coord_label, lv_color_hex(0x808080), 0);
    lv_obj_set_style_text_align(debug_coord_label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(debug_coord_label, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
    lv_obj_move_foreground(debug_coord_label);
}
/* Inicialização de Hardware -------------------------------------------------*/
void KSDK_GPIO_Init(void) {
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

static void update_probe_state(void)
{
    // Leitura direta dos pinos
    bool dc = GPIO_PinRead(CTRL_GPIO, AC_DC_PIN); // 1 = DC, 0 = AC
    bool att1x = GPIO_PinRead(CTRL_GPIO, ATTEN_10X_PIN); // 1 = 1x, 0 = 10x
    bool div5 = GPIO_PinRead(CTRL_GPIO, DIV_2_PIN); // 1 = /5, 0 = /2
    // Detecta mudança
    if (dc != g_is_dc_coupling || att1x != g_is_1x_atten || div5 != (g_divider_ratio == 2.0f))
    {
        g_is_dc_coupling = dc;
        g_is_1x_atten = att1x;
        // Escolhe o divisor: /5 ou /2
        uint8_t divisor = div5 ? 5.6 : 2;
        g_divider_ratio = divisor;
        g_total_gain = (att1x ? 1 : 10) * divisor;
        // Atualiza os labels
        lv_label_set_text(info_label, dc ? "Cpl: DC" : "Cpl: AC");
        char txt[32];
        sprintf(txt, "Sonda: %dx /%d", att1x ? 1 : 10, divisor);
        lv_label_set_text(probe_label, txt);
    }
}
/* Função Principal ----------------------------------------------------------*/
int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    KSDK_GPIO_Init();
    UART0_Init(1000000);

    // Teste imediato (opcional)
    UART0_SendString("UART0 OK!\r\n");

    // Configuração do canal ADC
    adc16ChannelConfig.channelNumber = ADC_USER_CHANNEL;
    adc16ChannelConfig.enableInterruptOnConversionCompleted = false;
    adc16ChannelConfig.enableDifferentialConversion = false;

    // LVGL
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

    /* --- INICIALIZAÇÃO ADC + DMA --- */
    adc_init(); // ADC1: 10-bit, contínuo, ALTA VELOCIDADE (Corrigido)
    dma_init(); // DMA Ping-Pong
    ADC16_EnableDMA(ADC1_PERIPHERAL, true);
    Display_init(1);
    touchscreen_init(); // Touchscreen: 10-bit (só inicializa ADC0)
    UI_Create();

    // Inicia a conversão contínua
    ADC16_SetChannelConfig(ADC1_PERIPHERAL, ADC_CHANNEL_GROUP, &adc16ChannelConfig);
    int fs_hz = 300000;
    PIT_Init(fs_hz);

    Delay_ms(100);
    char info_text[100];
    uint32_t local_buffer[DMA_BUFFER_SIZE];
    uint32_t aligned_buffer[DMA_BUFFER_SIZE];
    SysTick_Config(SystemCoreClock / 1000U); // SystemCoreClock é 120MHz

    while (1) {
        lv_task_handler();
        update_probe_state();
        if (data_ready_flag) {
            // A medição de tempo foi MOVIDA para a ISR do DMA
            __disable_irq();
            memcpy(local_buffer, (void*)ready_dma_buffer, sizeof(local_buffer));
            data_ready_flag = false;
            __enable_irq();
            if (!g_is_running) {
                continue;
            }
            // ==========================================================
            // ETAPA 1: LÓGICA DE TRIGGER (Encontrar o ponto de disparo)
            // ==========================================================
            int trigger_index = -1; // -1 = Não encontrado
            for (int i = 1; i < DMA_BUFFER_SIZE; i++) {
            	// Valores crus do ADC
            	int32_t last_raw = local_buffer[i-1] & 0x3FF;
            	int32_t curr_raw = local_buffer[i] & 0x3FF;

            	// Centralização SOMENTE para a lógica do trigger
            	// (offset da tela NÃO afeta o trigger)
            	int32_t last_centered = last_raw - 512;
            	int32_t curr_centered = curr_raw - 512;

            	// Trigger também centralizado, independentemente do offset da tela
            	int32_t trigger_level_centered = g_trigger_level - 512;

            	// Comparação do trigger
            	if (g_trigger_edge == RISING_EDGE &&
            	    last_centered < trigger_level_centered &&
            	    curr_centered >= trigger_level_centered)
            	{
            	    trigger_index = i;
            	    break;
            	}
            	else if (g_trigger_edge == FALLING_EDGE &&
            	         last_centered > trigger_level_centered &&
            	         curr_centered <= trigger_level_centered)
            	{
            	    trigger_index = i;
            	    break;
            	}

            }
            // ==========================================================
            // ETAPA 2: DECIDIR SE VAMOS DESENHAR
            // ==========================================================
            if (g_trigger_mode == TRIGGER_NORMAL && trigger_index == -1) {
                continue;
            }
            if (g_trigger_mode == TRIGGER_AUTO && trigger_index == -1) {
                trigger_index = 0; // Modo roll
            }
            // ==========================================================
            // ETAPA 3: ALINHAR O BUFFER E ENVIAR VIA SERIAL
            // ==========================================================
            for (int i = 0; i < DMA_BUFFER_SIZE; i++) {
                int source_index = (trigger_index - g_trigger_x_pos + i + DMA_BUFFER_SIZE) % DMA_BUFFER_SIZE;
                aligned_buffer[i] = local_buffer[source_index];
            }
            static char uart_tx_buf[16];
			for (int i = 0; i < DMA_BUFFER_SIZE; i++) {
				uint16_t val = aligned_buffer[i] & 0x3FF;
				// Converte número para string sem sprintf (muito mais rápido)
				char *p = uart_tx_buf + sizeof(uart_tx_buf) - 1;
				*p = '\0';
				do {
					*--p = '0' + (val % 10);
					val /= 10;
				} while (val);
				*--p = ',';
				UART_WriteBlocking(UART0, (uint8_t*)p, strlen(p));
			}
			UART_WriteBlocking(UART0, (uint8_t*)"\n", 2);
            // ==========================================================
            // ETAPA 4: CÁLCULOS (AGORA NO BUFFER ALINHADO)
            // ==========================================================
            int32_t min_val = 1024;
            int32_t max_val = 0;
            uint32_t sum = 0;
            uint64_t sum_of_squares = 0;
            for (int i = 0; i < DMA_BUFFER_SIZE; i++) {
                uint32_t raw = aligned_buffer[i] & 0x3FF;
                if (raw < min_val) min_val = raw;
                if (raw > max_val) max_val = raw;
                sum += raw;
                sum_of_squares += (uint64_t)raw * raw;
                // --- MODIFICAÇÃO (v8.7): Aplicar o offset vertical ---
                // O sinal é centralizado em 512, e o offset é aplicado
                int32_t centered = (int32_t)raw - (512 + g_vertical_offset);
                // ----------------------------------------------------
                int16_t y = map(centered, -512, 511,
                                scales[current_scale_index].min,
                                scales[current_scale_index].max);
                lv_chart_set_value_by_id(chart, ser, i, y);
            }
            // --- Fim dos Cálculos ---
            double vmed_adc = (double)sum / DMA_BUFFER_SIZE;
            double mean_square_adc = (double)sum_of_squares / DMA_BUFFER_SIZE;
            double vrms_adc = sqrt(mean_square_adc);
            int32_t vpp_adc = max_val - min_val;
            double v_pp = (vpp_adc / ADC_MAX_COUNTS) * V_REF * g_total_gain;
            double v_med = (vmed_adc / ADC_MAX_COUNTS) * V_REF * g_total_gain;
            double v_rms = (vrms_adc / ADC_MAX_COUNTS) * V_REF * g_total_gain;
            lv_chart_refresh(chart);
            // --- MODIFICAÇÃO (v8.8): Atualizar Posição do Marcador Zero ---
            // Mapeia o 0V atual (512 + offset) para a coordenada Y da tela
            lv_coord_t zero_y = map(25 - g_vertical_offset, 1023, 0, 0, 239);
            lv_obj_set_y(zero_level_label, zero_y);
            // -----------------------------------------------------------
            // Formatação manual de Float para Sprintf
            int32_t vpp_int = (int32_t)v_pp;
            int32_t vpp_frac = (int32_t)((v_pp - vpp_int) * 100);
            int32_t vmed_int = (int32_t)v_med;
            int32_t vmed_frac = (int32_t)((v_med - vmed_int) * 100);
            int32_t vrms_int = (int32_t)v_rms;
            int32_t vrms_frac = (int32_t)((v_rms - vrms_int)* 100);

            // ==========================================================
            // ETAPA 5: CÁLCULO DE FREQUÊNCIA DO SINAL
            // ==========================================================
            uint32_t fs_khz = fs_hz/1000;
            uint32_t freq_sinal_hz = 0;
            int n_samples = 0;
            int32_t trigger_centered = g_trigger_level - 512;
            for (int i = g_trigger_x_pos + 10; i < DMA_BUFFER_SIZE; i++) {
                int32_t last_centered = ((aligned_buffer[i-1] & 0x3FF) - 512 - g_vertical_offset);
                int32_t curr_centered = ((aligned_buffer[i] & 0x3FF) - 512 - g_vertical_offset);
                bool edge_found = false;
                if (g_trigger_edge == RISING_EDGE &&
                    last_centered < trigger_centered &&
                    curr_centered >= trigger_centered) {
                    edge_found = true;
                }
                else if (g_trigger_edge == FALLING_EDGE &&
                         last_centered > trigger_centered &&
                         curr_centered <= trigger_centered) {
                    edge_found = true;
                }
                if (edge_found) {
                    n_samples = i - g_trigger_x_pos;
                    break;
                }
            }
            if (n_samples > 0) {
                freq_sinal_hz = fs_hz / n_samples;
            }
            // ==========================================================
            // Atualize o Label (com Frequência do Sinal)
            sprintf(info_text, "CH1\nVpp: %ld.%02ldV\nVmed: %ld.%02ldV\nVrms: %ld.%02ldV\nFreq: %lu Hz",
                    vpp_int, vpp_frac,
                    vmed_int, vmed_frac,
					vrms_int, vrms_frac,
                    freq_sinal_hz); // <-- Mostra a frequência do sinal
            lv_label_set_text(info_CH1_label, info_text);
        }
    }
}
void SysTick_Handler(void) {
    lv_tick_inc(1);
}
/* ISR do DMA – Ping-Pong ----------------------------------------------------*/
void DMA0_IRQHandler(void) {
    // 1. LIMPAR A FLAG DE INTERRUPÇÃO (CORREÇÃO DO ERRO 1)
    // O registro correto para limpar a interrupção do Canal 0 é o CINT
    DMA0->CINT = DMA_CINT_CINT(0);

    // 2. Lógica de Troca de Buffers (Melhorada para clareza)
    volatile uint32_t *temp_ptr = active_dma_buffer;
    active_dma_buffer = ready_dma_buffer;
    ready_dma_buffer = temp_ptr;

    // 3. Reprograma o destino do DMA
	DMA0->TCD[0].DADDR = (uint32_t)active_dma_buffer;
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(DMA_BUFFER_SIZE);
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(DMA_BUFFER_SIZE);

    data_ready_flag = true;

    // 4. Reconfigurar Endereço de Destino (DADDR)
    DMA0->TCD[0].DADDR = (uint32_t)active_dma_buffer;

    // 5. RE-HABILITAR A REQUISIÇÃO DMA (CORREÇÃO DO ERRO 2)
    // Isso garante que o módulo DMA aceitará o próximo trigger do ADC/PDB
    DMA0->ERQ = DMA_ERQ_ERQ0_MASK;
}

void PIT0_IRQHandler(void)
{
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    // Inicia a conversão no ADC1, canal 6
    ADC1->SC1[0] = ADC_SC1_ADCH(ADC_USER_CHANNEL);

    // (Opcional) medir tempo entre amostras aqui, como antes
}
