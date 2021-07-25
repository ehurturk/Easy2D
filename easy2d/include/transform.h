//
// Created by Emir Hürtürk on 20.07.2021.
//

#ifndef EASY2D_TRANSFORM_H
#define EASY2D_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cglm/cglm.h>

struct EZTransform {
    mat4 model;
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

typedef struct EZTransform EZTransform;

struct EZTransform *ezInitTransform();

void ezGetTransformModel(struct EZTransform* transform, mat4 mat);


#ifdef __cplusplus
}
#endif

#endif//EASY2D_TRANSFORM_H
