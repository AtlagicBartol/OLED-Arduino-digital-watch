#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DISPLAY_ADDR 0x3C

extern Adafruit_SSD1306 display;

struct Datetime{
  uint8_t hour;
  uint8_t minutes;
  uint8_t seconds;

  uint8_t day;
  uint8_t month;
  uint16_t year;
};

extern Datetime datetime;

void display_init();
void display_show_text(const char* text);
void display_show_hr(int hr);
void displayTime();
void updateTime();
void display2digits(uint8_t value);

#endif