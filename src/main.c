#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "chip_emulator.h"
#include "SDL.h"

#define CHIP_SDL_GL
//#define CHIP_GLEW
//#define CHIP_GLUT

#ifdef CHIP_SDL_GL
#include "chip_sdl.h"
#endif

int main(int argc, char** argv)
{
    //Reset registers and data structures
    init();
    //Load game
    load_game("pong");

    // Set up render system and register input callbacks
    create_SDL_window();

    init_texture();

    byte loop = 1;
    while(loop) {
        emulate_cycle();
        if(draw_flag) {
            update_texture();
            draw_flag = 0;
        }

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                printf("Quit\n");
                loop = 0;
            }
            else {
                handle_keyboard_event(event);
            }
        }
        struct timespec t = {.tv_sec = 0, .tv_nsec = 50 * 1000 * 1000};
        nanosleep(&t,NULL);
    }
    close_SDL_window();
    return 0;

}