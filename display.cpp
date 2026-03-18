#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Datetime datetime = {17,14, 58,18,3,2026};

void display_init()
{
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void display_show_text(const char* text)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println(text);
    display.display();
}

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

void displayTime(){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(68, 0);
    display2digits(datetime.day);
    display.print("/");
    display2digits(datetime.month);
    display.print("/");
    display.print(datetime.year);

    display.setTextSize(2);
    display.setCursor(16, 24);
    display2digits(datetime.hour);
    display.print(":");
    display2digits(datetime.minutes);
    display.print(":");
    display2digits(datetime.seconds);

    display.display();
}

void updateTime(){
    datetime.seconds++;

    if(datetime.seconds >= 60){
        datetime.seconds = 0;
        datetime.minutes++;
    }
    if(datetime.minutes >= 60){
        datetime.minutes = 0;
        datetime.hour++;
    }
    if(datetime.hour >= 24){
        datetime.hour = 0;
        datetime.day++;
    }

}

void display2digits(uint8_t value){
    if(value < 10){
        display.print(0);
        display.print(value);
    }
    else{
        display.print(value);
    }
}