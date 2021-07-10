//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "shader.h"

struct EZShader
{
    unsigned int prgid;
};

unsigned int ezGetShaderProgramId(struct EZShader *shader) {
    return shader->prgid;
}