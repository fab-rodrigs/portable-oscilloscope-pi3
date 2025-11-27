#include <lvgl/lvgl.h>
#include "tft.h"
#include "user_setting.h"
#include "fsl_gpio.h"

// ... (Macros de acesso direto como RD_HIGH, etc. permanecem as mesmas) ...
#define RD_HIGH()   (RD_GPIO->PSOR = (1U << RD_PIN))
#define RD_LOW()    (RD_GPIO->PCOR = (1U << RD_PIN))
#define WR_HIGH()   (WR_GPIO->PSOR = (1U << WR_PIN))
#define WR_LOW()    (WR_GPIO->PCOR = (1U << WR_PIN))
#define CD_HIGH()   (CD_GPIO->PSOR = (1U << CD_PIN))
#define CD_LOW()    (CD_GPIO->PCOR = (1U << CD_PIN))
#define CS_HIGH()   (CS_GPIO->PSOR = (1U << CS_PIN))
#define CS_LOW()    (CS_GPIO->PCOR = (1U << CS_PIN))
#define WR_STROBE() {WR_LOW(); WR_HIGH();}

// ... (Funções LCD_Write_Data_Fast, write_command, write_data, etc. permanecem as mesmas) ...
static inline void LCD_Write_Data_Fast(uint8_t data) {
    uint32_t porta_mask_clear = (((data >> 3) & 1) ? 0 : (1U << D3_PIN)) | (((data >> 5) & 1) ? 0 : (1U << D5_PIN));
    uint32_t portb_mask_clear = (((data >> 2) & 1) ? 0 : (1U << D2_PIN)) | (((data >> 4) & 1) ? 0 : (1U << D4_PIN));
    uint32_t portc_mask_clear = (((data >> 0) & 1) ? 0 : (1U << D0_PIN)) | (((data >> 1) & 1) ? 0 : (1U << D1_PIN)) | (((data >> 6) & 1) ? 0 : (1U << D6_PIN)) | (((data >> 7) & 1) ? 0 : (1U << D7_PIN));
    uint32_t porta_mask_set = (((data >> 3) & 1) ? (1U << D3_PIN) : 0) | (((data >> 5) & 1) ? (1U << D5_PIN) : 0);
    uint32_t portb_mask_set = (((data >> 2) & 1) ? (1U << D2_PIN) : 0) | (((data >> 4) & 1) ? (1U << D4_PIN) : 0);
    uint32_t portc_mask_set = (((data >> 0) & 1) ? (1U << D0_PIN) : 0) | (((data >> 1) & 1) ? (1U << D1_PIN) : 0) | (((data >> 6) & 1) ? (1U << D6_PIN) : 0) | (((data >> 7) & 1) ? (1U << D7_PIN) : 0);
    GPIOA->PCOR = porta_mask_clear; GPIOB->PCOR = portb_mask_clear; GPIOC->PCOR = portc_mask_clear;
    GPIOA->PSOR = porta_mask_set;   GPIOB->PSOR = portb_mask_set;   GPIOC->PSOR = portc_mask_set;
}

void write_command(uint8_t cmd) { CD_LOW(); LCD_Write_Data_Fast(cmd); WR_STROBE(); CD_HIGH(); }
void write_data(uint8_t data) { CD_HIGH(); LCD_Write_Data_Fast(data); WR_STROBE(); }
void write_data_16bit(uint16_t data) { write_data(data >> 8); write_data(data & 0xFF); }
void set_addr_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    write_command(0x2A); write_data_16bit(x1); write_data_16bit(x2);
    write_command(0x2B); write_data_16bit(y1); write_data_16bit(y2);
    write_command(0x2C);
}

void tft_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    CS_LOW();
    set_addr_window(area->x1, area->y1, area->x2, area->y2);
    uint32_t size = lv_area_get_size(area);
    for (uint32_t i = 0; i < size; i++) { write_data_16bit(color_p[i].full); }
    CS_HIGH();
    lv_disp_flush_ready(drv);
}

// --- FUNÇÃO MODIFICADA ---
void Display_init(uint8_t orientation) {
    CS_LOW();
    RESET_GPIO->PCOR = (1U << RESET_PIN); SDK_DelayAtLeastUs(10000, CORE_CLOCK);
    RESET_GPIO->PSOR = (1U << RESET_PIN); SDK_DelayAtLeastUs(120000, CORE_CLOCK);

    write_command(0x01); SDK_DelayAtLeastUs(120000, CORE_CLOCK); // Software Reset
    write_command(0x11); SDK_DelayAtLeastUs(120000, CORE_CLOCK); // Sleep Out
    write_command(0x3A); write_data(0x55);    // Pixel Format: 16 bpp

    write_command(0x36); // Memory Access Control
    // Os valores de orientação são baseados na biblioteca Adafruit GFX
    switch (orientation) {
        case 0: // Retrato (Portrait)
            write_data(0x48);
            break;
        case 1: // Paisagem (Landscape)
            write_data(0x28);
            break;
        case 2: // Retrato Invertido
            write_data(0x88);
            break;
        case 3: // Paisagem Invertida
            write_data(0xE8);
            break;
        default:
            write_data(0x48); // Padrão
            break;
    }

    write_command(0x29); SDK_DelayAtLeastUs(20000, CORE_CLOCK); // Display ON
    CS_HIGH();
}
