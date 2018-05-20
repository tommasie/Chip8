cmake_minimum_required(VERSION 3.0.0)
project(Chip-8 VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

#Include SDL
set(SDL2_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_LIBRARIES "/usr/lib/libSDL2.so")
include_directories(${SDL2_INCLUDE_DIRS})

#Include OpenGL2
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#Include GLEW
find_package(GLEW REQUIRED)
#For some reason, find_package doesn't return the proper include dir
include_directories("/usr/include/GL")

#Include GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

#include project files
include_directories(include)
file(GLOB SOURCES "src/*.c")

#Generate executable from sources
add_executable(emu ${SOURCES})

#Link SDL libraries to the executable
target_link_libraries(emu ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
