//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_SPRITE_H
#define EASY2D_SPRITE_H

#ifdef __cplusplus
extern "C" { /* name mangling */
#endif

#include <stdlib.h>
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <cglm/cglm.h>

typedef struct EZSprite EZSprite;

/* TODO: Populate this layout once new features are added. */
struct VertexLayout {
    int positionCount;
    int uvCount;
};

struct EZSprite *ezCreateSpriteWithVertices(const float *vertices, size_t vsize, const unsigned int *indices, size_t isize, size_t vertexSize, struct VertexLayout layout);
struct EZSprite *ezSquareSprite(float x, float y, float z, float w, float h);

void ezSetSpriteShader(struct EZSprite *sprite, struct EZShader *shader);
void ezSetSpriteTexture(struct EZSprite *sprite, struct EZTexture *texture);

void ezTranslateSprite(struct EZSprite *sprite, vec3 xyz);
void ezScaleSprite(struct EZSprite *sprite, vec3 xyz);
void ezRotateSprite(struct EZSprite *sprite, float angle_d);

void ezSetSpritePosition(struct EZSprite *sprite, float x, float y);

/* Getters - Since structs (besides EZApplication) are opaque types */
struct EZShader *ezGetSpriteShader(const struct EZSprite *sprite);
struct EZTexture **ezGetSpriteTextures(const struct EZSprite *sprite);
struct EZTexture *ezGetSpriteTextureAt(const struct EZSprite *sprite, int i);
unsigned int ezGetSpriteTextureIDAt(const struct EZSprite *sprite, int i);
unsigned int ezGetSpriteVAO(const struct EZSprite *sprite);
unsigned int ezGetSpriteVBO(const struct EZSprite *sprite);
unsigned int ezGetSpriteEBO(const struct EZSprite *sprite);
unsigned int ezGetSpriteIndexCount(const struct EZSprite *sprite);
unsigned int ezGetSpriteVertexCount(const struct EZSprite *sprite);
unsigned int ezGetSpriteTextureSlots(const struct EZSprite *sprite);
struct EZTransform *ezGetSpriteTransform(const struct EZSprite *sprite);

void ezReleaseSprite(struct EZSprite *sprite);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SPRITE_H
