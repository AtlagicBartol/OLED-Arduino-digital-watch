#include <Arduino.h>
#include <Wire.h>

#include "display.h"
#include "heartrate.h"
#include "weather.h"
#include "weatherDisplay.h"
#include "rtc.h"

#define SDA_PIN 21
#define SCL_PIN 22


unsigned long lastDisplay = 0;

DateTime now;

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);
    wifiConnect();

    fetchWeather();

    display_init();

    rtc_init();

    DateTime setTime = {12, 30, 14, 25, 3, 2026};
    rtc_set(&setTime);
    //heartrate_init();
}

void loop()
{
    //int hr = heartrate_read();

    rtc_read(&now);

    displayTime(now);

    //Serial.println(hr);

    //display_show_hr(hr);
    delay(20);
}