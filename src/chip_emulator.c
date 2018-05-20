#include "chip_emulator.h"
#include "chip_memory.h"
#include "chip_opcodes.h"
#include "chip_structs.h"
#include <string.h>

void init()
{
    //Reset single registers
    PC = 0x200;
    opcode = 0;
    SP = 0;
    I = 0;

    // Clear display
    memset(screen, 0, sizeof(byte) * 32 * 64);
    memset(gfx, 0, sizeof(byte) * 64 * 32);
    draw_flag = 1;	
    // Clear stack
    memset(stack, 0, sizeof(stack));
    // Clear registers V0-VF
    memset(V, 0, sizeof(V));
    memset(key, 0,sizeof(key));
    // Clear memory
    memset(memory, 0, sizeof(memory));
    // Load fontset
    for(int i = 0; i < 0x50; i++)
        memory[i] = fontset[i];

    //Reset timers
    delay_timer = 0;
    sound_timer = 0;
}

void emulate_cycle()
{
    //Fetch opcode
    //Memory cell is 1 byte, opcodes are 2 bytes
    opcode = memory[PC] << 8 | memory[PC + 1];
    printf("Current opcode: %04X\n", opcode);
    //Decode opcode
    //Execute opcode
    decode_execute_opcode(opcode);

    //Update timers
    if(delay_timer > 0)
        delay_timer--;
    
    if(sound_timer > 0) {
        if(sound_timer == 1)
            printf("BEEP!\n");
        sound_timer--;
    }
}