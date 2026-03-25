#ifndef RTC_H
#define RTC_H

#include <Wire.h>
#include <stdint.h>

#define DS3231_ADDR 0x68

struct DateTime {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

void rtc_init();
void rtc_read(DateTime* dt);
void rtc_set(DateTime* dt);

#endif