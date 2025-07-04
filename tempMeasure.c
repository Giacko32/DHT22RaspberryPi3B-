#include <stdint.h>
#include "spi_bb.h"
#include "max7219_driver.h"
#include "led_matrix_patterns.h"
#include "dht22.h"

void main(void)
{
    //la misura e la stampa avvengono iterativamente
    while (1)
    {
        //0.5 secondo di delay iniziale
        delay_us(500000);
        //manda lo start signal al sensore
        if(send_start_signal() == 0) {
            //stampa errore;
            printDigit(14);
            continue;
        }

        //legge i valori mandati dal sensore
        uint16_t tempBits = readTemperatureBits();

        //0x8000 è il valore di errore
        if (tempBits == 0x8000)
        {
            //stampa errore;
            printDigit(14);
            continue;
        }

        //converte la temperatura che è in formato 1 bit di segno - 15 bit dato in un int32 con segno
        int32_t temp = convertTemp(tempBits);

        //inizializza spi con bit banging
        spi_init();
        //inizializza il display 8x8
        max7219_init();
        //pulizia del display
        max7219_clear();

        //stampa della temperatura sul display
        printTemp(temp);
    }
}








