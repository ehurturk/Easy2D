//
// Created by Emir Hürtürk on 20.07.2021.
//

#include "transform.h"
#include <stdlib.h>


struct EZTransform *ezInitTransform() {
    struct EZTransform *tr = malloc(sizeof(struct EZTransform));
    glm_mat4_identity(tr->model);
    for (int i = 0; i < 3; i++) {
        tr->position[i] = 0.0f;
        tr->rotation[i] = 0.0f;
        tr->scale[i] = 1.0f; /* must be 1.0f as default */
    }

    return tr;
}

void ezGetTransformModel(struct EZTransform *transform, mat4 mat) {
    glm_mat4_copy(transform->model, mat);
}

/* Model matrix is:
 *
 * scale.x      0       0       pos.x
 * 0        scale.y     0       pos.y
 * 0            0     scale.z   pos.z
 * 0            0       0       1
 *
 * */