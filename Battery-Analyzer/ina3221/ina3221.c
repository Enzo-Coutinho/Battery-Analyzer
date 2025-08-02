#include "ina3221.h"

float _shunt_resistors[3] = {0.1, 0.1, 0.1}; // Placeholder for shunt resistors
const uint8_t INA3221_ADDRESS = INA3221_I2C_ADDRESS_GND;

void reset_ina3221(void) {

}

void get_configuration(configuration_t * configuration)
{
    read_register_ina3221(__ADDR_CONFIGURATION, configuration->u8_configuration, sizeof(configuration->u8_configuration));
}

void set_configuration(configuration_t  *config) {
    get_configuration(config);
    write_register_ina3221(__ADDR_CONFIGURATION, config->u8_configuration, sizeof(config->u8_configuration));
}

void read_register_ina3221(uint8_t reg, uint8_t *data, size_t length) {
    i2c_read(INA3221_ADDRESS, reg, data, length);
}

void write_register_ina3221(uint8_t reg, const uint8_t *data, size_t length) {
    i2c_write(INA3221_ADDRESS, reg, data, length);
}