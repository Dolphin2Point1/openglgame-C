cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
project(openglgame)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(openglgame src/main.cpp src/ALMasterController.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ext/glfw)
target_link_libraries(openglgame glfw)

option(GLM_TEST_ENABLE_CXX_98 ON FORCE)
option(GLM_TEST_ENABLE_CXX_11 ON FORCE)
option(GLM_TEST_ENABLE_CXX_14 ON FORCE)
option(GLM_TEST_ENABLE_CXX_17 ON FORCE)
option(GLM_TEST_ENABLE_CXX_20 ON FORCE)
add_subdirectory(ext/glm)
target_link_libraries(openglgame)

find_package(OpenGL REQUIRED)

target_include_directories(openglgame PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(openglgame ${OPENGL_gl_LIBRARY})

find_package(OpenAL REQUIRED)

target_link_libraries(openglgame ${OPENAL_LIBRARY})
include_directories(openglgame ${OPENAL_INCLUDE_DIR})

include_directories(ext/glad/include)
add_library(glad ext/glad/src/glad.c include/Mesh.h include/ALMasterController.h)
target_link_libraries(openglgame glad)


include_directories(ext/stb)

include_directories(include)
