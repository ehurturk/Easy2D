//
// Created by Emir Hürtürk on 21.07.2021.
//

#include "scene.h"
#include "sprite.h"
#include "camera.h"
#include "log.h"
#include "stl/vector.h"
#include <stdlib.h>

struct EZScene {
    struct EZCamera *cam;
    /* renderer */
    struct EZSprite *def_spr;
    /* gameobject vector */
    EZVector *vec;
};

int active_scene = 0;

struct EZScene *ezCreateScene() {
    if (active_scene == 1) {
        EZ_ERROR_RAW("[EZ2D:ERROR]: Can't create another scene while a scene is currently active\n");
        return NULL;
    }

    struct EZScene *scene = malloc(sizeof(struct EZScene));
    scene->cam = NULL;
    scene->vec = malloc(sizeof(EZVector));
    ez_vector_init(scene->vec);
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
        case EZ_S_GAMEOBJECT:
            scene->def_spr = (struct EZSprite *) comp;
            break;
        case EZ_GAMEOBJS:
            /* handle gameobject arrays */
            ezVectorPushBack(scene->vec, comp);
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
        case EZ_S_GAMEOBJECT:
            return scene->def_spr;
        case EZ_GAMEOBJS:
            return scene->vec;
        default:
            return NULL;
            break;
    }
}

void ezDestroyScene(struct EZScene *scene) {
    free(scene->cam);
    ezReleaseSprite(scene->def_spr);
    ezVectorFree(scene->vec);
    free(scene->vec);
    free(scene);
}