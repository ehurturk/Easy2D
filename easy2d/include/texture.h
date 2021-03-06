//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_TEXTURE_H
#define EASY2D_TEXTURE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct EZTexture EZTexture;

struct EZTexture *ezLoadTexture(const char *file);
struct EZTexture *ezLoadTextureFromSpritesheet(const char *file, int x, int y, int w, int h);

unsigned int ezGetTextureId(const struct EZTexture *tex);
size_t ezGetSizeofTexture();
void ezReleaseTexture(struct EZTexture *tex);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_TEXTURE_H
