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

    defaultInitINA3221();

    setShuntOffset(get_shunt_voltage(CHANNEL_2));

    float previousInternalResistance = 0.0f;

    const float maxBatteryCharge_Ah = 3.0; // 3000Ah

    while (true) {

        float busVoltage[3] = {0.0f};
        float shuntVoltage[3] = {0.0f};
        float current[3] = {0.0f};
        float resistance[3] = {390.1f, 1000.1f, 0.0f};
        float voltageDrop[3] = {0.0f};


        for(int i=CHANNEL_1; i<=CHANNEL_3; i++)
        {
            busVoltage[i] = get_bus_voltage(i);
            shuntVoltage[i] = get_shunt_voltage(i);
            current[i] = getCurrent(i);

            voltageDrop[i] = resistance[i] * current[i];

            printf("Bus voltage (V) on channel %d: %lf\n", i + 1, busVoltage[i]);
            printf("Shunt voltage (mV) on channel %d: %lf\n", i + 1, shuntVoltage[i] * 1000);
            printf("Current (mA) on channel %d: %lf\n", i + 1, current[i] * 1000);
            printf("Voltage Drop across channel %d: %lf\n", i + 1, voltageDrop[i]);
        }
        
        float internalBatteryResistance = (busVoltage[CHANNEL_2] - voltageDrop[CHANNEL_1]) / current[CHANNEL_1];
        printf("Internal Resistance (ohm): %lf\n", internalBatteryResistance);

        sleep_ms(1000);
    }
}
