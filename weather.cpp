#include "weather.h"

WifiInfo wifiInfo = {"Extender", "m63F4B5dnn"};
ApiInfo apiInfo = {"cc815ce3b0ea75b779e8377a62fbf334", "Osijek", "metric"};
WeatherInfo weatherInfo = {"Clear", "0"};

void wifiConnect(){
  Wifi.begin(wifiInfo.ssid, wifiInfo.password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void fetchWeather() {
  WiFiClientSecure client;

  client.setInsecure();

  client.connect("api.openweathermap.org", 443); // ovo malo prouci

  if (client.connect("api.openweathermap.org", 80)) {
    client.println("GET /data/2.5/weather?q=" + apiInfo.city + "&appid=" + apiInfo.apiKey + "&units=" + apiInfo.units + " HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();

    String payload = "";
    unsigned long timeout = millis();
    
    while (client.connected() && millis() - timeout < 5000) {
      while (client.available()) {
        char c = client.read();
        payload += c;
      }
    }
    client.stop();

    int bodyStart = payload.indexOf("\r\n\r\n");
    if (bodyStart == -1) return;
    payload = payload.substring(bodyStart + 4);

    int tIndex = payload.indexOf("\"temp\":");
    if (tIndex != -1) {
      int tEnd = payload.indexOf(",", tIndex);
      String tempStr = payload.substring(tIndex + 7, tEnd);
      weatherInfo.temperature = tempStr + " °C";
    }

    int wIndex = payload.indexOf("\"main\":\"");
    if (wIndex != -1) {
      int wEnd = payload.indexOf("\"", wIndex + 8);
      weatherInfo.weather = payload.substring(wIndex + 8, wEnd);
    }
  }
}