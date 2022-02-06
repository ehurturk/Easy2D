//
// Created by Emir Hürtürk on 11.08.2021.
//

#include "aabb.h"
#include "sprite.h"

int ezCheckAabbCollision(struct EZAabbBoundingBox *b1, struct EZAabbBoundingBox *b2) {
    if (b1->trigger == 0 && b2->trigger == 0) {
        if (b1->x <= b2->x + b2->w &&
            b1->x + b1->w >= b2->x &&
            b1->y <= b2->y + b2->h &&
            b1->y + b1->h >= b2->y) {
            // collision detected!
            printf("collision\n");
            return 1;
        }
    }
    return 0;
}

struct EZAabbBoundingBox *ezInitAabbBoundingBox(float w, float h, float x, float y) {
    struct EZAabbBoundingBox *box = malloc(sizeof(struct EZAabbBoundingBox));
    box->w = w;
    box->h = h;
    box->x = x;
    box->y = y;
    box->trigger = 0;
    return box;
}
