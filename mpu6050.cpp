#include "mpu6050.h"
#include <math.h>

int16_t ax,ay,az;
int steps = 0;
bool stepReady = true;


float filtered = 0;

void mpu_init(){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void mpu_read(int16_t* ax, int16_t* ay, int16_t* az){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) {
    return;
  }

  Wire.requestFrom(MPU_ADDR, 6, true);

  if (Wire.available() < 6) {
    return;
  }

  *ax = Wire.read() << 8 | Wire.read();
  *ay = Wire.read() << 8 | Wire.read();
  *az = Wire.read() << 8 | Wire.read();
}

float getMagnitude(int16_t ax, int16_t ay, int16_t az){
  return sqrtf((float)ax*ax + (float)ay*ay + (float)az*az);
}

float lowPass(float input){
  float alpha = 0.1;
  filtered = alpha * input + (1-alpha) * filtered;
  return filtered;
}

void detectStep(float value){
  float thresholdHigh = 16500;
  float thresholdLow = 14000;
  if(value >thresholdHigh && stepReady){
    steps++;
    stepReady = false;
  }
  if(value < thresholdLow){
    stepReady = true;
  }
}

int mpu_getSteps(){
  mpu_read(&ax,&ay,&az);

  float mag = getMagnitude(ax,ay,az);
  float filt = lowPass(mag);
  detectStep(filt);

  return steps;
}


