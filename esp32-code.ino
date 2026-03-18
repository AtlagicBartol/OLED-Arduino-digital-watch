#include <Arduino.h>
#include <Wire.h>

#include "display.h"
#include "heartrate.h"
#include "weather.h"

#define SDA_PIN 21
#define SCL_PIN 22


unsigned long lastDisplay = 0;

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);
    wifi_connect();

    display_init();
    //heartrate_init();

    display_show_text("Starting...");
}

void loop()
{
    //int hr = heartrate_read();

    if(millis() - lastDisplay >= 1000){
        lastDisplay = millis();
        updateTime();
        displayTime();
    }

    //Serial.println(hr);

    //display_show_hr(hr);

    delay(1000);
}