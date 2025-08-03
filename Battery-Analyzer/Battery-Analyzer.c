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

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
