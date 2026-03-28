#include "rtc.h"

uint8_t bcdToDec(uint8_t val)
{
    return (val >> 4) * 10 + (val & 0x0F);
}

uint8_t decToBcd(uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

void rtc_init()
{
    Wire.begin();
}

void rtc_read(DateTime* dt){
  Wire.beginTransmission(DS3231_ADDR);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDR,7);

  dt->seconds = bcdToDec(Wire.read() & 0x7F);
  dt->minutes = bcdToDec(Wire.read());
  dt->hours = bcdToDec(Wire.read() & 0x3F);

  Wire.read();

  dt->day = bcdToDec(Wire.read());
  dt->month = bcdToDec(Wire.read() & 0x1F);
  dt->year = 2000 + bcdToDec(Wire.read());
}

void rtc_set(DateTime* dt)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x00);

    Wire.write(decToBcd(dt->seconds));
    Wire.write(decToBcd(dt->minutes));
    Wire.write(decToBcd(dt->hours));
    Wire.write(0); // Postavaljas dan (pon itd.)
    Wire.write(decToBcd(dt->day));
    Wire.write(decToBcd(dt->month));
    Wire.write(decToBcd(dt->year - 2000));

    Wire.endTransmission();
}