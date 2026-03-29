#ifndef HEALTHDISPLAY_H
#define HEALTHDISPLAY_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void display_show_hr(int hr);
void displaySteps();
int numberOfDigits(int number);
int calculateStartingPoint();

#endif