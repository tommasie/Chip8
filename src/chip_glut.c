#include "chip_glut.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "chip_structs.h"
#include "chip_emulator.h"

int init_glut(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitWindowSize( 64*10,32*10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("GLUT Test");
    glutDisplayFunc(update_texture_glut);
    glutIdleFunc(update_texture_glut);
    glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp); 

    init_texture_glut();

    glutMainLoop();

}

void init_texture_glut()
{
    // Clear screen
    memset(screen_data, 0, 32*64*3);

	// Create a texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);
	
    // Set up the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 

	// Enable textures
	glEnable(GL_TEXTURE_2D);
}

void update_texture_glut()
{
    emulate_cycle();
    if(draw_flag) {
        // Update pixels
        for(byte y = 0; y < 32; y++) {
            for(byte x = 0; x < 64; x++) {
                /*if(screen_data[y][x][0] == 0)
                    screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0xFF;
                else
                    screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0;
                */
                if(screen[y][x] == 1) {
                    screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0xFF;
                }
                else {
                    screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0;
                }
            }
        }

        for(byte y = 0; y < 32; y++) {
            byte x = 0;
            printf("Line %2d: ", y);
            while(x < 64) {
                if(screen_data[y][x][0] == 0xFF)
                    printf("X");
                else
                    printf(".");
                x++;
            }
            printf("\n");

            draw_flag = 0;
        }
    }
    struct timespec t = {.tv_sec = 1, .tv_nsec = 100 * 1000};
    nanosleep(&t,NULL);
}

void keyboardUp(unsigned char k, int x, int y)
{
    if(k == '1')		key[0x1] = 0;
	else if(k == '2')	key[0x2] = 0;
	else if(k == '3')	key[0x3] = 0;
	else if(k == '4')	key[0xC] = 0;

	else if(k == 'q')	key[0x4] = 0;
	else if(k == 'w')	key[0x5] = 0;
	else if(k == 'e')	key[0x6] = 0;
	else if(k == 'r')	key[0xD] = 0;

	else if(k == 'a')	key[0x7] = 0;
	else if(k == 's')	key[0x8] = 0;
	else if(k == 'd')	key[0x9] = 0;
	else if(k == 'f')	key[0xE] = 0;

	else if(k == 'z')	key[0xA] = 0;
	else if(k == 'x')	key[0x0] = 0;
	else if(k == 'c')	key[0xB] = 0;
	else if(k == 'v')	key[0xF] = 0;
}

void keyboardDown(unsigned char k, int x, int y)
{
    if(k == 27)    // esc
		exit(0);

	if(k == '1')		key[0x1] = 1;
	else if(k == '2')	key[0x2] = 1;
	else if(k == '3')   key[0x3] = 1;
	else if(k == '4')	key[0xC] = 1;

	else if(k == 'q')	key[0x4] = 1;
	else if(k == 'w')	key[0x5] = 1;
	else if(k == 'e')	key[0x6] = 1;
	else if(k == 'r')	key[0xD] = 1;

	else if(k == 'a')	key[0x7] = 1;
	else if(k == 's')	key[0x8] = 1;
	else if(k == 'd')	key[0x9] = 1;
	else if(k == 'f')	key[0xE] = 1;

	else if(k == 'z')	key[0xA] = 1;
	else if(k == 'x')	key[0x0] = 1;
	else if(k == 'c')	key[0xB] = 1;
	else if(k == 'v')	key[0xF] = 1;
}
