#include "weather.h"
/*
DODAJ FUNKCIONALNOST DA UKOLIKO NEMA INTERNETA PREKO TOG SSID DA PRELAZI NA DRUGI SSID
*/
WifiInfo wifiInfo = {"****", "*****"};
ApiInfo apiInfo = {"******", "Osijek", "metric"};
WeatherInfo weatherInfo = {"Clear", "0"};

void wifiConnect(){
  WiFi.begin(wifiInfo.ssid, wifiInfo.password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void fetchWeather()
{
    WiFiClientSecure client;
    client.setInsecure(); // skip cert validation

    if (!client.connect("api.openweathermap.org", 443))
    {
        Serial.println("Connection failed");
        return;
    }
    String request = "GET /data/2.5/weather?q=" + apiInfo.city +
                     "&appid=" + apiInfo.apiKey +
                     "&units=" + apiInfo.units +
                     " HTTP/1.1\r\n" +
                     "Host: api.openweathermap.org\r\n" +
                     "User-Agent: ESP32\r\n" +
                     "Connection: close\r\n\r\n";

    client.print(request);

    String payload = "";

    while (client.connected() || client.available())
    {
        if (client.available())
        {
            char c = client.read();
            payload += c;
        }
    }

    client.stop();

    int bodyStart = payload.indexOf("\r\n\r\n");
    if (bodyStart == -1) return;

    payload = payload.substring(bodyStart + 4);

    int tIndex = payload.indexOf("\"temp\":");
    if (tIndex != -1)
    {
        int tEnd = payload.indexOf(",", tIndex);
        String tempStr = payload.substring(tIndex + 7, tEnd);
        weatherInfo.temperature = tempStr + " °C";
    }

    int wIndex = payload.indexOf("\"main\":\"");
    if (wIndex != -1)
    {
        int wEnd = payload.indexOf("\"", wIndex + 8);
        weatherInfo.weather = payload.substring(wIndex + 8, wEnd);
    }

    Serial.println(weatherInfo.temperature);
    Serial.println(weatherInfo.weather);
}
