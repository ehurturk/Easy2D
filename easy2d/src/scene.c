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
    }
}

void *ezFindSpriteWithName(const struct EZScene *scene, const char *name) {
    for (int i = 0; i < ezVectorTotal(scene->vec); i++) {
        struct EZSprite *spr = (struct EZSprite *) ezVectorGet(scene->vec, i);
        if (ezGetSpriteName(spr) == name) {
            return (void *) spr;
        }
    }
    return NULL;
}

void ezInstantiateSprite(struct EZScene *scene, const void *comp, float x, float y) {
    ezAddToScene(scene, comp, EZ_GAMEOBJS);
    ezSetSpritePosition((struct EZSprite *) comp, x, y);
}

void ezDestroyScene(struct EZScene *scene) {
    free(scene->cam);
    EZVector *vec = (EZVector *) ezGetSceneComponent(scene, EZ_GAMEOBJS);
    for (int i = 0; i < ezVectorTotal(vec); i++) {
        ezReleaseSprite((struct EZSprite *) ezVectorGet(vec, i));
    }
    ezVectorFree(scene->vec);
    free(scene->vec);
    free(scene);
}