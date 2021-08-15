//
// Created by Emir Hürtürk on 21.07.2021.
//

#ifndef EASY2D_SCENE_H
#define EASY2D_SCENE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EZScene EZScene;

#define EZ_CAMERA 0
#define EZ_RENDERER 1
#define EZ_S_GAMEOBJECT 2
#define EZ_GAMEOBJS 3

struct EZScene *ezCreateScene();

void ezAddToScene(struct EZScene *scene, void *comp, int type);
void *ezGetSceneComponent(const struct EZScene *scene, int type);
void ezInstantiateSprite(struct EZScene *scene, const void *comp, float x, float y);
void ezStartScene(const struct EZScene *scene);
void ezUpdateScene(const struct EZScene *scene);
void *ezFindSpriteWithName(const struct EZScene *scene, const char *name);
void ezDestroyScene(struct EZScene *scene);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SCENE_H
