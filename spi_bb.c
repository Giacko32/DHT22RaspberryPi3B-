#include "peripherals.h"

#define SPI_PIN_CLK 11
#define SPI_PIN_MOSI 10
#define SPI_PIN_CS 8

static void spi_send_bit(uint16_t bit_value, uint32_t half_period);

void spi_init()
{
    //set dei pin ad Output per bit banging  
    pinMode(SPI_PIN_CLK, OUTPUT);
    pinMode(SPI_PIN_MOSI, OUTPUT);
    pinMode(SPI_PIN_CS, OUTPUT);

    //MOSI a 0 
    digitalWrite(SPI_PIN_MOSI, 0);
    //Clock a 0
    digitalWrite(SPI_PIN_CLK, 0);
    //Chip select alto
    digitalWrite(SPI_PIN_CS, 1);
}

void spi_send(uint8_t data)
{
    uint32_t half_period_us;
    uint8_t mask;
    half_period_us = 20;
    for (mask = 0x80; mask; mask = (mask >> 1))
    {
        spi_send_bit(data & mask, half_period_us);
    }
}

void spi_send_bit(uint16_t bit_value, uint32_t half_period)
{
    digitalWrite(SPI_PIN_MOSI, bit_value);
    delay_us(5);
    digitalWrite(SPI_PIN_CLK, 1);
    delay_us(half_period-5);
    digitalWrite(SPI_PIN_CLK, 0);
    delay_us(half_period);
}


