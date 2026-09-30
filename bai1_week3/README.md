# Bài 01: I2C với OLED trên STM32F103 (lập trình thanh ghi)

- Sinh viên: <Pham Truong Phuoc> - MSSV: <B23DCDT195>
- Vi điều khiển: STM32F103 (Blue Pill), lập trình trực tiếp thanh ghi
- Ngoại vi chọn: OLED 128x64 giao tiếp I2C (SSD1306/SH1106, địa chỉ 0x3C)
- Nội dung: cấu hình I2C1, hiển thị chữ HTN lên OLED bằng cách vẽ các hình chữ nhật (x, y, rộng, cao)

## Đấu dây

| OLED | STM32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SCL | PB6 (I2C1_SCL) |
| SDA | PB7 (I2C1_SDA) |

UART1 để debug (9600 baud): PA9 (TX) -> RX của USB-UART, PA10 (RX) -> TX của USB-UART.

## Cấu trúc thư mục

- `src/`: main.c, startup.c, i2c.c, ssd1306.c, uart.c
- `inc/`: stm32f103.h (định nghĩa thanh ghi), các header driver
- `linker.ld`: linker script
- `Makefile`
- `build/`: bai01.bin, bai01.elf, bai01.map

## Build và nạp

```
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi make openocd
make          # biên dịch
make flash    # nạp bằng ST-Link
make serial   # xem log UART (picocom 9600)
```
