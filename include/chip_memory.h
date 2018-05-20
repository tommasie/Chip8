#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include "chip_structs.h"

//Main RAM memory, 4096 bytes
byte memory[4096];

//Game ROM buffer
byte game_buffer[0xDFF];

//Start address
extern const word START;

//Alternate start address for ETI 660
extern const word ETI_START;

void load_game();

#endif