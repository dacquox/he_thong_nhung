/* inc/i2c.h */
#ifndef I2C_H
#define I2C_H
#include <stdint.h>
void i2c1_init(void);
int  i2c1_write(uint8_t addr7, const uint8_t *buf, uint32_t len); /* 0 = OK, -1 = lỗi */
void i2c1_scan(void);
#endif
