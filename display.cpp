#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void display_init()
{
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void display_show_text(const char* text)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(text);
    display.display();
}

void display_show_hr(int hr)
{
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0,0);
    display.println("Heart Rate");

    display.setTextSize(3);
    display.setCursor(0,30);
    display.print(hr);
    display.println(" BPM");

    display.display();
}