#ifndef HEARTRATE_H
#define HEARTRATE_H

#define MAX30101_ADDR 0x57

#include <Wire.h>

void heartrate_init();
int heartrate_read();

#endif