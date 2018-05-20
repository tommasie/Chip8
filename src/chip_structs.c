#include "chip_structs.h"
#include <stdio.h>

byte fontset[80] = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void print_state()
{
    printf("## V registers ##\n");
    byte i;
    for(i = 0; i <= 0xF; i++) {
        printf("-----", i);
    }
    printf("\n");
    for(i = 0; i <= 0xF; i++) {
        printf("| V%01X ", i);
    }
    printf("|\n");
    for(i = 0; i <= 0xF; i++) {
        printf("-----", i);
    }
    printf("\n");
    for(i = 0; i <= 0xF; i++) {
        printf("| %02X ", V[i]);
    }
    printf("|\n");
    for(i = 0; i <= 0xF; i++) {
        printf("-----", i);
    }
    printf("\n\n");

    printf("## Other registers ##\n");
    for(i = 0; i <= 5; i++) {
        printf("-----", i);
    }
    printf("\n");
    printf("|  I   |  PC  | SP | DT | ST |\n");
    for(i = 0; i <= 5; i++) {
        printf("-----", i);
    }
    printf("\n");
    printf("| %04X | %04X | %02X | %02X | %02X |\n", I, PC, SP, delay_timer, sound_timer);
    for(i = 0; i <= 5; i++) {
        printf("-----", i);
    }
    printf("\n\n");

}

void print_screen()
{
    byte y, x;
    for(y = 0; y < 32; y++) {
        for(x = 0; x < 64; x++) {
            if(screen[y][x]) {
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}