/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file : pin_magic.h
  * @brief : Macros for TFT control signals (RD, WR, CD, CS) and data bus operations
  *          Adapted from Adafruit SPFD5408 pin_magic.h for FRDM-K64F using KSDK
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef _PIN_MAGIC_H_
#define _PIN_MAGIC_H_

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "user_setting.h"

// Control signals are ACTIVE LOW (idle is HIGH)
#define RD_ACTIVE  GPIO_PinWrite(BOARD_INITPINS_RD_GPIO, BOARD_INITPINS_RD_PIN, 0)
#define RD_IDLE    GPIO_PinWrite(BOARD_INITPINS_RD_GPIO, BOARD_INITPINS_RD_PIN, 1)
#define WR_ACTIVE  GPIO_PinWrite(GPIOB, 0, 0) // Changed to PTB0
#define WR_IDLE    GPIO_PinWrite(GPIOB, 0, 1) // Changed to PTB0
#define CD_COMMAND GPIO_PinWrite(BOARD_INITPINS_RS_GPIO, BOARD_INITPINS_RS_PIN, 0)
#define CD_DATA    GPIO_PinWrite(BOARD_INITPINS_RS_GPIO, BOARD_INITPINS_RS_PIN, 1)
#define CS_ACTIVE  GPIO_PinWrite(BOARD_INITPINS_CS_GPIO, BOARD_INITPINS_CS_PIN, 0)
#define CS_IDLE    GPIO_PinWrite(BOARD_INITPINS_CS_GPIO, BOARD_INITPINS_CS_PIN, 1)

// Data write strobe
#define WR_STROBE { WR_ACTIVE; SDK_DelayAtLeastUs(1, SystemCoreClock); WR_IDLE; }

// Write data to bus
#define writeDataBusInline(d) { \
    GPIO_PinWrite(BOARD_INITPINS_D0_GPIO, BOARD_INITPINS_D0_PIN, (d >> 0) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D1_GPIO, BOARD_INITPINS_D1_PIN, (d >> 1) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D2_GPIO, BOARD_INITPINS_D2_PIN, (d >> 2) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D3_GPIO, BOARD_INITPINS_D3_PIN, (d >> 3) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D4_GPIO, BOARD_INITPINS_D4_PIN, (d >> 4) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D5_GPIO, BOARD_INITPINS_D5_PIN, (d >> 5) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D6_GPIO, BOARD_INITPINS_D6_PIN, (d >> 6) & 1); \
    GPIO_PinWrite(BOARD_INITPINS_D7_GPIO, BOARD_INITPINS_D7_PIN, (d >> 7) & 1); \
}

// Set value of TFT register: 8-bit address, 8-bit value
#define writeRegister8inline(a, d) { \
    CS_ACTIVE; \
    SDK_DelayAtLeastUs(20, SystemCoreClock); \
    CD_COMMAND; \
    writeDataBusInline(a); \
    WR_STROBE; \
    SDK_DelayAtLeastUs(20, SystemCoreClock); \
    CD_DATA; \
    writeDataBusInline(d); \
    WR_STROBE; \
    SDK_DelayAtLeastUs(20, SystemCoreClock); \
    CS_IDLE; \
    SDK_DelayAtLeastUs(20, SystemCoreClock); \
}

// Set value of TFT register: 16-bit address, 16-bit value
#define writeRegister16inline(a, d) { \
    uint8_t hi = (a) >> 8, lo = (a); \
    writeRegister8inline(hi, (d) >> 8); \
    writeRegister8inline(lo, (d) & 0xFF); \
}

// Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
#define writeRegisterPairInline(aH, aL, d) { \
    uint8_t hi = (d) >> 8, lo = (d); \
    writeRegister8inline(aH, hi); \
    writeRegister8inline(aL, lo); \
}

#endif /* _PIN_MAGIC_H_ */
