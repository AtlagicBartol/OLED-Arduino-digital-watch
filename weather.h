#ifndef WEATHER_H
#define WEATHER_H

#include <WiFi.h>

struct WifiInfo{
  char* ssid;
  char* password;
};

struct ApiInfo{
  String apiKey;
  String city;
  String units;
};

struct WeatherInfo{
  String weather;
  String temperature;
};

extern WifiInfo wifiInfo;
extern ApiInfo apiInfo;
extern WeatherInfo weatherInfo;


void wifiConnect();
void fetchWeather();
void displayWeather();

#endif