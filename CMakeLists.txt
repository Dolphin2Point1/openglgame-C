cmake_minimum_required(VERSION 3.15)
project(openglgame)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(openglgame main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ext/glfw)

target_link_libraries(openglgame glfw)

find_package(OpenGL REQUIRED)

target_include_directories(openglgame PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(openglgame ${OPENGL_gl_LIBRARY})

include_directories(ext/glad/include)
add_library(glad ext/glad/src/glad.c)
target_link_libraries(openglgame glad)
