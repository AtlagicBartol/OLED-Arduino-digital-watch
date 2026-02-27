#include "ssd1306.h"
#include "i2c.h"

static uint8_t buffer[OLED_BUFFER_SIZE];

const uint8_t font5x7[][5] = {
    {0x00,0x00,0x00,0x00,0x00}, // space
    {0x7C,0x12,0x11,0x12,0x7C}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
};

static void ssd1306_command(uint8_t cmd)
{
    i2c_start();
    i2c_write(SSD1306_ADDR << 1);
    i2c_write(0x00);
    i2c_write(cmd);
    i2c_stop();
}

void ssd1306_init(void)
{
    ssd1306_command(0xAE);
    ssd1306_command(0xD5); ssd1306_command(0x80);
    ssd1306_command(0xA8); ssd1306_command(0x3F);
    ssd1306_command(0xD3); ssd1306_command(0x00);
    ssd1306_command(0x40);
    ssd1306_command(0x8D); ssd1306_command(0x14);
    ssd1306_command(0x20); ssd1306_command(0x00);
    ssd1306_command(0xA1);
    ssd1306_command(0xC8);
    ssd1306_command(0xDA); ssd1306_command(0x12);
    ssd1306_command(0x81); ssd1306_command(0xCF);
    ssd1306_command(0xD9); ssd1306_command(0xF1);
    ssd1306_command(0xDB); ssd1306_command(0x40);
    ssd1306_command(0xA4);
    ssd1306_command(0xA6);
    ssd1306_command(0xAF);
}

void ssd1306_clear(void)
{
    for (uint16_t i = 0; i < OLED_BUFFER_SIZE; i++)
        buffer[i] = 0x00;
}

void ssd1306_update(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        ssd1306_command(0xB0 + page);
        ssd1306_command(0x00);
        ssd1306_command(0x10);

        i2c_start();
        i2c_write(SSD1306_ADDR << 1);
        i2c_write(0x40);

        for (uint16_t x = 0; x < OLED_WIDTH; x++)
            i2c_write(buffer[page * OLED_WIDTH + x]);

        i2c_stop();
    }
}

void ssd1306_pixel(uint8_t x, uint8_t y, uint8_t color)
{
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT)
        return;

    uint16_t index = x + (y / 8) * OLED_WIDTH;

    if (color)
        buffer[index] |= (1 << (y % 8));
    else
        buffer[index] &= ~(1 << (y % 8));
}

void ssd1306_draw_char(uint8_t x, uint8_t y, char c)
{
    uint8_t index;

    if (c == ' ') index = 0;
    else if (c == 'A') index = 1;
    else if (c == 'B') index = 2;
    else return;

    for (uint8_t i = 0; i < 5; i++) {
        uint8_t line = font5x7[index][i];
        for (uint8_t j = 0; j < 8; j++) {
            ssd1306_pixel(x + i, y + j, line & (1 << j));
        }
    }
}