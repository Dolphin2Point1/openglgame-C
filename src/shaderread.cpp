#include <cstdio>
#include <cstdlib>
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

    const char* filestring = static_cast<const char *>(malloc(filesize + 1));
    fread((void *) filestring, 1, filesize, file);
    fclose(file);
    return filestring;
}

unsigned int compileShader(const char* source, int shadertype) {
    unsigned int shader;
    shader = glCreateShader(shadertype);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength + 1, NULL, infoLog);
        const char *stringshadertype;
        switch(shadertype) {
            case GL_VERTEX_SHADER:
                stringshadertype = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                stringshadertype = "fragment";
                break;
        }
        printf("ERROR: SHADER COMPILATION FAILED. Error:\n\"%s\"\nSource:\n\"%s\"\nType:\n\"%s\"\nThis might make the program unrunnable :/\n", infoLog, source, stringshadertype);
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
    printf("VERTEX SHADER SOURCE:\n\"%s\"\n FRAGMENT SHADER SOURCE:\n\"%s\"\n", vertexSource, fragmentSource);
    unsigned int vertex = compileShader(vertexSource, GL_VERTEX_SHADER);
    if(vertex == NULL) {
        return NULL;
    }
    unsigned int fragment = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    if(fragment == NULL) {
        return NULL;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {

        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        printf("ERROR: LINKING FAILED. ERROR: \n\"%s\"\nThis might make the program unrunnable.\n", infoLog);

        return NULL;
    }
    printf("SUCCESS: LINKING\n");
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}
