#include "ina3221.h"

float _shunt_resistors[3] = {0.1, 0.1, 0.1}; // Placeholder for shunt resistors

const uint8_t INA3221_ADDRESS = INA3221_I2C_ADDRESS_GND;

enum ENDIANESS
{
    BIG_ENDIAN = 0,
    LITTLE_ENDIAN = 1
};

uint16_t swap_endian(uint8_t value[2], enum ENDIANESS endianess);

void reset_ina3221(void) {
    configuration_t configuration = {.configuration_bitmap = {._rst = 1}};
    set_configuration(&configuration);
}

void get_configuration(configuration_t * configuration)
{
    read_register_ina3221(__ADDR_CONFIGURATION, configuration->u8_configuration, sizeof(configuration->u8_configuration));
    configuration->u16_configuration = swap_endian(configuration->u8_configuration, LITTLE_ENDIAN);
}

void set_configuration(configuration_t  *config) {
    configuration_t current_config;
    get_configuration(&current_config);

    config->u16_configuration |= current_config.u16_configuration;

    swap_endian(config->u8_configuration, BIG_ENDIAN);

    write_register_ina3221(__ADDR_CONFIGURATION, config->u8_configuration, sizeof(config->u8_configuration));
}




void read_register_ina3221(uint8_t reg, uint8_t *data, size_t length) {
    i2c_read(INA3221_ADDRESS, reg, data, length);
}

void write_register_ina3221(uint8_t reg, const uint8_t *data, size_t length) {
    i2c_write(INA3221_ADDRESS, reg, data, length);
}

uint16_t swap_endian(uint8_t value[2], enum ENDIANESS endianess) {
    switch(endianess)
    {
        case LITTLE_ENDIAN:
            return ((value[MSB] << 8) | value[LSB]);
        case BIG_ENDIAN:
            return ((value[MSB] >> 8) | value[LSB]);
        default:
            return 0;
    }
}