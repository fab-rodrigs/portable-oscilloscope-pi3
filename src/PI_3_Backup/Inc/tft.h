#ifndef TFT_H
#define TFT_H

#include "lvgl.h"
#include "fsl_common.h"
#include <stdint.h>

// Definição global da frequência do core para ser visível em todos os ficheiros
#define CORE_CLOCK 120000000U

// Funções que o main.c precisa de "ver"
void Display_init(uint8_t orientation);
void tft_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);

#endif // TFT_H
