//
// Created by Emir Hürtürk on 21.07.2021.
//

#include "camera.h"
#include "application.h"

struct EZCamera {
    mat4 proj;
    mat4 view;
    mat4 model;

    vec3 pos;
};

void ezGetProjMatrix(struct EZCamera *cam, mat4 m) {
    glm_mat4_copy(cam->proj, m);
}

void ezGetModelMatrix(struct EZCamera *cam, mat4 m) {
    glm_mat4_copy(cam->model, m);
}

void ezGetViewMatrix(struct EZCamera *cam, mat4 m) {
    glm_mat4_copy(cam->view, m);
}


struct EZCamera *ezCreateCamera(int type) {
    extern struct EZApplication *app;
    struct EZCamera *cam = malloc(sizeof(struct EZCamera));
    switch (type) {
        case EZ_ORTHOGRAPHIC:
            /* proj mat in orthographic mode */
            glm_ortho(0.0f, ezGetWindowConfig(app->window).width, ezGetWindowConfig(app->window).height, 0.0f, -1.0f, 1.0f, cam->proj);
            break;
        case EZ_PERSPECTIVE:
            glm_perspective(glm_rad(45), (float) ezGetWindowConfig(app->window).width / (float) ezGetWindowConfig(app->window).height, -1.0f, 100.0f, cam->proj);
            break;
        default:
            break;
    }

    glm_mat4_identity(cam->model);
    glm_mat4_identity(cam->view);

    cam->pos[0] = 0.0f; /* x */
    cam->pos[1] = 0.0f; /* y */
    cam->pos[2] = -0.5f; /* z */

    return cam;
}
