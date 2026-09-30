/* src/uart.c */
#include "stm32f103.h"
#include "uart.h"

void uart_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    /* PA9 = TX: AF push-pull 50MHz (0xB); PA10 = RX: input floating (0x4) */
    GPIOA->CRH &= ~((0xFu << 4) | (0xFu << 8));
    GPIOA->CRH |=  ((0xBu << 4) | (0x4u << 8));

    USART1->BRR = 833;   /* 8MHz / 9600 = 833.33 */
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void uart_putc(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (uint32_t)c;
}

void uart_puts(const char *s)
{
    while (*s) uart_putc(*s++);
}

void uart_puthex8(uint8_t v)
{
    const char *h = "0123456789ABCDEF";
    uart_puts("0x");
    uart_putc(h[v >> 4]);
    uart_putc(h[v & 0xF]);
}
