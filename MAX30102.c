#include "max30102.h"
#include "i2c.h"
#include <util/delay.h>


void max30102_init(void)
{
    max30102_reset();

    // FIFO Configuration
    max30102_write_reg(0x08, 0x4F);   // sample avg=4, FIFO rollover enabled

    // Mode Configuration
    max30102_write_reg(0x09, 0x03);   // SpO2 mode

    // SpO2 Configuration
    max30102_write_reg(0x0A, 0x27);   // 100Hz, 411us pulse width

    // LED Pulse Amplitude
    max30102_write_reg(0x0C, 0x24);   // RED LED current
    max30102_write_reg(0x0D, 0x24);   // IR LED current

    // Clear FIFO pointers
    max30102_write_reg(0x04, 0x00);
    max30102_write_reg(0x05, 0x00);
    max30102_write_reg(0x06, 0x00);
}

void max30102_write_reg(uint8_t reg, uint8_t value)
{
    i2c_start();
    i2c_write(MAX30102_ADDR << 1);  // write
    i2c_write(reg);
    i2c_write(value);
    i2c_stop();
}

uint8_t max30102_read_reg(uint8_t reg)
{
    uint8_t value;

    i2c_start();
    i2c_write(MAX30102_ADDR << 1);   // write
    i2c_write(reg);

    i2c_start();                    // repeated start
    i2c_write((MAX30102_ADDR << 1) | 1);  // read

    value = i2c_read_nack();
    i2c_stop();

    return value;
}

void max30102_reset(void)
{
    max30102_write_reg(0x09, 0x40);   // MODE_CONFIG reset bit
    _delay_ms(100);
}

void max30102_read_fifo(uint32_t *ir, uint32_t *red)
{
    uint8_t data[6];

    i2c_start();
    i2c_write(MAX30102_ADDR << 1);
    i2c_write(0x07);   // FIFO_DATA register

    i2c_start();
    i2c_write((MAX30102_ADDR << 1) | 1);

    for (int i = 0; i < 5; i++)
        data[i] = i2c_read_ack();

    data[5] = i2c_read_nack();

    i2c_stop();

    *red = ((uint32_t)data[0] << 16) |
           ((uint32_t)data[1] << 8)  |
            data[2];

    *ir  = ((uint32_t)data[3] << 16) |
           ((uint32_t)data[4] << 8)  |
            data[5];

    *red &= 0x03FFFF;  // 18-bit mask
    *ir  &= 0x03FFFF;
}