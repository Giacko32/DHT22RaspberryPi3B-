#ifndef DHT_22_H
#define DHT_22_H

#include <stdint.h>

uint8_t send_start_signal(void);

uint16_t readTemperatureBits(void);

int32_t convertTemp(uint16_t tempBits);

#endif
