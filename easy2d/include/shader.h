//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_SHADER_H
#define EASY2D_SHADER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EZShader EZShader;

unsigned int ezGetShaderProgramId(struct EZShader *shader);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SHADER_H
