#ifndef INA3221_H
#define INA3221_H

#include "i2c/i2c_driver.h"
#include "register_map.h"

enum CHANNEL {
    CHANNEL_1 = 0,
    CHANNEL_2 = 1,
    CHANNEL_3 = 2
};

void reset_ina3221(void);
uint8_t is_connected_ina3221(void);

uint16_t get_manufacturer_id(void);
uint16_t get_die_id(void);

void get_configuration(configuration_t* configuration);
void set_configuration(configuration_t* configuration);

void get_shunt_voltage(enum CHANNEL channel, shunt_voltage_t* shunt_voltage);
void get_bus_voltage(enum CHANNEL channel, bus_voltage_t* bus_voltage);


uint16_t get_current(enum CHANNEL channel);

void read_register_ina3221(uint8_t reg, uint8_t *data);
void write_register_ina3221(uint8_t reg, const uint8_t *data);

#endif