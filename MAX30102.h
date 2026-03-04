#ifndef MAX30102_H_
#define MAX30102_H_

#include <stdint.h>

#define MAX30102_ADDR 0x57

void max30102_init(void);
void max30102_reset(void);

void max30102_write_reg(uint8_t reg, uint8_t value);
uint8_t max30102_read_reg(uint8_t reg);

void max30102_read_fifo(uint32_t *ir, uint32_t *red);

int process_heart_rate(uint32_t ir_value);

#endif