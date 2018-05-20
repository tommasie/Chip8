#ifndef CHIP_GLEW_H
#define CHIP_GLEW_H

#include "glew.h"
#include "SDL.h"

SDL_Window* window;
SDL_GLContext gl_context;

int create_SDL_window_glew();

void init_texture_glew();

void update_texture_glew();

void close_SDL_window_glew();

#endif