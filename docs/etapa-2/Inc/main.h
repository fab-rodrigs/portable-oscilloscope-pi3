#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes KSDK -------------------------------------------------------------*/
#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

/* Includes KSDK/LVGL */
#include "lvgl.h"
#include "stdio.h"
#include "user_setting.h" // Inclui as definições de pinos K64F

/* Exported functions prototypes ---------------------------------------------*/
void SystemClock_Config(void);
void KSDK_GPIO_Init(void); // Função de inicialização do GPIO no KSDK
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
