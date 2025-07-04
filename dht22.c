#include <stdint.h>
#include "peripherals.h"

//dati ottenuti dalla lettura del sensore
typedef struct
{
    uint8_t correct; //1 se checksum ok, 0 altrimenti
    uint16_t temp;   //temperatura
    uint16_t hum;    //umidità
} dhtData;

uint8_t send_start_signal();
uint16_t readTemperatureBits();
dhtData parseValAndCheck(uint64_t data);
int32_t convertTemp(uint16_t tempBits);


uint8_t send_start_signal(){

    //GPIO4 come output
    pinMode(4, OUTPUT);

    //Linea Dati bassa per almeno 1ms
    digitalWrite(4, 0);

    //delay 1.1 ms
    delay_us(1100);

    //Linea Dati alta per 20-40 us
    digitalWrite(4, 1);
    delay_us(30);

    //L'host lascia la linea al sensore

    //GPIO4 come input
    pinMode(4, INPUT);
    //polling per attendere la risposta del sensore
    //finchè la linea rimane alta attende

    if(waitLowVal(4, 200) == 0){
        return 0;
    } 
    //Attendi che la linea torni alta
    if(waitHighVal(4, 200) == 0){
        return 0;
    }

    return 1;
}

uint16_t readTemperatureBits()
{
    //inizializza una variabile in cui memorizzare i valori ottenuti
    uint64_t received_val = 0;

    //0x8000 corrisponde ad una temperatura di 0 negativo, quindi lo usiamo come valore di errore

    // polling in attesa che la linea diventi bassa
    if(waitLowVal(4, 200) == 0){
        return 0x8000;
    } 

    for (uint32_t i = 0; i < 40; i++)
    {
        // polling per attendere la linea alta
        if(waitHighVal(4, 200) == 0){
            return 0x8000;
        }

        // Misurazione del tempo di valore alto per capire se è 0 o 1
        uint32_t start_time = SYSTIMER_CLO;
        if(waitLowVal(4, 200) == 0){
            return 0x8000;
        } 
        uint32_t duration = SYSTIMER_CLO - start_time;

        //shift per inserire il successivo bit
        received_val = received_val << 1;

        //somma uno al bit meno significativo se è stato rilevato 1
        if (duration > 30)
        {
            received_val += 1;
        }
    }

    delay_us(50);
    // GPIO4 come output per terminare la comunicazione
    pinMode(4, OUTPUT);

    // La trasmissione termina alzando nuovamente la linea dati
    digitalWrite(4, 1);

    dhtData dhtValues = parseValAndCheck(received_val);

    //se la checksum non è corretta allora ritorna un valore di errore
    if (dhtValues.correct != 1)
    {
        return 0x8000;
    }

    return dhtValues.temp;
}

dhtData parseValAndCheck(uint64_t data)
{

    // Gli 8 bit meno significativi sono della checksum
    uint8_t checksum_value = (uint8_t)(data & 0xff);
    // I 16 bit successivi sono quelli della temperatura
    uint16_t temp_val = (uint16_t)((data & 0xffff00) >> 8);
    // I 16 bit successivi sono quelli dell'umidità
    uint16_t hum_val = (uint16_t)((data & 0xffff000000) >> 24);

    dhtData values;

    values.temp = temp_val;
    values.hum = hum_val;
    values.correct = 0;

    //calcolo della checksum
    uint16_t sum1 = (uint8_t)(temp_val >> 8) + (uint8_t)(temp_val);
    uint16_t sum2 = (uint8_t)(hum_val >> 8) + (uint8_t)(hum_val);

    uint8_t Last8bitSum = (uint8_t)(sum1 + sum2);

    //check della checksum
    if (Last8bitSum == checksum_value)
    {
        values.correct = 1;
    }

    return values;
}

int32_t convertTemp(uint16_t tempBits){

    int16_t signed_temp;

    // controlla se il valore è negativo
    if (tempBits & 0x8000)
    {
        signed_temp = -(int16_t)(tempBits & 0x7FFF);
    }
    else
    {
        signed_temp = (int16_t)(tempBits & 0x7FFF);
    }

    return signed_temp;
}