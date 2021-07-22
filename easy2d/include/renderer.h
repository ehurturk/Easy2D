//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_RENDERER_H
#define EASY2D_RENDERER_H

#include "sprite.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "scene.h"

#ifdef __cplusplus
extern "C" {
#endif


/* batch renderer struct could be useful in the future */

void ezRenderSprite(const struct EZSprite *sprite, const struct EZCamera *cam);
void ezRenderScene(const struct EZScene *scene);
void ezClearFrame();
void ezSetBackgroundColor(float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_RENDERER_H
