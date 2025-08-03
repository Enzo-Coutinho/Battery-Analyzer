#ifndef REGISTER_MAP_H
#define REGISTER_MAP_H

#include <inttypes.h>

#define DEFAULT_CONFIGURATION 0x7127
#define DEFAULT_SHUNT_VOLTAGE 0x00
#define DEFAULT_BUS_VOLTAGE 0x00
#define DEFAULT_MANUFACTURER_ID 0x5449
#define DEFAULT_DIE_ID 0x3220

#define INA3221_I2C_ADDRESS_GND 0x40 // Default I2C address for INA3221

#define MSB 0
#define LSB 1

typedef uint8_t u8;
typedef uint16_t u16;

enum REGISTERS_ADDRESS {
    __ADDR_CONFIGURATION = 0x00,
    __ADDR_CH1_SV = 0x01,
    __ADDR_CH1_BV = 0x02,
    __ADDR_CH2_SV = 0x03,
    __ADDR_CH2_BV = 0x04,
    __ADDR_CH3_SV = 0x05,
    __ADDR_CH3_BV = 0x06,
    __ADDR_CH1_CA = 0x07,
    __ADDR_CH1_WA = 0x08,
    __ADDR_CH2_CA = 0x09,
    __ADDR_CH2_WA = 0x0A,
    __ADDR_CH3_CA = 0x0B,
    __ADDR_CH3_WA = 0x0C,
    __ADDR_SV_SUM = 0x0D,
    __ADDR_SV_SUM_LIM = 0x0E,
    __ADDR_MASK = 0x0F,
    __ADDR_PW_V_UP_LIM = 0x10,
    __ADDR_PW_V_LW_LIM = 0x11,
    __ADDR_MANUFCTER_ID = 0xFE,
    __ADDR_DIE_ID = 0xFF
};

typedef union
{
    struct configuration
    {
        u8 _modes : 3;
        u8 _vsh_ct : 3;
        u8 _vbus_ct : 3;
        u8 _avg_mode : 3;
        u8 _ch1 : 1;
        u8 _ch2 : 1;
        u8 _ch3 : 1;
        u8 _rst : 1;
    } configuration_bitmap;
    u16 u16_configuration;
} configuration_t;

typedef union
{
    struct shunt_voltage
    {
        u8 : 3;
        u16 _data : 12;
        u8 _sign : 1;
    } shunt_voltage_bitmap;
    u16 u16_shunt_voltage;
} shunt_voltage_t;

typedef union
{
    struct bus_voltage
    {
        u8 : 3;
        u16 _data : 12;
        u8 _sign : 1;
    } bus_voltage_bitmap;
    u16 u16_bus_voltage;
} bus_voltage_t;

#endif