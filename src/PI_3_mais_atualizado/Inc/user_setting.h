#ifndef USER_SETTING_H_
#define USER_SETTING_H_

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "lvgl.h"

// Definições de atraso para eliminar os erros 'WRITE_DELAY' e 'READ_DELAY'
// Deixe vazio se os pinos de controle (WR/RD) já forem lentos o suficiente.
#define WRITE_DELAY
#define READ_DELAY

/* ================= PINAGEM ================== */
// Mantido o mapeamento para K64F (presume-se que RD_PIN e WR_PIN sejam os índices 0-31)
#define RD_GPIO   GPIOB
#define RD_PORT   PORTB
#define RD_PIN    2
#define WR_GPIO   GPIOB
#define WR_PORT   PORTB
#define WR_PIN    3
#define CD_GPIO   GPIOB
#define CD_PORT   PORTB
#define CD_PIN    10
#define CS_GPIO   GPIOB
#define CS_PORT   PORTB
#define CS_PIN    11
#define RESET_GPIO GPIOC
#define RESET_PORT PORTC
#define RESET_PIN 11
#define D0_GPIO   GPIOC
#define D0_PORT   PORTC
#define D0_PIN    12
#define D1_GPIO   GPIOC
#define D1_PORT   PORTC
#define D1_PIN    4
#define D2_GPIO   GPIOB
#define D2_PORT   PORTB
#define D2_PIN    9
#define D3_GPIO   GPIOA
#define D3_PORT   PORTA
#define D3_PIN    1
#define D4_GPIO   GPIOB
#define D4_PORT   PORTB
#define D4_PIN    23
#define D5_GPIO   GPIOA
#define D5_PORT   PORTA
#define D5_PIN    2
#define D6_GPIO   GPIOC
#define D6_PORT   PORTC
#define D6_PIN    2
#define D7_GPIO   GPIOC
#define D7_PORT   PORTC
#define D7_PIN    3


/* =============== UTILITÁRIOS KINETIS SDK (KSDK) ================== */

// As funções PIN_LOW, PIN_HIGH, PIN_INPUT e PIN_OUTPUT foram convertidas
// para o KSDK e transformadas em funções inline para evitar erros de
// 'conflicting types' e 'implicit declaration'.

/**
 * @brief Define o pino para nível lógico LOW (Reset).
 * @param gpio Ponteiro para a base do GPIO (e.g., GPIOC).
 * @param pin Número do pino (0-31).
 */
static inline void PIN_LOW(GPIO_Type *gpio, uint32_t pin)
{
    // KSDK: 0U é o valor para resetar o pino.
    GPIO_PinWrite(gpio, pin, 0U);
}

/**
 * @brief Define o pino para nível lógico HIGH (Set).
 * @param gpio Ponteiro para a base do GPIO (e.g., GPIOC).
 * @param pin Número do pino (0-31).
 */
static inline void PIN_HIGH(GPIO_Type *gpio, uint32_t pin)
{
    // KSDK: 1U é o valor para setar o pino.
    GPIO_PinWrite(gpio, pin, 1U);
}

/**
 * @brief Configura o pino como INPUT.
 * @param gpio Ponteiro para a base do GPIO (e.g., GPIOC).
 * @param pin Número do pino (0-31).
 */
static inline void PIN_INPUT(GPIO_Type *gpio, uint32_t pin)
{
    // KSDK usa pinDirection para configurar INPUT/OUTPUT.
    gpio_pin_config_t cfg = {kGPIO_DigitalInput, 0U};
    GPIO_PinInit(gpio, pin, &cfg);
}

/**
 * @brief Configura o pino como OUTPUT.
 * @param gpio Ponteiro para a base do GPIO (e.g., GPIOC).
 * @param pin Número do pino (0-31).
 */
static inline void PIN_OUTPUT(GPIO_Type *gpio, uint32_t pin)
{
    // KSDK usa pinDirection para configurar INPUT/OUTPUT.
    gpio_pin_config_t cfg = {kGPIO_DigitalOutput, 0U};
    GPIO_PinInit(gpio, pin, &cfg);
}

// Funções de leitura/escrita do BUS de 8 bits (baseadas no snippet do código original)

/**
 * @brief Escreve um byte no barramento de dados (bits D0-D7).
 * @param d Byte a ser escrito.
 */
static inline void write_8(uint8_t d)
{
    // Usa as novas funções PIN_HIGH/PIN_LOW baseadas em KSDK.
    (d & (1 << 0)) ? PIN_HIGH(D0_GPIO, D0_PIN) : PIN_LOW(D0_GPIO, D0_PIN);
    (d & (1 << 1)) ? PIN_HIGH(D1_GPIO, D1_PIN) : PIN_LOW(D1_GPIO, D1_PIN);
    (d & (1 << 2)) ? PIN_HIGH(D2_GPIO, D2_PIN) : PIN_LOW(D2_GPIO, D2_PIN);
    (d & (1 << 3)) ? PIN_HIGH(D3_GPIO, D3_PIN) : PIN_LOW(D3_GPIO, D3_PIN);
    (d & (1 << 4)) ? PIN_HIGH(D4_GPIO, D4_PIN) : PIN_LOW(D4_GPIO, D4_PIN);
    (d & (1 << 5)) ? PIN_HIGH(D5_GPIO, D5_PIN) : PIN_LOW(D5_GPIO, D5_PIN);
    (d & (1 << 6)) ? PIN_HIGH(D6_GPIO, D6_PIN) : PIN_LOW(D6_GPIO, D6_PIN);
    (d & (1 << 7)) ? PIN_HIGH(D7_GPIO, D7_PIN) : PIN_LOW(D7_GPIO, D7_PIN);
}

/**
 * @brief Lê um byte do barramento de dados (bits D0-D7).
 * @return Byte lido.
 */
static inline uint8_t read_8(void)
{
    uint8_t d = 0;
    // Usa a função KSDK GPIO_PinRead
    if (GPIO_PinRead(D0_GPIO, D0_PIN)) d |= (1 << 0);
    if (GPIO_PinRead(D1_GPIO, D1_PIN)) d |= (1 << 1);
    if (GPIO_PinRead(D2_GPIO, D2_PIN)) d |= (1 << 2);
    if (GPIO_PinRead(D3_GPIO, D3_PIN)) d |= (1 << 3);
    if (GPIO_PinRead(D4_GPIO, D4_PIN)) d |= (1 << 4);
    if (GPIO_PinRead(D5_GPIO, D5_PIN)) d |= (1 << 5);
    if (GPIO_PinRead(D6_GPIO, D6_PIN)) d |= (1 << 6);
    if (GPIO_PinRead(D7_GPIO, D7_PIN)) d |= (1 << 7);
    return d;
}

#endif /* USER_SETTING_H_ */
