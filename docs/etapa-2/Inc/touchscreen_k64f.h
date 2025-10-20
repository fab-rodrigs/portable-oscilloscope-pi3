/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file : touchscreen_k64f.h
  * @brief : Header for touchscreen_k64f.c, adapted from Adafruit SPFD5408_TouchScreen for FRDM-K64F
  *         Declares functions and types for touchscreen handling using KSDK.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef _TOUCHSCREEN_K64F_H_
#define _TOUCHSCREEN_K64F_H_

/* Includes */
#include <stdint.h>
#include <stdbool.h>
#include "fsl_gpio.h"
#include "fsl_adc16.h"

/* Definições de Oversampling */
#define NUMSAMPLES 2  // 1= sem oversampling, 2= double-sampling, 3+= median sort

/* Definições de Pinos */
#define XP_PIN   2    // PTC2
#define YP_PIN   3    // PTB3
#define XM_PIN   10   // PTB10
#define YM_PIN   3    // PTC3
#define XP_PORT  PORTC
#define YP_PORT  PORTB
#define XM_PORT  PORTB
#define YM_PORT  PORTC
#define XP_GPIO  GPIOC
#define YP_GPIO  GPIOB
#define XM_GPIO  GPIOB
#define YM_GPIO  GPIOC

// ADC configuration
//#define ADC0_BASE ADC0
//#define ADC1_BASE ADC1
#define YP_ADC_CHAN 13U
#define XM_ADC_CHAN 14U

#define RXPLATE 300U  // Resistência de pull-up
#define PRESSURE_THRESHOLD 10U  // Threshold de pressão

/* Struct equivalente a TSPoint class */
typedef struct {
    int16_t x, y, z;  // x, y coordenadas; z = pressão
} TSPoint;

/* Protótipos de Funções */
void touchscreen_init(void);
TSPoint get_touch_point(void);
int read_touch_x(void);
int read_touch_y(void);
uint16_t get_pressure(void);

#endif /* _TOUCHSCREEN_K64F_H_ */
