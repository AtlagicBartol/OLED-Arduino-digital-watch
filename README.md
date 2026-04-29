# ⌚ ESP32 OLED Digital Watch

An embedded digital watch built using the ESP32 microcontroller and a 128x64 OLED display. The project integrates multiple hardware modules including RTC, sensors, and WiFi-based services to create a multifunctional smart watch system.

---

## 🌿 Branches

This repository contains two different implementations of the project:

- **main branch** → Arduino Uno version (register-level / AVR-based implementation)  
- **esp32-version branch** → ESP32 version with extended features (WiFi, API, sensors)  

The ESP32 version includes significantly more functionality such as weather data, NTP synchronization, and improved modular architecture.

---
## 📌 Features

- 🕒 Real-time clock using DS3231 RTC module  
- 🌐 Time synchronization via NTP (WiFi)  
- 🌤️ Weather data fetching using OpenWeather API  
- 📟 OLED display (SSD1306 128x64)  
- 🚶 Motion detection / step tracking (MPU6050)  
- 🔄 Multiple display modes (time, weather, sensors)  
- 🔌 I2C communication with multiple devices  

---

## 🧠 System Architecture

The system is modular and organized into separate components:

- **Display module** – handles rendering on OLED  
- **RTC module** – manages timekeeping  
- **Weather module** – fetches data from API  
- **Main application** – controls logic and display switching  

---

## 🔧 Functionality

### ⏱️ Time Management
- Uses DS3231 RTC for accurate timekeeping  
- Optional synchronization via NTP server  

### 🌤️ Weather Integration
- Fetches weather data using HTTP requests  
- Parses temperature and conditions manually  

### 📊 Sensor Processing
- Accelerometer data filtering (low-pass filter)  
- Basic step detection algorithm  
- Heart rate raw data acquisition  

### 📺 Display
- Text rendering with dynamic positioning  
- Centering and formatting  
- Multiple UI states  

---

## 🛠️ Technologies Used

- C/C++ (Arduino framework)  
- ESP32 (WiFi-enabled microcontroller)  
- I2C communication  
- REST API (OpenWeather)  
- Embedded systems design  

## 🚀 Getting Started

### Hardware Requirements

- ESP32 or Arduino
- SSD1306 OLED display (128x64)  
- DS3231 RTC module  
- MPU6050 accelerometer  
- MAX30101 heart rate sensor  
- WiFi connection  

---

### Setup

1. Clone the repository:
```
git clone https://github.com/AtlagicBartol/OLED-Arduino-digital-watch.git
```

2. Open project in Arduino IDE  

3. Install required libraries:
- Adafruit SSD1306  
- Adafruit GFX  
- Wire  

4. Configure WiFi credentials and API key in `weather.cpp`

5. Upload code to ESP32  
