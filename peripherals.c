#include "peripherals.h"
#include <stdint.h>

void pinMode(uint32_t pin, uint32_t function)
{
    uint32_t reg = pin / 10;
    uint32_t offset = (pin % 10) * 3;
    GPFSEL[reg] &= ~(0b111 << offset);
    GPFSEL[reg] |= ((0b111 & function) << offset);
}

void digitalWrite(uint32_t pin, uint32_t val)
{
    uint32_t reg = pin / 32;
    uint32_t offset = pin % 32;
    if (val)
        GPSET[reg] = 1 << offset;
    else
        GPCLR[reg] = 1 << offset;
}

uint32_t digitalRead(uint32_t pin)
{
    uint32_t reg = pin / 32;
    uint32_t offset = pin % 32;

    return (GPLEV[reg] >> offset) & 0x00000001; 
}

void delay_us(uint32_t us)
{
    uint32_t start = SYSTIMER_CLO;
    while ((SYSTIMER_CLO - start) < us);
}

uint8_t waitLowVal(uint32_t pin, uint32_t timeout){

    uint32_t reg = pin / 32;
    uint32_t offset = pin % 32;

    while ((GPLEV[reg] & (1 << offset)) && --timeout)
    {
        delay_us(1);
    }

    if(timeout == 0){
        return 0;
    }
    return 1;

}

uint8_t waitHighVal(uint32_t pin, uint32_t timeout){
    
    uint32_t reg = pin / 32;
    uint32_t offset = pin % 32;

    while (!(GPLEV[reg] & (1 << offset)) && --timeout)
    {
        delay_us(1);
    }

    if(timeout == 0){
        return 0;
    }
    return 1;

}