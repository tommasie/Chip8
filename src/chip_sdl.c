#include "chip_sdl.h"
#include "glad.h"
#include <stdio.h>

void print_display_sdl();

GLenum error;

int file_size(FILE* fp)
{
    int size;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}

GLchar* get_shader_code(char* path)
{
    FILE* in = fopen(path, "r");
    if(in == NULL) {
        fprintf(stderr, "Error reading file");
        return NULL;
    }
    int size = file_size(in);
    GLchar* string = (GLchar*)malloc(size);
    int i = 0;
    char c;
    while((c = fgetc(in)) != EOF) {
        string[i++] = (GLchar)c;
    }
    fclose(in);
    string[i] = '\0';
    return string;

}

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Disable old deprectaed code
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    //Create window
    window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                display_width, display_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if((gl_context = SDL_GL_CreateContext(window)) == NULL) {
        fprintf(stderr, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    printf("OpenGL loaded\n");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    //Use Vsync
    if(SDL_GL_SetSwapInterval(1) < 0) {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

	return 1;
}

void init_texture()
{
    // Clear screen
    memset(screen_data, 0, 32*64*3);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //TODO understand why rendering with EBO doesn't work

    //Vertices data
    //NOTE : the screen matrix from the emulator has y flipped
    //therefore (-1,-1) on display is mapped to (0,1) rather than (0,0)
    /*
    const GLfloat vertices[] = {
        //Position    //TexCoord
        -1.0f, -1.0f, 0.0f, 1.0f, //Bottom left
        -1.0f,  1.0f, 0.0f, 0.0f, //Top left
         1.0f, -1.0f, 1.0f, 1.0f, //Bottom right
         1.0f,  1.0f, 1.0f, 0.0f  //Top right
    };

    const GLuint indices[] = {
        3, 2, 1,
        1, 0, 2
    };*/

    GLfloat vertices[] = {
        // Pos          Tex
        -1.0f,-1.0f,  0.0f, 1.0f,
        -1.0f, 1.0f,  0.0f, 0.0f,
         1.0f,-1.0f,  1.0f, 1.0f,
         1.0f, 1.0f,  1.0f, 0.0f,
         1.0f,-1.0f,  1.0f, 1.0f,
        -1.0f, 1.0f,  0.0f, 0.0f,
    };

    //Buffers

    //Define the Vertex Array Object
    //It stores up to 16 pointers to vertex attributes for each VBO
    glGenVertexArrays(1,&(data.VAO));
    glBindVertexArray(data.VAO);

    //Define the Vertex Buffer Object, the input of the pipeline
    glGenBuffers(1,&(data.VBO));
    //Bind the VBO to the GL_ARRAY_BUFFER attribute
    glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //TODO set vertex attribute pointers
    //Position Attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //TexCoord Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Define the Element Buffer Object, which allows to draw stuff like rects using only 3 vertices
    /*
    glGenBuffers(1, &(data.EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    error = glGetError();
    if(error != GL_NO_ERROR) {
        printf("Error EBO %d\n", error);
    }

    //Shaders
    GLint status;

    const GLchar* vertex_shader_source = get_shader_code("../shaders/vertex_shader.vert");
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char error_buffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, error_buffer);
        fprintf(stderr, "Vertex shader error:\n%s\n", error_buffer);
        abort();
    }
     //Cast variable to non-const version (compiler emits warnings)
    free((GLchar*)vertex_shader_source);

    const GLchar* fragment_shader_source = get_shader_code("../shaders/fragment_shader.frag");
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char error_buffer[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, error_buffer);
        fprintf(stderr, "Fragment shader error:\n%s\n", error_buffer);
        abort();
    }
    //Cast variable to non-const version (compiler emits warnings)
    free((GLchar*)fragment_shader_source);

    data.shader_program = glCreateProgram();
    glAttachShader(data.shader_program, vertex_shader);
    glAttachShader(data.shader_program, fragment_shader);
    glLinkProgram(data.shader_program);
    glGetProgramiv(data.shader_program, GL_LINK_STATUS, &status);
    if (!status) {
        char error_buffer[512];
        glGetProgramInfoLog(data.shader_program, 512, NULL, error_buffer);
        fprintf(stderr, "Shader link error:\n%s\n", error_buffer);
        abort();
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(data.shader_program);
    error = glGetError();
    if(error != GL_NO_ERROR) {
        printf("Error Program %d\n", error);
    }

    //Texture
    glGenTextures(1, &(data.texture));
    glBindTexture(GL_TEXTURE_2D, data.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

void update_texture()
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

    //print_display_sdl();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, data.texture);
    glUseProgram(data.shader_program);
    
    glBindVertexArray(data.VAO);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 64, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, screen_data);
    
    glUniform1i(glGetUniformLocation(data.shader_program, "display"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
   //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    error = glGetError();
    if(error != GL_NO_ERROR) {
        printf("Error drawing %d\n", error);
    }
    SDL_GL_SwapWindow(window);
    glBindVertexArray(0);
}

void handle_keyboard_event(SDL_Event event)
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

void print_display_sdl()
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