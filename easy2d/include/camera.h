//
// Created by Emir Hürtürk on 21.07.2021.
//

#ifndef EASY2D_CAMERA_H
#define EASY2D_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cglm/cglm.h>
#include <stdlib.h>

#include "shader.h"

typedef struct EZCamera EZCamera;

#define EZ_ORTHOGRAPHIC 0
#define EZ_PERSPECTIVE 1

void ezGetProjMatrix(struct EZCamera *cam, mat4 m);
void ezGetViewMatrix(struct EZCamera *cam, mat4 m);

void ezUpdateCamera(const struct EZCamera *cam);

struct EZCamera *ezCreateCamera(int type);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_CAMERA_H
