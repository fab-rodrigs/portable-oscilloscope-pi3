#include "UART0.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "MK64F12.h"

/* ----------------- Ring Buffer ----------------- */

#define RING_BUFFER_SIZE 256

static volatile uint8_t ringBuffer[RING_BUFFER_SIZE];
static volatile uint16_t ringHead = 0;
static volatile uint16_t ringTail = 0;

/* Insere no ring buffer */
static inline void RingBuffer_Put(uint8_t data)
{
    uint16_t next = (ringHead + 1) % RING_BUFFER_SIZE;

    if (next != ringTail)      // não sobrescreve se cheio
    {
        ringBuffer[ringHead] = data;
        ringHead = next;
    }
}

/* Lê do ring buffer */
bool UART0_Read(uint8_t *data)
{
    if (ringTail == ringHead)
        return false; // vazio

    *data = ringBuffer[ringTail];
    ringTail = (ringTail + 1) % RING_BUFFER_SIZE;
    return true;
}

bool UART0_Available(void)
{
    return (ringTail != ringHead);
}

/* ----------------- UART0 IRQ ----------------- */

void UART0_RX_TX_IRQHandler(void)
{
    if (UART_GetStatusFlags(UART0) & kUART_RxDataRegFullFlag)
    {
        uint8_t ch = UART_ReadByte(UART0);
        RingBuffer_Put(ch);
    }

    __DSB(); // evita repetição da IRQ
}

/* ----------------- UART0 Inicialização ----------------- */

void UART0_Init(uint32_t baudrate)
{
    uart_config_t config;

    /* Ativa clock do PORTB e UART0 */
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_Uart0);

    /* Configura pinos:
       PTB16 = UART0_RX (ALT3)
       PTB17 = UART0_TX (ALT3)
    */
    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = baudrate;
    config.enableTx = true;
    config.enableRx = false;

    UART_Init(UART0, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    /* Habilita FIFO RX/TX */
    UART0->PFIFO |= UART_PFIFO_RXFE_MASK | UART_PFIFO_TXFE_MASK;

    /* Habilita interrupção RX */
    UART_EnableInterrupts(UART0, kUART_RxDataRegFullInterruptEnable);

    /* Habilita IRQ no NVIC */
    EnableIRQ(UART0_RX_TX_IRQn);

    /* Limpa ring buffer */
    ringHead = 0;
    ringTail = 0;
}

/* ----------------- TX Simples ----------------- */

void UART0_SendByte(uint8_t data)
{
    while (!(UART0->S1 & UART_S1_TDRE_MASK))
        ;
    UART0->D = data;
}

void UART0_SendString(const char *str)
{
    while (*str)
        UART0_SendByte(*str++);
}
