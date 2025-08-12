#include <stdio.h>
#include "ina3221/ina3221.h"

const unsigned int buttonSingleShoot = 12;

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

    gpio_init(buttonSingleShoot);

    gpio_set_dir(buttonSingleShoot, GPIO_IN);

    gpio_pull_up(buttonSingleShoot);

    init_i2c_comm();

    awaitConnectionOfINA3221();

    resetINA3221();

    awaitConnectionOfINA3221();

    defaultInitINA3221();

    setShuntOffset(0.0f / 1000.0f);

    bool previousButtonSingleShot = false;
    bool activeReadOperation = false;
    unsigned int countReads = 0U;

    float busVoltage[3] = {0.0f};
    float shuntVoltage[3] = {0.0f};
    float current[3] = {0.0f};

    while (true) {
        if(gpio_get(buttonSingleShoot) && !previousButtonSingleShot) activeReadOperation = !activeReadOperation;
        if(activeReadOperation)
        {
            busVoltage[countReads] = get_bus_voltage(countReads);
            shuntVoltage[countReads] = get_shunt_voltage(countReads);
            current[countReads] = getCurrent(countReads);

            printf("CH %d: bus V = %.6f V, shunt = %.6f mV, I = %.6f mA\n",
                countReads+1, busVoltage[countReads], shuntVoltage[countReads]*1000.0f, current[countReads]*1000.0f);

            ++countReads;
            activeReadOperation = false;
        }
        if(countReads == 2)
        {
            countReads = 0;
            float internalBatteryResistance = ((busVoltage[CHANNEL_1] + shuntVoltage[CHANNEL_1]) - (busVoltage[CHANNEL_2])) / current[CHANNEL_2];
            printf("Internal Resistance (ohm): %lf\n", internalBatteryResistance);
        }
        sleep(50);
    }
}
