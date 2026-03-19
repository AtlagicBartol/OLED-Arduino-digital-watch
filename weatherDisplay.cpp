#include "weatherDisplay.h"
#include "weather.h"
#include "display.h"
/*
DODAJ IKONE ZA RAZLIČITE TIPOVE VREMENA
DODAJ DA SE ISPISUJE °C, A NE SAMO C
PREBACI BOLJE DA CONVERTAS STRING TEMPERATURE ODMAH ČIM GA PRIMIŠ
*/

void displayWeather(){
  display.clearDisplay();
  displayTemperature();
  displayLocation();
  display.display();
}

void displayTemperature(){
  int n = 2;
  display.setTextSize(n);
  String temperature = convertTemperature();
  display.setCursor( startLocation(temperature, n), 24);
  display.print(temperature);
}

String convertTemperature(){
  String temperature = "";
  for(int i = 0; weatherInfo.temperature[i] != ' ';i++){
    temperature += weatherInfo.temperature[i];
  }
  return temperature + " C";
}

void displayLocation(){
  int n = 1;
  display.setTextSize(1);
  display.setCursor(SCREEN_WIDTH - (stringLength(apiInfo.city) * n * 6) , 0);
  display.print(apiInfo.city);
}

int startLocation(String word, int pixels){
  int letters = stringLength(word) * pixels * 6;
  return (SCREEN_WIDTH - letters) / 2;
}

int stringLength(String word){
  int counter = 0;
  for(int i = 0; word[i] != '\0'; i++){
    counter++;
  }
  return counter;
}