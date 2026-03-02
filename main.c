#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "ssd1306.h"

volatile uint8_t sec = 0;
volatile uint8_t min = 18;
volatile uint8_t hour = 10;
volatile uint8_t day = 2;
volatile uint8_t month = 3;
volatile int year = 2026;
volatile uint8_t redraw = 0;

int main(void)
{
    i2c_init();
    ssd1306_init();
    ssd1306_clear();
    timer1_init();
    sei();  // enable global interrupts
    char clock[9]; 
    char date[11];

    while (1){
        if(redraw){
            redraw = 0;

            redraw_clock(clock);
            redraw_date(date);

            ssd1306_clear();

            ssd1306_draw_string(12, 0, date);

            ssd1306_draw_string(25, 30, clock);
            
            ssd1306_update();
        }
    }
}

void redraw_clock(char *clock){
    clock[0] = (hour/10) + '0';
    clock[1] = (hour%10) + '0';
    clock[2] = ':';
    clock[3] = (min/10) + '0';
    clock[4] = (min%10) + '0';
    clock[5] = ':';
    clock[6] = (sec/10) + '0';
    clock[7] = (sec%10) + '0';
    clock[8] = '\0';
}

void redraw_date(char *date){
    date[0] = (day / 10) + '0';
    date[1] = (day % 10) + '0';
            
    date[2] = ':';

    date[3] = (month / 10) + '0';
    date[4] = (month % 10) + '0';

    date[5] = ':';

    date[6] = ((year / 1000) % 10) + '0';
    date[7] = ((year / 100) % 10) + '0';
    date[8] = ((year / 10) % 10) + '0';
    date[9] = (year % 10) + '0';

    date[10] = '\0';
}

void timer1_init(void)
{
    TCCR1A = 0x00;                 // normal mode
    TCCR1B = (1 << WGM12);         // CTC mode
    OCR1A  = 15624;                // 1 second
    TIMSK1 = (1 << OCIE1A);        // enable compare interrupt
    TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
}

ISR(TIMER1_COMPA_vect)
{
    sec++;

    if (sec >= 60) {
        sec = 0;
        min++;
    }

    if (min >= 60) {
        min = 0;
        hour++;
    }

    if (hour >= 24) {
        hour = 0;
        day++;
    }

    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day >= 32){
        day = 1;
        month++;
    }
    if((month == 4 || month == 6 || month == 9 || month == 11) && day >= 31){
        day = 1;
        month++;
    }
    if((month == 2 && year % 4 == 0) && day >= 30){
        day = 1;
        month++;
    }
    if((month == 2 && year % 4 != 0) && day >= 29){
        day = 1;
        month++;
    }
    if(month >= 13){
        month = 0;
        year++;
    }

    redraw = 1;
}