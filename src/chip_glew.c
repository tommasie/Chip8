#include "chip_glew.h"
#include "chip_structs.h"
#include <stdio.h>

const int modifier = 10;
int display_width = 64 * modifier;
int display_height = 32 * modifier;

void print_display();

int create_SDL_window_glew()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}

    //Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //Disable old deprectaed code
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    glewInit();

    //Create window
    window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                display_width, display_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if((gl_context = SDL_GL_CreateContext(window)) == NULL) {
        fprintf(stderr, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    //Use Vsync
    if( SDL_GL_SetSwapInterval(1) < 0 ) {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

	return 1;
}

void init_texture_glew()
{
    // Clear screen
    memset(screen_data, 0, 32*64*3);

    glViewport(0, 0, display_width, display_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, display_width, display_height, 0, 0, 1.0f);
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);

	// Set up the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 

	// Enable textures
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
}

void update_texture_glew()
{
    // Update pixels
    for(byte y = 0; y < 32; y++) {
        for(byte x = 0; x < 64; x++) {
            if(screen[y][x] == 1) {
                screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0xFF;
            }
            else {
                screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0;
            }
        }
    }

    //Print display matrix to console
    //print_display();

    glClear(GL_COLOR_BUFFER_BIT);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 32, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);
    
	// Update Texture
    //glDrawPixels(display_width, display_height, GL_RGB, GL_UNSIGNED_BYTE,(GLvoid*) screen_data);
	/*glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);	glVertex2d(-1.0f, -1.0f);
		glTexCoord2d(1.0f, 0.0f); 	glVertex2d(1.0f, -1.0f);
		glTexCoord2d(1.0f, 1.0f); 	glVertex2d(1.0f, DISPLAY_HEIGHT);
		glTexCoord2d(0.0f, 1.0f); 	glVertex2d(-1.0f, DISPLAY_HEIGHT);
	glEnd();*/
    glBegin(GL_QUADS);
        glTexCoord2d(0.0f, 0.0f);	glVertex2d(0.0f, 0.0f);
        glTexCoord2d(1.0f, 0.0f); 	glVertex2d(64*10, 0.0f);
        glTexCoord2d(1.0f, 1.0f); 	glVertex2d(64*10, 32*10);
        glTexCoord2d(0.0f, 1.0f); 	glVertex2d(0.0f, 32*10);
    glEnd();
    
    SDL_GL_SwapWindow(window);
}

void handle_input(SDL_Event event)
{
    if(event.type == SDL_KEYDOWN) {
        printf("Key pressed: %c\n", event.key.keysym.sym);
        switch(event.key.keysym.sym) {
            case SDLK_x: key[0] = 1; break;
            case SDLK_a: key[1] = 1; break;
            case SDLK_s: key[2] = 1; break;
            case SDLK_d: key[3] = 1; break;
            case SDLK_q: key[4] = 1; break;
            case SDLK_w: key[5] = 1; break;
            case SDLK_e: key[6] = 1; break;
            case SDLK_1: key[7] = 1; break;
            case SDLK_2: key[8] = 1; break;
            case SDLK_3: key[9] = 1; break;
            case SDLK_z: key[10] = 1; break;
            case SDLK_c: key[11] = 1; break;
            case SDLK_4: key[12] = 1; break;
            case SDLK_r: key[13] = 1; break;
            case SDLK_f: key[14] = 1; break;
            case SDLK_v: key[15] = 1; break;
        }
    }
    else if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_x: key[0] = 0; break;
            case SDLK_a: key[1] = 0; break;
            case SDLK_s: key[2] = 0; break;
            case SDLK_d: key[3] = 0; break;
            case SDLK_q: key[4] = 0; break;
            case SDLK_w: key[5] = 0; break;
            case SDLK_e: key[6] = 0; break;
            case SDLK_1: key[7] = 0; break;
            case SDLK_2: key[8] = 0; break;
            case SDLK_3: key[9] = 0; break;
            case SDLK_z: key[10] = 0; break;
            case SDLK_c: key[11] = 0; break;
            case SDLK_4: key[12] = 0; break;
            case SDLK_r: key[13] = 0; break;
            case SDLK_f: key[14] = 0; break;
            case SDLK_v: key[15] = 0; break;
        }
    }
}

void close_SDL_window_glew()
{
    //Delete OpenGL context
    SDL_GL_DeleteContext(gl_context);
	// Destroy window
	SDL_DestroyWindow(window);
    window = NULL;
	// Shutdown SDL 2
	SDL_Quit();
}

void print_display()
{
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
    }
}