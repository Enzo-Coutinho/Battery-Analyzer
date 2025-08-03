#include "ina3221.h"

float _shunt_resistors[3] = {0.1, 0.1, 0.1}; // Placeholder for shunt resistors

const uint8_t INA3221_ADDRESS = INA3221_I2C_ADDRESS_GND;

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
    return read_register_ina3221(__ADDR_MANUFCTER_ID);
}

uint16_t get_die_id(void)
{
    return read_register_ina3221(__ADDR_MANUFCTER_ID);
}

void get_configuration(configuration_t * configuration)
{
    configuration->u16_configuration = read_register_ina3221(__ADDR_CONFIGURATION);
}

void set_configuration(configuration_t  *config) {
    uint16_t set_config = config->u16_configuration;
    get_configuration(config);

    config->u16_configuration |= set_config;

    write_register_ina3221(__ADDR_CONFIGURATION, config->u16_configuration);
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
    shunt_voltage->u16_shunt_voltage = read_register_ina3221(reg);
}

void get_bus_voltage(enum CHANNEL channel, bus_voltage_t* bus_voltage)
{
    uint8_t reg = 0;
    switch(channel)
    {
        case CHANNEL_1:
            reg = __ADDR_CH1_BV;
            break;
        case CHANNEL_2:
            reg = __ADDR_CH2_BV;
            break;
        case CHANNEL_3:
            reg = __ADDR_CH2_BV;
            break;
        default:
            return;
    }
    bus_voltage->u16_bus_voltage = read_register_ina3221(reg);
}

uint16_t read_register_ina3221(const uint8_t reg) {
    uint8_t buffer[2];
    i2c_read(INA3221_ADDRESS, reg, buffer, 2);
    return (buffer[0] << 8 | buffer[1]);
}

void write_register_ina3221(const uint8_t reg, const uint16_t data) {
    const uint8_t buffer[3] = {reg, (uint8_t)((data >> 8) & 0xFF), (uint8_t)(data & 0xFF)};
    i2c_write(INA3221_ADDRESS, buffer, 3);
}