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

    setShuntOffset(0.0f / 1000.0f);

    while (true) {
        float busVoltage[3] = {0.0f};
        float shuntVoltage[3] = {0.0f};
        float current[3] = {0.0f};

        for(int i=CHANNEL_1; i<=CHANNEL_3; i++)
        {
            busVoltage[i] = get_bus_voltage(i);
            shuntVoltage[i] = get_shunt_voltage(i);
            current[i] = getCurrent(i);

            printf("CH %d: bus V = %.6f V, shunt = %.6f mV, I = %.6f mA\n",
                i+1, busVoltage[i], shuntVoltage[i]*1000.0f, current[i]*1000.0f);
        }
        
        float internalBatteryResistance = ((busVoltage[CHANNEL_1] + shuntVoltage[CHANNEL_1]) - (busVoltage[CHANNEL_2] - shuntVoltage[CHANNEL_2])) / current[CHANNEL_2];
        printf("Internal Resistance (ohm): %lf\n", internalBatteryResistance);



        sleep_ms(1000);
    }
}
