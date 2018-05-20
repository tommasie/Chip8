#ifndef CHIP_GLUT_H
#define CHIP_GLUT_H

#include "glut.h"

int init_glut(int* argc, char** argv);

void init_texture_glut();

void update_texture_glut();

void keyboardUp(unsigned char k, int x, int y);

void keyboardDown(unsigned char k, int x, int y);

#endif