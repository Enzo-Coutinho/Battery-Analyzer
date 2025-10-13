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
typedef int16_t s16;

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

enum AVARAGE_MODES
{
    AVG_1 = 0b000,
    AVG_4 = 0b001,
    AVG_16 = 0b010,
    AVG_64 = 0b011,
    AVG_128 = 0b100,
    AVG_256 = 0b101,
    AVG_512 = 0b110,
    AVG_1024 = 0b111
};

enum CT_TIMES
{
    _140_US = 0b000,
    _204_US = 0b001,
    _332_US = 0b010,
    _588_US = 0b011,
    _1_1_MS = 0b100,
    _2_116_MS = 0b101,
    _4_156_MS = 0b110,
    _8_244_MS = 0b111
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

#endif