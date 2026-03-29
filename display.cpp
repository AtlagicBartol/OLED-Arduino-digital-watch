#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


void display_init()
{
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void displayTime(DateTime datetime){
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
    display2digits(datetime.hours);
    display.print(":");
    display2digits(datetime.minutes);
    display.print(":");
    display2digits(datetime.seconds);

    display.display();
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