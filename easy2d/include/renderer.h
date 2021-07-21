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


/* batch renderer struct could be useful in the future */

void ezRenderSprite(const struct EZSprite *sprite);
void ezClearFrame();
void ezSetBackgroundColor(float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_RENDERER_H
