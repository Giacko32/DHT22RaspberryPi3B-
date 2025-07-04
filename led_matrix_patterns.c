// led_matrix_patterns.c

#include "led_matrix_patterns.h"
#include <stdint.h>          

// Pattern per la cifra 0
uint8_t char_0[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

// Pattern per la cifra 1
uint8_t char_1[8] = {
    0b00010000, //     X
    0b00110000, //    XX
    0b00010000, //     X
    0b00010000, //     X
    0b00010000, //     X
    0b00010000, //     X
    0b00010000, //     X
    0b00111000  //    XXX
};

// Pattern per la cifra 2
uint8_t char_2[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b00000100, //       X
    0b00001000, //      X
    0b00010000, //     X
    0b00100000, //    X
    0b01000000, //   X
    0b01111110  //  XXXXXXX
};

// Pattern per la cifra 3
uint8_t char_3[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b00000010, //       X
    0b00001100, //      XX
    0b00000010, //       X
    0b00000010, //       X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

// Pattern per la cifra 4
uint8_t char_4[8] = {
    0b00001000, //     X
    0b00011000, //    XX
    0b00101000, //   X X
    0b01001000, //  X  X
    0b01111100, //  XXXXXX
    0b00001000, //     X
    0b00001000, //     X
    0b00001000  //     X
};

// Pattern per la cifra 5
uint8_t char_5[8] = {
    0b01111110, //  XXXXXXX
    0b01000000, //  X
    0b01000000, //  X
    0b01111100, //  XXXXXX
    0b00000010, //       X
    0b00000010, //       X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

// Pattern per la cifra 6
uint8_t char_6[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b01000000, //  X
    0b01111100, //  XXXXXX
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

// Pattern per la cifra 7
uint8_t char_7[8] = {
    0b01111110, //  XXXXXXX
    0b00000010, //       X
    0b00000010, //       X
    0b00000100, //      X
    0b00001000, //     X
    0b00010000, //    X
    0b00100000, //   X
    0b01000000  //  X
};

// Pattern per la cifra 8
uint8_t char_8[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

// Pattern per la cifra 9
uint8_t char_9[8] = {
    0b00111100, //   XXXX
    0b01000010, //  X    X
    0b01000010, //  X    X
    0b00111110, //   XXXXXX
    0b00000010, //       X
    0b00000010, //       X
    0b01000010, //  X    X
    0b00111100  //   XXXX
};

uint8_t minus[8] = {
    0b00000000, // Riga 0
    0b00000000, // Riga 1
    0b00000000, // Riga 2
    0b01111110, // Riga 3 (linea orizzontale)
    0b01111110, // Riga 4 (linea orizzontale)
    0b00000000, // Riga 5
    0b00000000, // Riga 6
    0b00000000  // Riga 7
};

uint8_t plus[8] = {
    0b00000000, // Riga 0:   . . . . . . . .
    0b00011000, // Riga 1:   . . . X X . . .
    0b00011000, // Riga 2:   . . . X X . . .
    0b01111110, // Riga 3:   . X X X X X X .  (Linea orizzontale solida)
    0b01111110, // Riga 4:   . X X X X X X .  (Linea orizzontale solida)
    0b00011000, // Riga 5:   . . . X X . . .
    0b00011000, // Riga 6:   . . . X X . . .
    0b00000000  // Riga 7:   . . . . . . . .
};

uint8_t point[8] = {
    0b00000000,
    0b00000000, 
    0b00000000, 
    0b00000000,
    0b00000000, 
    0b00000000, 
    0b00011000, 
    0b00011000 
};

uint8_t T[8] = {
    0b11111111,
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000
};

uint8_t E[8] = {
    0b11111111,  // ████████
    0b11000000,  // ██
    0b11000000,  // ██
    0b11111110,  // ███████
    0b11000000,  // ██
    0b11000000,  // ██
    0b11000000,  // ██
    0b11111111   // ████████
};



// Definizione dell'array di puntatori ai pattern delle cifre
uint8_t* digit_patterns[15] = {
    char_0,
    char_1,
    char_2,
    char_3,
    char_4,
    char_5,
    char_6,
    char_7,
    char_8,
    char_9,
    minus,
    plus,
    point,
    T,
    E
};