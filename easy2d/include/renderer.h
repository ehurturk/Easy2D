//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_RENDERER_H
#define EASY2D_RENDERER_H

#include "sprite.h"
#include "shader.h"
#include "texture.h"

#ifdef __cplusplus
extern "C" {
#endif


void ezRenderSprite(const struct EZSprite *sprite);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_RENDERER_H
