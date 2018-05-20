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
    load_game("invaders");

    // Set up render system and register input callbacks
    create_SDL_window_glew();

    init_texture_glew();

    byte loop = 1;
    while(loop) {
        emulate_cycle();
        if(draw_flag) {
            update_texture_glew();
        }

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                printf("Quit\n");
                loop = 0;
            }
            else {
                handle_input(event);
            }
        }
        struct timespec t = {.tv_sec = 0, .tv_nsec = 500 * 1000 * 1000};
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

/*#include "glad.h"
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int file_size(FILE* fp)
{
    int size;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}


int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL) {
        fprintf(stderr, "Error loading window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    FILE* vertex = fopen("../shaders/vertex_shader.glsl", "r");
    int size = file_size(vertex);
    char glsl[size];
    int i = 0;
    char c;
    while((c = fgetc(vertex)) != EOF) {
        glsl[i++] = c;
    }
    glsl[i] = '\0';
    printf("%s\n", glsl);

    const GLchar* vertexShaderSource = (GLchar*)glsl;
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Check if shader compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Error compiling vertex shader: %s\n", infoLog);
    }

    FILE* fragment = fopen("../shaders/fragment_shader.glsl", "r");
    memset(glsl,0,sizeof(char));
    i = 0;
    while((c = fgetc(fragment)) != EOF) {
        glsl[i++] = c;
    }
    glsl[i] = '\0';
    printf("%s\n", glsl);

    const GLchar* fragmentShaderSource = "#version 330 core\n \
        out vec4 FragColor;\n \
        void main() \
        { \
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
        }";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Error compiling fragment shader: %s\n", infoLog);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Error linking program: %s\n", infoLog);
    }
    glUseProgram(shaderProgram);
    //Once the program is created, the shaders are not needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}*/
