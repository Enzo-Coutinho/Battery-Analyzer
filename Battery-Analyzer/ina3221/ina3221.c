#include "ina3221.h"
#include <math.h>

// Private functions

uint16_t get_configuration(void);
void set_configuration(configuration_t* configuration);

uint16_t read_register_ina3221(const uint8_t reg);
void write_register_ina3221(const uint8_t reg, const uint16_t data);

// Private variables

const uint8_t INA3221_ADDRESS = INA3221_I2C_ADDRESS_GND;

static bus_voltage_t bus_voltage = {.s16_bus_voltage = 0};
static shunt_voltage_t shunt_voltage = {.s16_shunt_voltage = 0};
static configuration_t configuration = {.u16_configuration = 0};

float _shunt_resistors[3] = {0.1, 0.1, 0.1}; // Placeholder for shunt resistors

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

    
}

float getCurrent(enum CHANNEL channel)
{
    float shuntVoltage = get_shunt_voltage(channel);
    if(isnan(shuntVoltage)) return NAN;

    return shuntVoltage / _shunt_resistors[channel];
}

uint16_t get_manufacturer_id(void)
{
    return read_register_ina3221(__ADDR_MANUFCTER_ID);
}

uint16_t get_die_id(void)
{
    return read_register_ina3221(__ADDR_MANUFCTER_ID);
}

uint16_t get_configuration(void)
{
    return read_register_ina3221(__ADDR_CONFIGURATION);
}

void set_configuration(configuration_t  * config) {
    config->u16_configuration |= get_configuration();
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
            reg = __ADDR_CH2_SV;
            break;
        default:
            return NAN;
    }
    shunt_voltage.s16_shunt_voltage = read_register_ina3221(reg);
    return (shunt_voltage.s16_shunt_voltage >> 3) * 40e-6;
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
            reg = __ADDR_CH2_BV;
            break;
        default:
            return NAN;
    }
    bus_voltage.s16_bus_voltage = read_register_ina3221(reg);
    return (bus_voltage.s16_bus_voltage >> 3) * 8e-3;
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