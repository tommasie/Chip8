#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;

//Registers
byte V[16];
//Index register
word I;
//Program Counter
word PC;
//Program Stack
word stack[16];
//Stack Pointer
word SP;

//Screen matrix (no need for RGB since it's BW)
byte screen[32][64];
byte gfx[64*32];
byte draw_flag;

byte screen_data[32][64][3];

//Timer registers
byte sound_timer;
byte delay_timer;

//Keyboard (16 keys)
byte key[16];

extern byte fontset[80];
word opcode;

void print_state();

void print_screen();


#endif