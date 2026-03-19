#ifndef WEATHERDISPLAY_H
#define WEATHERDISPLAY_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// extern unsigned char rainIcon[] = {
// 	0xff, 0xff, 0xf0, 0x3f, 0xe7, 0x9f, 0xef, 0xc3, 0xdf, 0xfd, 0xbf, 0xfd, 0xbf, 0xfd, 0xbf, 0xfd, 
// 	0xbf, 0xfd, 0xcf, 0xe3, 0xf0, 0x0f, 0xff, 0xff, 0xed, 0xb7, 0xff, 0xff, 0xf6, 0xdf, 0xff, 0xff
// };

int stringLength(String word);
String convertTemperature();
int startLocation(String word, int pixels);
void displayLocation();
void displayTemperature();
void displayWeather();

//void displayIcon(); ZA BUDUCE UNAPRIJEĐENJE

#endif