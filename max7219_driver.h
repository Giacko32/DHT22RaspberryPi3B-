#ifndef MAX7219_DRIVER_H
#define MAX7219_DRIVER_H

#include <stdint.h> 
#include "peripherals.h"

void max7219_init();

void max7219_clear();

void max7219_display(uint8_t *rows);

void printTemp(int32_t tempVal);

void printDigit(uint8_t digit);

#endif