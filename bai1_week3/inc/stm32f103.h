#ifndef STM32F103_H
#define STM32F103_H
#include <stdint.h>

#define __IO volatile

/* ---- RCC (0x40021000) ---- */
typedef struct {
    __IO uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
} RCC_t;
#define RCC ((RCC_t *)0x40021000UL)
#define RCC_APB2ENR_IOPAEN   (1u << 2)
#define RCC_APB2ENR_IOPBEN   (1u << 3)
#define RCC_APB2ENR_IOPCEN   (1u << 4)
#define RCC_APB2ENR_USART1EN (1u << 14)
#define RCC_APB1ENR_I2C1EN   (1u << 21)

/* ---- GPIO ---- */
typedef struct {
    __IO uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} GPIO_t;
#define GPIOA ((GPIO_t *)0x40010800UL)
#define GPIOB ((GPIO_t *)0x40010C00UL)
#define GPIOC ((GPIO_t *)0x40011000UL)

/* ---- USART1 (0x40013800) ---- */
typedef struct {
    __IO uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
} USART_t;
#define USART1 ((USART_t *)0x40013800UL)
#define USART_SR_TXE  (1u << 7)
#define USART_CR1_RE  (1u << 2)
#define USART_CR1_TE  (1u << 3)
#define USART_CR1_UE  (1u << 13)

/* ---- I2C1 (0x40005400) ---- */
typedef struct {
    __IO uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE;
} I2C_t;
#define I2C1 ((I2C_t *)0x40005400UL)
#define I2C_CR1_PE     (1u << 0)
#define I2C_CR1_START  (1u << 8)
#define I2C_CR1_STOP   (1u << 9)
#define I2C_CR1_SWRST  (1u << 15)
#define I2C_SR1_SB     (1u << 0)
#define I2C_SR1_ADDR   (1u << 1)
#define I2C_SR1_BTF    (1u << 2)
#define I2C_SR1_TXE    (1u << 7)
#define I2C_SR1_AF     (1u << 10)

#endif
