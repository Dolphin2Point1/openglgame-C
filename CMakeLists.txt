cmake_minimum_required(VERSION 3.15)
project(openglgame C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(openglgame src/main.c src/shaderread.c)

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

include_directories(ext/stb)

project(cglm C)
add_library(cglm ext/cglm/src/euler.c
ext/cglm/src/affine.c
ext/cglm/src/io.c
ext/cglm/src/quat.c
ext/cglm/src/cam.c
ext/cglm/src/vec3.c
ext/cglm/src/vec4.c
ext/cglm/src/mat3.c
ext/cglm/src/mat4.c
ext/cglm/src/plane.c
ext/cglm/src/frustum.c
ext/cglm/src/box.c
ext/cglm/src/project.c
ext/cglm/src/sphere.c
ext/cglm/src/ease.c
ext/cglm/src/curve.c
ext/cglm/src/bezier.c
ext/cglm/src/mat2.c)
target_link_libraries(openglgame cglm)
include_directories(ext/cglm/include)

include_directories(include)