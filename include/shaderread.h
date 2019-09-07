//
// Created by finian on 9/6/19.
//

#ifndef CGLM_SHADERREAD_H
#define CGLM_SHADERREAD_H

#endif //CGLM_SHADERREAD_H

const char* loadFile(const char* filename);

unsigned int compileShader(const char* source, int shadertype);

unsigned int make(const char* filename, int shadertype);

unsigned int makeAndLinkVF(const char* vertexSourceFile, const char* fragmentSourceFile);