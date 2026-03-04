#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "ssd1306.h"
#include <util/delay.h>

volatile uint8_t sec = 0;
volatile uint8_t min = 18;
volatile uint8_t hour = 10;
volatile uint8_t day = 2;
volatile uint8_t month = 3;
volatile int year = 2026;
volatile uint8_t redraw = 0;

#define SAMPLE_RATE 100

uint32_t ir, red;

uint32_t ir_prev = 0;
uint32_t ir_curr = 0;

uint32_t last_peak_time = 0;
uint32_t sample_counter = 0;

uint8_t heart_rate = 0;

uint8_t rising = 0;

int main(void)
{
    i2c_init();
    ssd1306_init();
    max30102_init();
    ssd1306_clear();
    timer1_init();
    sei();  // enable global interrupts
    char clock[9]; 
    char date[11];
    char bpm_str[8];

    while (1)
    {
        max30102_read_fifo(&ir, &red);
        process_heart_rate(ir);

        _delay_ms(10);   // 100 Hz sampling

        if (redraw)
        {
            redraw = 0;

            redraw_clock(clock);
            redraw_date(date);
            redraw_bpm(bpm_str);

            ssd1306_clear();

            ssd1306_draw_string(12, 0, date);
            ssd1306_draw_string(25, 30, clock);

            ssd1306_draw_string(12, 50, bpm_str);

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

void redraw_bpm(char *bpm_str){
    bpm_str[0] = (heart_rate/100) % 10 + '0';
    bpm_str[1] = (heart_rate/10) % 10 + '0';
    bpm_str[2] = (heart_rate%10) + '0';
    bpm_str[3] = ' ';
    bpm_str[4] = 'B';
    bpm_str[5] = 'P';
    bpm_str[6] = 'M';
    bpm_str[7] = '\0';
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

int process_heart_rate(uint32_t ir_value)
{
    ir_prev = ir_curr;
    ir_curr = ir_value;

    sample_counter++;

    // Minimalni threshold (makni šum)
    if (ir_curr > 50000)
    {
        // Ako signal raste
        if (ir_curr > ir_prev)
        {
            rising = 1;
        }
        // Ako je prije rastao, a sada pada → peak
        else if (rising)
        {
            uint32_t period = sample_counter - last_peak_time;

            // Ignoriraj prebrze peakove (anti-noise)
            if (period > (SAMPLE_RATE / 2))   // >0.5s
            {
                heart_rate = (60 * SAMPLE_RATE) / period;
                last_peak_time = sample_counter;
            }

            rising = 0;
        }
    }
    return heart_rate;
}