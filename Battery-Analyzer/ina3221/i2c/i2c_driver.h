#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "pico/stdlib.h"

#define I2C_PORT i2c0

void init_i2c_comm(const uint8_t SDA, const uint8_t SCL, const uint8_t i2c_port);

void i2c_write(const uint8_t address, const uint8_t reg, const uint8_t *data, const size_t length);
void i2c_read(const uint8_t address, const uint8_t reg, uint8_t *data, const size_t length);

#endif