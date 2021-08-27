//
// Created by Emir Hürtürk on 11.08.2021.
//

#ifndef EASY2D_AABB_H
#define EASY2D_AABB_H

#ifdef __cplusplus
extern "C" {
#endif


struct EZAabbBoundingBox {
    float w, h;
    float x, y;
    int trigger;
};

int ezCheckAabbCollision(struct EZAabbBoundingBox *b1, struct EZAabbBoundingBox *b2);
struct EZAabbBoundingBox *ezInitAabbBoundingBox(float w, float h, float x, float y);

#ifdef __cplusplus
};
#endif

#endif//EASY2D_AABB_H

