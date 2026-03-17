#include "heartrate.h"

void writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MAX30101_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void heartrate_init()
{
    writeRegister(0x09, 0x03); // SpO2 mode
    writeRegister(0x0A, 0x27); // sample rate
    writeRegister(0x0C, 0x24); // LED pulse amplitude
}
uint32_t readIR()
{
    Wire.beginTransmission(MAX30101_ADDR);
    Wire.write(0x07); // FIFO data register
    Wire.endTransmission();

    Wire.requestFrom(MAX30101_ADDR, 3);

    uint32_t value = 0;

    if(Wire.available() >= 3)
    {
        value = Wire.read();
        value <<= 8;
        value |= Wire.read();
        value <<= 8;
        value |= Wire.read();
        }

    value &= 0x03FFFF;

    return value;
}

int heartrate_read()
{
    return readIR();
}