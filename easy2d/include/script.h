//
// Created by Emir Hürtürk on 15.08.2021.
//

#ifndef EASY2D_SCRIPT_H
#define EASY2D_SCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stl/vector.h"

#define CC "gcc"

struct EZSprite;

struct EZScript {
    void (*update)(struct EZSprite *sprite);
    void (*start)(struct EZSprite *sprite);
    void (*destroy)(struct EZSprite *sprite);

    void (*key_input)(int key, int action);
};

struct EZScriptManager {
    struct EZSprite *parent;
    EZVector *scripts;
};

/* This must be called inside the additional script. */
#define EZ_INIT_SCRIPT(name, startfn, updatefn, destroyfn, keyfn)        \
struct EZScript *name;             \
void init##name() {                 \
    (name) = (struct EZScript *)malloc(sizeof(struct EZScript));                                \
    (name)->start = startfn;            \
    (name)->update = updatefn;        \
    (name)->destroy = destroyfn;      \
    (name)->key_input = keyfn;                                \
}

/* This must be called inside your driver file (i.e main.cpp or main.c) to ensure that the scripts are initialized and their corresponding functions will be called */
#define EZ_INITIALIZE_SCRIPT(name) init##name();

typedef struct EZScriptManager EZScriptManager;
typedef struct EZScript EZScript;

void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager);

void ezStartScripts(const struct EZScriptManager *manager);
void ezUpdateScripts(const struct EZScriptManager *manager);
void ezCallInputScripts(const struct EZScriptManager *manager, int key, int action);
void ezDestroyScripts(const struct EZScriptManager *manager);

void ezDeleteManager(struct EZScriptManager *manager);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SCRIPT_H
