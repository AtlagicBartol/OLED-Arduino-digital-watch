#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "ssd1306.h"

volatile uint8_t sec = 0;
volatile uint8_t min = 49;
volatile uint8_t hour = 12;
volatile uint8_t redraw = 0;

int main(void)
{
    i2c_init();
    ssd1306_init();
    ssd1306_clear();
    timer1_init();
    sei();  // enable global interrupts
    char clock[6]; 
    char word[] = "DIGITAL CLOCK";


    clock[0] = (hour / 10) + '0';
    clock[1] = (hour % 10) + '0';

    clock[2] = ':';

    clock[3] = (min / 10) + '0';
    clock[4] = (min % 10) + '0';

    clock[5] = '\0';

    while (1){
        if(redraw){
            redraw = 0;

            char clock[9];
            
            clock[0] = (hour/10) + '0';
            clock[1] = (hour%10) + '0';
            clock[2] = ':';
            clock[3] = (min/10) + '0';
            clock[4] = (min%10) + '0';
            clock[5] = ':';
            clock[6] = (sec/10) + '0';
            clock[7] = (sec%10) + '0';
            clock[8] = '\0';

            ssd1306_clear();

            for(int i = 0; word[i] != '\0'; i++){
                ssd1306_draw_char(12 + i * 7,10, word[i]);
            }

            for(int i = 0; clock[i] != '\0';i++){
                ssd1306_draw_char(25 + i * 7, 30, clock[i]);
            }
            ssd1306_update();
        }
    }
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
    }

    redraw = 1;   // signal main() da osvježi ekran
}