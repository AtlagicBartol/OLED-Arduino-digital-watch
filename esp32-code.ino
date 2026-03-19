#include <Arduino.h>
#include <Wire.h>

#include "display.h"
#include "heartrate.h"
#include "weather.h"
#include "weatherDisplay.h"

#define SDA_PIN 21
#define SCL_PIN 22


unsigned long lastDisplay = 0;

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);
    wifiConnect();

    fetchWeather();

    display_init();
    //heartrate_init();
}

void loop()
{
    //int hr = heartrate_read();

    if(millis() - lastDisplay >= 1000){
        lastDisplay = millis();
        updateTime();
        //displayTime();
        displayWeather();
    }

    //Serial.println(hr);

    //display_show_hr(hr);

    delay(1000);
}