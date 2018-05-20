#include "chip_memory.h"
#include <string.h>

const word START = 0x200;
const word ETI_START = 0x600;

void load_game(char* filename)
{
    printf("Loading game...\n");
    char path[1024] = "../games/";
    strcat(path, filename);
    strcat(path, ".rom");
    printf("pathname: %s\n", path);
    FILE* in = fopen(path, "rb");
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