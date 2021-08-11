//
// Created by Emir Hürtürk on 11.08.2021.
//

#include "aabb.h"
#include "sprite.h"

struct EZAabbBoundingBox {
    float w, h;
    float x, y;
};

int ezCheckSpriteCollision(struct EZSprite *s1, struct EZSprite *s2) {
    struct EZTransform *t1 = ezGetSpriteTransform(s1);
    struct EZTransform *t2 = ezGetSpriteTransform(s2);

    if (t1->position[0] < t2->position[0] + ezGetSpriteWidth(s2) &&
        t1->position[0] + ezGetSpriteWidth(s1) > t2->position[0] &&
        t1->position[1] < t2->position[1] + ezGetSpriteHeight(s2) &&
        t1->position[1] + ezGetSpriteHeight(s1) > t2->position[1]) {
        // collision detected!
        return 1;
    }

    return 0;
}

struct EZAabbBoundingBox *ezInitAabbBoundingBox(float w, float h, float x, float y) {
    struct EZAabbBoundingBox *box = malloc(sizeof(struct EZAabbBoundingBox));
    box->w = w;
    box->h = h;
    box->x = x;
    box->y = y;
    return box;
}
