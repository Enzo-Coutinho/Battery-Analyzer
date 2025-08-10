#include <stdio.h>
#include "ina3221/ina3221.h"

void awaitConnectionOfINA3221()
{
    do
    {
        sleep_ms(500);
        printf("ID: %d\n", get_manufacturer_id());
        printf("Die ID: %d\n", get_die_id());
    } while (!isConnectedINA3221());
}

int main()
{
    stdio_init_all();

    init_i2c_comm();

    awaitConnectionOfINA3221();

    resetINA3221();

    awaitConnectionOfINA3221();

    //defaultInit3221();

    while (true) {
        float busVoltage1 = get_bus_voltage(CHANNEL_1);
        float busVoltage2 = get_bus_voltage(CHANNEL_2);
        float busVoltage3 = get_bus_voltage(CHANNEL_3);
        
        float shuntVoltage1 = get_shunt_voltage(CHANNEL_1);
        float shuntVoltage2 = get_shunt_voltage(CHANNEL_2);
        float shuntVoltage3 = get_shunt_voltage(CHANNEL_3);

        float current1 = getCurrent(CHANNEL_1);
        float current2 = getCurrent(CHANNEL_2);
        float current3 = getCurrent(CHANNEL_3);

        printf("Bus voltage on channel 1: %lf\n", busVoltage1);
        printf("Bus voltage on channel 2: %lf\n", busVoltage2);
        printf("Bus voltage on channel 3: %lf\n", busVoltage3);

        printf("Shunt voltage on channel 1: %lf\n", shuntVoltage1);
        printf("Shunt voltage on channel 2: %lf\n", shuntVoltage2);
        printf("Shunt voltage on channel 3: %lf\n", shuntVoltage3);

        printf("Current on channel 1: %lf\n", current1);
        printf("Current on channel 2: %lf\n", current2);
        printf("Current on channel 3: %lf\n", current3);

        sleep_ms(1000);
    }
}
