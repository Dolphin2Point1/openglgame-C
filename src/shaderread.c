#include <stdio.h>
#include <stdlib.h>
#include <shaderread.h>
#include <glad/glad.h>

const char* loadFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    const char* filestring = malloc(filesize + 1);
    fread(filestring, 1, filesize, file);
    fclose(file);
    return filestring;
}

unsigned int compileShader(const char* source, int shadertype) {
    unsigned int shader;
    shader = glCreateShader(shadertype);
    int success;
    char infoLog[512];
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR: SHADER COMPILATION FAILED. Error:\n\"%s\"\nSource:\n\"%s\"\nThis might make the program unrunnable :/", infoLog, source);
        return NULL;
    }

    return shader;

}

unsigned int make(const char* filename, int shadertype) {
    const char* filestring = loadFile(filename);
    if(filestring == NULL) {
        return NULL;
    }
    return compileShader(filestring, shadertype);
}

unsigned int makeAndLinkVF(const char* vertexSourceFile, const char* fragmentSourceFile) {
    const char* vertexSource = loadFile(vertexSourceFile);
    if(vertexSource == NULL) {
        return NULL;
    }
    const char* fragmentSource = loadFile(fragmentSourceFile);
    if(fragmentSource == NULL) {
        return NULL;
    }
    unsigned int vertex = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragment = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, vertex);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {

        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        printf("ERROR: LINKING FAILED. ERROR: \n\"%s\"\n", infoLog);

    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}
