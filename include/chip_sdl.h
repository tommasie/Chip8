#ifndef CHIP_SDL_H
#define CHIP_SDL_H

#include "chip_structs.h"
#include "SDL.h"
#include "glew.h"
#include "glut.h"
#include "SDL_opengl.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#define DISPLAY_WIDTH SCREEN_WIDTH * 10
#define DISPLAY_HEIGHT SCREEN_HEIGHT * 10

//byte screen_data[SCREEN_HEIGHT][SCREEN_WIDTH][3];
extern const int display_width;
extern const int display_height;

//The window we'll be rendering to
SDL_Window* window;
    
SDL_GLContext gl_context;

GLenum error;

void init_texture();

void update_texture();

int create_SDL_window();

void close_SDL_window();

#endif