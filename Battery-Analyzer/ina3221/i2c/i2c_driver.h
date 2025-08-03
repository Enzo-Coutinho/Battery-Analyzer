#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "pico/stdlib.h"

void init_i2c_comm(void);

void i2c_write(const uint8_t address, const uint8_t *data, const size_t length);
void i2c_read(const uint8_t address, const uint8_t reg, uint8_t *data, const size_t length);

#endif