#include <stdio.h>
#include "chip_sdl.h"

int create_SDL_window()
{
    int factor = 10;
    const int display_width = SCREEN_WIDTH * factor;
    const int display_height = SCREEN_HEIGHT * factor;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}

    //Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Disable old deprectaed code
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

    //Initialize OpenGL
    /*if(!init_GL())
    {
        fprintf(stderr, "Unable to initialize OpenGL!\n" );
        return 0;
    }*/

	return 1;
}

void init_texture()
{
    // Clear screen
    int x, y;
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

void update_texture()
{
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
    }


    //glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 32, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);
    
	// Update Texture
	/*glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);	glVertex2d(-1.0f, -1.0f);
		glTexCoord2d(1.0f, 0.0f); 	glVertex2d(1.0f, -1.0f);
		glTexCoord2d(1.0f, 1.0f); 	glVertex2d(1.0f, DISPLAY_HEIGHT);
		glTexCoord2d(0.0f, 1.0f); 	glVertex2d(-1.0f, DISPLAY_HEIGHT);
	glEnd();*/
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);		glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0, 0.0); 	glVertex2d(64*10, 0.0);
        glTexCoord2d(1.0, 1.0); 	glVertex2d(64*10, 32*10);
        glTexCoord2d(0.0, 1.0); 	glVertex2d(0.0,	32*10);
    glEnd();
    
    glutSwapBuffers();
}

void close_SDL_window() 
{
    //Delete OpenGL context
    SDL_GL_DeleteContext(gl_context);
	// Destroy window
	SDL_DestroyWindow(window);
    window = NULL;
	// Shutdown SDL 2
	SDL_Quit();
}