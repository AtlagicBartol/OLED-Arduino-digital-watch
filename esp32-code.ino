#include <Arduino.h>
#include <Wire.h>

#include "display.h"
#include "heartrate.h"

#define SDA_PIN 21
#define SCL_PIN 22

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    display_init();
    heartrate_init();

    display_show_text("Starting...");
}

void loop()
{
    int hr = heartrate_read();

    Serial.println(hr);

    display_show_hr(hr);

    delay(1000);
}