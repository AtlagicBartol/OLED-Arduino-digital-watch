#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "rtc.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DISPLAY_ADDR 0x3C

extern Adafruit_SSD1306 display;

void display_init();
void display_show_hr(int hr);
void displayTime(DateTime datetime);
void updateTime();
void display2digits(uint8_t value);

#endif