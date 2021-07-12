//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_TEXTURE_H
#define EASY2D_TEXTURE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EZTexture EZTexture;

struct EZTexture *ezLoadTexture(const char *file);

void ezReleaseTexture(struct EZTexture *tex);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_TEXTURE_H
