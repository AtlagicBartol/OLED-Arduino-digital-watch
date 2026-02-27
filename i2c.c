#include <avr/io.h>
#include "i2c.h"

#define F_CPU 16000000UL
#define SCL_FREQ 100000UL

void i2c_init(void)
{
    TWSR = 0x00;
    TWBR = ((F_CPU / SCL_FREQ) - 16) / 2;
    TWCR = (1 << TWEN);
}

void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}