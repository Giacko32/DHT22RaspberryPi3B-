#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <stdint.h>
/* Pi 2/3
 * Peripherals base address
 */
#define PERIPHERALS_BASE 0x3F000000
/* SYSTIMER register addresses
 */
#define SYSTIMER (PERIPHERALS_BASE + 0x00003000)
#define SYSTIMER_CLO (*(volatile uint32_t *)(SYSTIMER + 0x04))
/* GPIO register addresses
 */
#define GPIO (PERIPHERALS_BASE + 0x00200000)
#define GPFSEL ((volatile uint32_t *)(GPIO + 0x00))
#define GPSET ((volatile uint32_t *)(GPIO + 0x1C))
#define GPCLR ((volatile uint32_t *)(GPIO + 0x28))
#define GPLEV ((volatile uint32_t *)(GPIO + 0x34))
#define INPUT 0
#define OUTPUT 1

void pinMode(uint32_t pin, uint32_t function);
void digitalWrite(uint32_t pin, uint32_t val);
uint32_t digitalRead(uint32_t pin);
void delay_us(uint32_t us);
uint8_t waitLowVal(uint32_t pin, uint32_t timeout);
uint8_t waitHighVal(uint32_t pin, uint32_t timeout);

#endif