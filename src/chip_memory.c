#include "chip_memory.h"

const word START = 0x200;
const word ETI_START = 0x600;

void load_game()
{
    printf("Loading game...\n");
    FILE* in = fopen("../games/pong.rom", "rb");
    if(in == NULL) {
        fprintf(stderr, "Errore nella lettura del file");
        return;
    }
    fread(game_buffer, sizeof(byte), sizeof(game_buffer), in);
    fclose(in);

    int i;
    for(i = 0; i < 0xDFF; i++) {
        memory[i + 0x200] = game_buffer[i];
    }
    printf("Game loaded\n");
}