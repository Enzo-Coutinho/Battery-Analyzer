#include "ina3221.h"
#include <math.h>

// Private functions

uint16_t get_configuration(void);
void set_configuration(configuration_t* configuration);

uint16_t read_register_ina3221(const uint8_t reg);
void write_register_ina3221(const uint8_t reg, const uint16_t data);

// Private variables

const uint8_t INA3221_ADDRESS = INA3221_I2C_ADDRESS_GND;

static configuration_t configuration = {.u16_configuration = 0};

float _shunt_resistors[3] = {0.1, 0.1, 0.1}; // Placeholder for shunt resistors

float shunt_voltage_offset = 0.0f;

void resetINA3221(void) {
    configuration_t configuration = {.configuration_bitmap = {._rst = 1}};
    set_configuration(&configuration);
}

bool isConnectedINA3221(void)
{
    return (get_manufacturer_id() == DEFAULT_MANUFACTURER_ID && get_die_id() == DEFAULT_DIE_ID);
}

void defaultInitINA3221(void)
{
    configuration.configuration_bitmap._ch1 = 1;
    configuration.configuration_bitmap._ch2 = 1;
    configuration.configuration_bitmap._ch3 = 1;

    configuration.configuration_bitmap._avg_mode = AVG_1024;

    configuration.configuration_bitmap._vbus_ct = _8_244_MS;
    configuration.configuration_bitmap._vsh_ct = _8_244_MS;

    configuration.configuration_bitmap._modes = 0b111;

    set_configuration(&configuration);
}

float getCurrent(enum CHANNEL channel)
{
    float shuntVoltage = get_shunt_voltage(channel);
    if(isnan(shuntVoltage)) return NAN;

    return (shuntVoltage) / _shunt_resistors[channel];
}

void setShuntOffset(float offset)
{
    shunt_voltage_offset = offset;
}

uint16_t get_manufacturer_id(void)
{
    return read_register_ina3221(__ADDR_MANUFCTER_ID);
}

uint16_t get_die_id(void)
{
    return read_register_ina3221(__ADDR_DIE_ID);
}

uint16_t get_configuration(void)
{
    return read_register_ina3221(__ADDR_CONFIGURATION);
}

void set_configuration(configuration_t  * config) {
    write_register_ina3221(__ADDR_CONFIGURATION, config->u16_configuration);
}

float get_shunt_voltage(enum CHANNEL channel)
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
            reg = __ADDR_CH3_SV;
            break;
        default:
            return NAN;
    }
    int16_t shunt_voltage = read_register_ina3221(reg);
    return ((shunt_voltage >> 3) * 40e-6) - shunt_voltage_offset;
}

float get_bus_voltage(enum CHANNEL channel)
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
            reg = __ADDR_CH3_BV;
            break;
        default:
            return NAN;
    }
    int16_t bus_voltage = read_register_ina3221(reg);
    return (bus_voltage >> 3) * 8e-3;
}

uint16_t read_register_ina3221(const uint8_t reg) {
    uint8_t buffer[2];
    i2c_read(INA3221_ADDRESS, reg, buffer, 2);
    return ((buffer[0] << 8) | buffer[1]);
}

void write_register_ina3221(const uint8_t reg, const uint16_t data) {
    const uint8_t buffer[3] = {reg, (uint8_t)((data >> 8) & 0xFF), (uint8_t)(data & 0xFF)};
    i2c_write(INA3221_ADDRESS, buffer, 3);
}