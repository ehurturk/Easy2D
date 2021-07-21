//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_SHADER_H
#define EASY2D_SHADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cglm/cglm.h>
#include <stdarg.h>

#define EZ_VERTEX_SHADER 0
#define EZ_VERTEX_SHADER_STR 1
#define EZ_FRAGMENT_SHADER 2
#define EZ_FRAGMENT_SHADER_STR 3
#define EZ_GEOMETRY_SHADER 4
#define EZ_GEOMETRY_SHADER_STR 5
#define EZ_SHADER_PROGRAM 6

typedef struct EZShader EZShader;

struct EZShaderInfo {
    int type;
    const char *src;
};

unsigned int ezGetShaderProgramId(struct EZShader *shader);

/* Sequential Way to Create Shader Pipeline (like a tunnel) */
struct EZShader *ezSequentialShaderPipeline();
void ezAddToShaderPipeline(struct EZShader *shader, int type, const char *src);
void ezFinishShaderPipeline(struct EZShader *shader);
void ezUseShader(const struct EZShader *shader);

/* Direct Way to Create Shader Pipeline */
struct EZShader *ezDirectShaderPipeline(int n, ...); /* variadic of EZShaderInfo */

/* Uniforms */
void ezSetShaderUniformMat4(struct EZShader *shader, const char *loc, mat4 mvp);

/* Resource Deallocation */
void ezReleaseShader(struct EZShader *shader);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SHADER_H
