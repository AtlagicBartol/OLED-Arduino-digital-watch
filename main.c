#include <avr/io.h>
#include "i2c.h"
#include "ssd1306.h"

int main(void)
{
    i2c_init();
    ssd1306_init();
    ssd1306_clear();

    for (uint8_t i = 0; i < 20; i++)
        ssd1306_pixel(10 + i, 10, 1);

    ssd1306_update();

    while (1);
}