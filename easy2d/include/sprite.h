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

#define EZ_LOCAL_REF 0
#define EZ_WORLD_REF 1

#define EZ_SQUARE 0
#define EZ_EMPTY_GAMEOBJ 1

#define EZ_NOT_RENDERABLE -9999

typedef struct EZSprite EZSprite;

/* TODO: Populate this layout once new features are added. */
struct VertexLayout {
    int positionCount;
    int uvCount;
};

struct EZSprite *ezCreateSpriteWithVertices(const float *vertices, size_t vsize, const unsigned int *indices, size_t isize, size_t vertexSize, struct VertexLayout layout);
struct EZSprite *ezSquareSprite(const char *name, float x, float y, float z, float w, float h);
struct EZSprite *ezEmptySprite(int type, const char *name, float x, float y, float z);

void ezSetSpriteShader(struct EZSprite *sprite, struct EZShader *shader);
void ezSetSpriteTexture(struct EZSprite *sprite, struct EZTexture *texture);

void ezTranslateSprite(struct EZSprite *sprite, vec3 xyz, int mode);
void ezScaleSprite(struct EZSprite *sprite, vec3 xyz);
void ezRotateSprite(struct EZSprite *sprite, float angle_d);

void ezInitSprite(const struct EZSprite *sprite);
void ezStartSprite(const struct EZSprite *sprite);
void ezUpdateSprite(const struct EZSprite *sprite);

int ezCheckSpriteCollision(const struct EZSprite *s1, const struct EZSprite *s2);

void ezSetSpritePosition(struct EZSprite *sprite, float x, float y);
void ezMakeSpriteActive(struct EZSprite *sprite);

/* a bridge to actual code */
void ezSpriteAddScript(struct EZSprite *sprite, const char *path, const char *name);

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
unsigned int ezIsSpriteActive(const struct EZSprite *sprite);
const char *ezGetSpriteName(const struct EZSprite *sprite);
float ezGetSpriteWidth(const struct EZSprite *s);
float ezGetSpriteHeight(const struct EZSprite *s);
struct EZTransform *ezGetSpriteTransform(const struct EZSprite *sprite);

void ezReleaseSprite(struct EZSprite *sprite);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SPRITE_H
