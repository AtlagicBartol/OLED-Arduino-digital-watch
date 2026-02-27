#include <avr/io.h>
#include "i2c.h"
#include "ssd1306.h"

int main(void)
{
    i2c_init();
    ssd1306_init();
    ssd1306_clear();

    ssd1306_draw_char(10,10, 'A');
    ssd1306_draw_char(17,10, 'B');

    ssd1306_update();

    while (1);
}