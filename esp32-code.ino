#include <Arduino.h>
#include <Wire.h>
#include <time.h>

#include "display.h"
#include "heartrate.h"
#include "weather.h"
#include "weatherDisplay.h"
#include "rtc.h"
#include "mpu6050.h"

#define SDA_PIN 21
#define SCL_PIN 22

int stepsCounter = 0;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;


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

    mpu_init();
    heartrate_init();

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;

    
    if (getLocalTime(&timeinfo))
    {
        DateTime setTime = {
            (uint8_t)timeinfo.tm_sec,
            (uint8_t)timeinfo.tm_min,
            (uint8_t)timeinfo.tm_hour - 1,
            (uint8_t)timeinfo.tm_mday,
            (uint8_t)(timeinfo.tm_mon + 1),
            (uint16_t)(timeinfo.tm_year + 1900)
        };

        rtc_set(&setTime);
    }
}

void loop()
{
    rtc_read(&now);
    if(now.seconds % 10 >= 5){
        displayWeather();
    }
    else{
        displayTime(now);
    }
    
    stepsCounter = mpu_getSteps();

    mpu_read(&ax,&ay,&az);

    float mag = getMagnitude(ax,ay,az);
    float filtered = lowPass(mag);
    Serial.println(filtered);
    Serial.println(steps);
    delay(50);
}
