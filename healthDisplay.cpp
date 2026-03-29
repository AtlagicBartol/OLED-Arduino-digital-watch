#include "HealthDisplay.h"
#include "mpu6050.h"
#include "display.h"

void display_show_hr(int hr)
{
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Heart Rate");

    display.setTextSize(3);
    display.setCursor(0,30);
    display.print(hr);
    display.println(" BPM");

    display.display();
}

void displaySteps(){
  display.clearDisplay();

  uint8_t startingPointString = calculateStartingPoint() + numberOfDigits(steps) * 12;

  display.setTextSize(2);
  display.setCursor(calculateStartingPoint() ,24);
  display.print(steps);
  display.setTextSize(1);
  display.setCursor(startingPointString, 30);
  display.print(" steps");

  display.display();
}

int numberOfDigits(int number){
  if (number == 0) return 1;

  int counter = 0;
  while(number != 0){
    number = number / 10;
    counter++;
  }
  return counter;
}

int calculateStartingPoint(){
  return (92 - numberOfDigits(steps) * 12) / 2;
}