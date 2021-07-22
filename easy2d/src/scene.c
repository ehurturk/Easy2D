//
// Created by Emir Hürtürk on 21.07.2021.
//

#include "scene.h"
#include "camera.h"
#include "log.h"
#include <stdlib.h>

struct EZScene {
    struct EZCamera *cam;
    /* renderer */
    /* gameobjects */
};

int active_scene = 0;

struct EZScene *ezCreateScene() {
    if (active_scene == 1) {
        EZ_ERROR_RAW("[EZ2D:ERROR]: Can't create another scene while a scene is currently active\n");
        return NULL;
    }

    struct EZScene *scene = malloc(sizeof(struct EZScene));
    scene->cam = NULL;
    active_scene = 1;
    return scene;
}

void ezAddToScene(struct EZScene *scene, void *comp, int type) {
    switch (type) {
        case EZ_CAMERA:
            scene->cam = (struct EZCamera *) comp;
            break;
        case EZ_RENDERER:
            /* handle renderer */
            break;
        case EZ_GAMEOBJECT:
            /* handle gameobject arrays */
            break;
        default:
            break;
    }
}

void *ezGetSceneComponent(const struct EZScene *scene, int type) {
    switch (type) {
        case EZ_CAMERA:
            return scene->cam;
        case EZ_RENDERER:
            return NULL;
        case EZ_GAMEOBJECT:
            return NULL;
        default:
            return NULL;
            break;
    }
}