//
// Created by Emir Hürtürk on 11.08.2021.
//

#ifndef EASY2D_AABB_H
#define EASY2D_AABB_H

#ifdef __cplusplus
extern "C" {
#endif

struct EZSprite;

typedef struct EZAabbBoundingBox EZAabbBoundingBox;

int ezCheckSpriteCollision(struct EZSprite *s1, struct EZSprite *s2);
struct EZAabbBoundingBox *ezInitAabbBoundingBox(float w, float h, float x, float y);

#ifdef __cplusplus
};
#endif

#endif//EASY2D_AABB_H

