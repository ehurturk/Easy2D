//
// Created by Emir Hürtürk on 10.07.2021.
//

#include "shader.h"
#include "resource.h"
#include "log.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

struct EZShader {
    unsigned int prgid;
    unsigned int vid;
    unsigned int fid;
    unsigned int gid;
};


void ezValidateShaderPipeline(unsigned int shader, int type) {
    int success;
    char infoLog[1024];
    switch (type) {
        case EZ_SHADER_PROGRAM:
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                EZ_ERROR_RAW("[EZ2D ERROR]: Error happened when linking the shader program\n");
                EZ_DEBUGF_RAW("%s-- ---------------------------------------------- --\n", infoLog);
            }
            break;
        case EZ_GEOMETRY_SHADER:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                EZ_ERROR_RAW("[EZ2D ERROR]: Error happened when compiling shader of type: EZ_GEOMETRY_SHADER\n");
                EZ_DEBUGF_RAW("%s-- ---------------------------------------------- --\n", infoLog);
            }
            break;
        case EZ_FRAGMENT_SHADER:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                EZ_ERROR_RAW("[EZ2D ERROR]: Error happened when compiling shader of type: EZ_FRAGMENT_SHADER\n");
                EZ_DEBUGF_RAW("%s-- ---------------------------------------------- --\n", infoLog);
            }
            break;
        case EZ_VERTEX_SHADER:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                EZ_ERROR_RAW("[EZ2D ERROR]: Error happened when compiling shader of type: EZ_VERTEX_SHADER\n");
                EZ_DEBUGF_RAW("%s-- ---------------------------------------------- --\n", infoLog);
            }
            break;
    }
}

unsigned int ezGetShaderProgramId(struct EZShader *shader) {
    ASSERT(shader, "[EZ2D:ERROR]: Shader is NULL, can't get program id of a NULL shader\n");
    return shader->prgid;
}

/* Sequential Way to Create Shader Pipeline (like a tunnel) */
struct EZShader *ezSequentialShaderPipeline() {
    struct EZShader *pipe = malloc(sizeof(struct EZShader));
    pipe->prgid           = 0;
    pipe->vid             = 0;
    pipe->fid             = 0;
    pipe->gid             = 0;
    return pipe;
}

/* sequentially add shaders to the shader pipeline */
void ezAddToShaderPipeline(struct EZShader *shader, int type, const char *src) {
    ASSERTF(src, "Could not add shader file located at %s location to the shader pipeline since it is NULL\n", src);
    ASSERT(shader, "Could not add shader to a NULL shader object\n");

    struct EZResource *res = NULL;

    if (type % 2 == 0) {
        int err;
        res = ezLoadFile(src, &err);
        ASSERTF(!err, "(%i) Could not add shader located at %s to the pipeline\n", err, src);
    }
    /* Verbose output.
        EZ_DEBUG("Data: \n");
        EZ_DEBUGF("%s\n", ezGetResourceContent(res));
        EZ_DEBUG("=======================\n");
    */
    const char *source;
    switch (type) {
        case EZ_VERTEX_SHADER:
            shader->vid = glCreateShader(GL_VERTEX_SHADER);
            source      = ezGetResourceContent(res);
            glShaderSource(shader->vid, 1, &source, NULL);
            glCompileShader(shader->vid);
            ezValidateShaderPipeline(shader->vid, EZ_VERTEX_SHADER);
            break;
        case EZ_VERTEX_SHADER_STR:
            shader->vid = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(shader->vid, 1, &src, NULL);
            glCompileShader(shader->vid);
            ezValidateShaderPipeline(shader->vid, EZ_VERTEX_SHADER);
            break;
        case EZ_FRAGMENT_SHADER:
            shader->fid = glCreateShader(GL_FRAGMENT_SHADER);
            source      = ezGetResourceContent(res);
            glShaderSource(shader->fid, 1, &source, NULL);
            glCompileShader(shader->fid);
            ezValidateShaderPipeline(shader->fid, EZ_FRAGMENT_SHADER);
            break;
        case EZ_FRAGMENT_SHADER_STR:
            shader->fid = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(shader->fid, 1, &src, NULL);
            glCompileShader(shader->fid);
            ezValidateShaderPipeline(shader->fid, EZ_FRAGMENT_SHADER);
            break;
        case EZ_GEOMETRY_SHADER:
            shader->gid = glCreateShader(GL_GEOMETRY_SHADER);
            source      = ezGetResourceContent(res);
            glShaderSource(shader->gid, 1, &source, NULL);
            glCompileShader(shader->gid);
            ezValidateShaderPipeline(shader->gid, EZ_GEOMETRY_SHADER);
            break;
        case EZ_GEOMETRY_SHADER_STR:
            shader->gid = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(shader->gid, 1, &src, NULL);
            glCompileShader(shader->gid);
            ezValidateShaderPipeline(shader->gid, EZ_GEOMETRY_SHADER);
            break;
        default:
            break;
    }
    if (type % 2 == 0) ezReleaseResource(res);
}

/* finish up the shader pipeline by creating the shader program at last */
void ezFinishShaderPipeline(struct EZShader *shader) {
    ASSERT(shader, "Can't complete the shader pipeline of a NULL shader.\n");
    shader->prgid = glCreateProgram();
    glAttachShader(shader->prgid, shader->vid);
    glAttachShader(shader->prgid, shader->fid);
    /* since geometry shader is not necessary while fragment and vertex shaders are necessary */
    if (shader->gid != 0) {
        glAttachShader(shader->prgid, shader->gid);
    }
    glLinkProgram(shader->prgid);
    ezValidateShaderPipeline(shader->prgid, EZ_SHADER_PROGRAM);

    glDeleteShader(shader->vid);
    glDeleteShader(shader->fid);
    glDeleteShader(shader->gid);
}

/* Direct Way to Create Shader Pipeline */
struct EZShader *ezDirectShaderPipeline(int n, ...) { /* variadic of EZShaderInfo */
    struct EZShader *shader;
    va_list ap;
    va_start(ap, n);
    shader = malloc(sizeof(struct EZShader));
    for (int i = 0; i < n; ++i) {
        struct EZShaderInfo info = va_arg(ap, struct EZShaderInfo);
        ezAddToShaderPipeline(shader, info.type, info.src);
    }

    ezFinishShaderPipeline(shader);
    return shader;
}

void ezReleaseShader(struct EZShader *shader) {
    shader->prgid = 0;
    shader->vid = 0;
    shader->fid = 0;
    shader->gid = 0;
    free(shader);
    EZ_DEBUGC(EZ_COLOR_YELLOW "Releasing a shader...\n");
}