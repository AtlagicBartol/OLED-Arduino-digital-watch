#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <stdint.h>

#define MPU_ADDR 0x69
extern int16_t ax,ay,az;
extern int steps;

void mpu_init();
void mpu_read(int16_t* ax, int16_t* ay, int16_t* az);
float getMagnitude(int16_t ax, int16_t ay, int16_t az);
float lowPass(float input);
void detectStep(float value);
int mpu_getSteps();

#endif