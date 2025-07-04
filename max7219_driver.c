#include <stdint.h>
#include "spi_bb.h"
#include "led_matrix_patterns.h"
#include "peripherals.h"

#define SPI_PIN_CS 8

void max7219_write(uint8_t reg, uint8_t data);
void max7219_init();
void max7219_clear();
void max7219_display(uint8_t *rows);
void printTemp(int32_t tempVal);
void printDigit(uint8_t digit);

void max7219_write(uint8_t reg, uint8_t data)
{
    //chip select basso per iniziare la trasmissione
    digitalWrite(SPI_PIN_CS, 0); 
    spi_send(reg);  // manda prima i bit del registro in cui scriver
    spi_send(data); // poi il dato
    //chip select alto per terminare la trasmissione
    digitalWrite(SPI_PIN_CS, 1);
    delay_us(10); // piccolo delay di stabilità
}

void max7219_init()
{
    max7219_write(0x09, 0x00); // Disattiva la decodifica per i diplay a 7 segmenti
    max7219_write(0x0A, 0x08); // Intensità luminosa
    max7219_write(0x0B, 0x07); // 8 righe selezionate
    max7219_write(0x0C, 0x01); // Shutdown off
    max7219_write(0x0F, 0x00); // Display test off
}

void max7219_clear()
{
    for (uint8_t i = 1; i <= 8; i++)
    {
        max7219_write(i, 0x00);
    }
}

void max7219_display(uint8_t *rows)
{
    //manda tutte i dati delle righe del pattern
    for (uint8_t i = 0; i < 8; i++)
    {
        max7219_write(i + 1, rows[i]);
    }
}

void printTemp(int32_t tempVal)
{
    // mostra la T
    printDigit(13);

    // check del segno con stampa
    if (tempVal < 0)
    {
        printDigit(10);
    }
    else
    {
        printDigit(11);
    }

    // first digit
    uint8_t first_digit = (uint8_t)(tempVal / 100);
    printDigit(first_digit);

    tempVal = tempVal - 100 * ((uint32_t)first_digit);
    // second digit
    uint8_t second_digit = (uint8_t)(tempVal / 10);
    printDigit(second_digit);

    // stampa il punto
    printDigit(12);

    tempVal = tempVal - 10 * ((uint32_t)second_digit);
    //decimal digit
    uint8_t decimal_digit = (uint8_t)(tempVal);
    printDigit(decimal_digit);
}

void printDigit(uint8_t digit)
{
    max7219_clear();
    delay_us(500000);
    max7219_display(digit_patterns[digit]);
    delay_us(2000000);
}