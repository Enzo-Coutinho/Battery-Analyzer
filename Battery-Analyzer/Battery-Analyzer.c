#include <stdio.h>
#include "ina3221/ina3221.h"

int main()
{
    stdio_init_all();

    init_i2c_comm();

    do
    {
        sleep_ms(500);
        printf("ID: %d", get_manufacturer_id());
        printf("Die ID: %d", get_die_id());
    } while (!is_connected_ina3221());

    reset_ina3221();

    sleep_ms(100);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
