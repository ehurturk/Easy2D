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

void ezCreateScene();

void ezAddToScene(void *comp, int type);
void *ezGetSceneComponent(int type);
void ezInstantiateSprite(const void *comp, float x, float y);
void ezStartScene();
void ezUpdateScene();
void *ezFindSpriteWithName(const char *name);
void ezDestroyScene();

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SCENE_H
