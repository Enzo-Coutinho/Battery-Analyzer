#include "i2c_driver.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define I2C_FREQUENCY (400 * 1000) // 400 kHz

void init_i2c_comm(const uint8_t SDA, const uint8_t SCL, const uint8_t i2c_port) {
    i2c_init(i2c_port, I2C_FREQUENCY);

    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);

    bi_decl(bi_2pins_with_func(SDA, SCL, GPIO_FUNC_I2C));
}

void i2c_write(const uint8_t address, const uint8_t reg, const uint8_t *data, const size_t length) {
    uint8_t buf[length];
    buf[0] = reg;
    buf[1] = data[0]; // Copy the first byte of data
    for(int i=1; i<length; i++)
    {
        buf[i] = data[i];
    }
    i2c_write_blocking(I2C_PORT, address, buf, length, false);
}

void i2c_read(const uint8_t address, const uint8_t reg, uint8_t *data, size_t length) {
    i2c_write_blocking(I2C_PORT, address, &reg, 1, true); // Send register address
    i2c_read_blocking(I2C_PORT, address, &data[0], length, false); // Read data
}