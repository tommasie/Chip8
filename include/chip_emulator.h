#ifndef EMULATOR_H
#define EMULATOR_H

#include "chip_structs.h"
#include "chip_memory.h"

void init();

void emulate_cycle();

#endif