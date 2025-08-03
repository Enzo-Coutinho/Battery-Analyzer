#include "i2c_driver.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define I2C_FREQUENCY (400 * 1000) // 400 kHz

#define I2C_SDA 8
#define I2C_SCL 9
#define I2C_PORT i2c0

void init_i2c_comm(void) {
    i2c_init(I2C_PORT, I2C_FREQUENCY);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    bi_decl(bi_2pins_with_func(I2C_SDA, I2C_SCL, GPIO_FUNC_I2C));
}

void i2c_write(const uint8_t address, const uint8_t *data, const size_t length) {
    i2c_write_blocking(I2C_PORT, address, data, length, false);
}

void i2c_read(const uint8_t address, const uint8_t reg, uint8_t *data, size_t length) {
    i2c_write_blocking(I2C_PORT, address, &reg, 1, true); // Send register address
    i2c_read_blocking(I2C_PORT, address, &data[0], length, false); // Read data
}