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

uint8_t is_connected_ina3221(void)
{
    return (get_manufacturer_id() == DEFAULT_MANUFACTURER_ID && get_die_id() == DEFAULT_DIE_ID);
}

uint16_t get_manufacturer_id(void)
{
    uint8_t _id_buff[2] = {0};
    read_register_ina3221(__ADDR_MANUFCTER_ID, _id_buff);
    return swap_endian(_id_buff, LITTLE_ENDIAN);
}

uint16_t get_die_id(void)
{
    uint8_t _id_buff[2] = {0};
    read_register_ina3221(__ADDR_MANUFCTER_ID, _id_buff);
    return swap_endian(_id_buff, LITTLE_ENDIAN);
}

void get_configuration(configuration_t * configuration)
{
    read_register_ina3221(__ADDR_CONFIGURATION, configuration->u8_configuration);
    configuration->u16_configuration = swap_endian(configuration->u8_configuration, LITTLE_ENDIAN);
}

void set_configuration(configuration_t  *config) {
    configuration_t current_config;
    get_configuration(&current_config);

    config->u16_configuration |= current_config.u16_configuration;

    swap_endian(config->u8_configuration, BIG_ENDIAN);

    write_register_ina3221(__ADDR_CONFIGURATION, config->u8_configuration);
}

void get_shunt_voltage(enum CHANNEL channel, shunt_voltage_t* shunt_voltage)
{
    uint8_t reg = 0;
    switch(channel)
    {
        case CHANNEL_1:
            reg = __ADDR_CH1_SV;
            break;
        case CHANNEL_2:
            reg = __ADDR_CH2_SV;
            break;
        case CHANNEL_3:
            reg = __ADDR_CH2_SV;
            break;
        default:
            return;
    }
    read_register_ina3221(reg, shunt_voltage->u8_shunt_voltage);
    shunt_voltage->u16_shunt_voltage = swap_endian(shunt_voltage->u8_shunt_voltage, LITTLE_ENDIAN);
}

void read_register_ina3221(uint8_t reg, uint8_t *data) {
    i2c_read(INA3221_ADDRESS, reg, data, 2);
}

void write_register_ina3221(uint8_t reg, const uint8_t *data) {
    const uint8_t buffer[3] = {reg, data[0], data[1]};
    i2c_write(INA3221_ADDRESS, buffer, 3);
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