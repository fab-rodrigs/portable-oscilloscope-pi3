#ifndef UART0_H
#define UART0_H

#include <stdint.h>
#include <stdbool.h>

void UART0_Init(uint32_t baudrate);
void UART0_SendByte(uint8_t data);
void UART0_SendString(const char *str);

bool UART0_Available(void);
bool UART0_Read(uint8_t *data);

#endif
