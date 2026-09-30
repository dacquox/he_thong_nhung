#include "stm32f103.h"
#include "uart.h"
#include "i2c.h"
#include "ssd1306.h"

enum {
    TOP      = 12,   /* toạ độ y của đỉnh chữ */
    HEIGHT   = 40,   /* chiều cao mỗi chữ */
    STROKE   = 6,    /* độ dày nét */
    LETTER_W = 28,   /* chiều rộng mỗi chữ */

    H_X = 12,        /* toạ độ x của chữ H */
    T_X = 50,        /* toạ độ x của chữ T */
    N_X = 88         /* toạ độ x của chữ N */
};

static void delay_ms(uint32_t ms)       /* ước lượng thô ở 8MHz */
{
    for (volatile uint32_t i = 0; i < ms * 800; i++);
}

/* Tô đặc hình chữ nhật: góc trên-trái (x, y), rộng w, cao h */
static void fill_rect(int x, int y, int w, int h)
{
    for (int j = y; j < y + h; j++)
        for (int i = x; i < x + w; i++)
            ssd1306_pixel(i, j, 1);
}

static void draw_H(int x, int y)
{
    fill_rect(x, y, STROKE, HEIGHT);                          /* nét đứng trái */
    fill_rect(x + LETTER_W - STROKE, y, STROKE, HEIGHT);      /* nét đứng phải */
    fill_rect(x, y + (HEIGHT - STROKE) / 2, LETTER_W, STROKE);/* nét ngang giữa */
}

static void draw_T(int x, int y)
{
    fill_rect(x, y, LETTER_W, STROKE);                        /* nét ngang trên */
    fill_rect(x + (LETTER_W - STROKE) / 2, y, STROKE, HEIGHT);/* nét đứng giữa */
}

static void draw_N(int x, int y)
{
    fill_rect(x, y, STROKE, HEIGHT);                          /* nét đứng trái */
    fill_rect(x + LETTER_W - STROKE, y, STROKE, HEIGHT);      /* nét đứng phải */
    for (int i = 0; i < HEIGHT; i++)                          /* nét chéo: mỗi hàng dịch sang phải */
        fill_rect(x + (LETTER_W - STROKE) * i / (HEIGHT - 1), y + i, STROKE, 1);
}

int main(void)
{
    /* LED PC13 (Blue Pill): output push-pull 2MHz */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(0xFu << 20);
    GPIOC->CRH |=  (0x2u << 20);

    uart_init();
    i2c1_init();

    uart_puts("\r\n== Bai 01: I2C + SSD1306 ==\r\n");
    i2c1_scan();

    ssd1306_init();
    ssd1306_clear();

    draw_H(H_X, TOP);
    draw_T(T_X, TOP);
    draw_N(N_X, TOP);

    ssd1306_update();
    uart_puts("OLED updated\r\n");

    while (1) {
        GPIOC->ODR ^= (1u << 13);       /* nháy LED */
        delay_ms(500);
    }
}
