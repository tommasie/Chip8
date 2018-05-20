#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "chip_emulator.h"
#include "SDL.h"

//#define CHIP_SDL_GL
#define CHIP_GLEW
//#define CHIP_GLUT

#ifdef CHIP_SDL_GL
//#include "chip_sdl.h"
#endif

#ifdef CHIP_GLEW
#include "chip_glew.h"
#endif

#ifdef CHIP_GLUT
#include "chip_glut.h"
#endif

byte texture[32][64][3];

//SDL/OpenGL main
/*
int main(int argc, char** argv)
{

}
*/

//GLEW main
int main(int argc, char* argv[]) {

    //Reset registers and data structures
    init();
    //Load game
    load_game();

    // Set up render system and register input callbacks
    create_SDL_window_glew();

    init_texture_glew();

    int loop = 1;
    while(loop) {
        emulate_cycle();
        //print_state();
        if(draw_flag) {
            update_texture_glew();
        }

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                printf("Quit\n");
                loop = 0;
            }
            if(event.type == SDL_KEYDOWN) {
                printf("Key down");
            }
        }
        struct timespec t = {.tv_sec = 0, .tv_nsec = 100 * 1000 * 1000};
        nanosleep(&t,NULL);
    }

    close_SDL_window_glew();
    return 0;
}

//GLUT main
/*
int main(int argc, char** argv)
{
    glut_init(&argc, argv);
}
*/
