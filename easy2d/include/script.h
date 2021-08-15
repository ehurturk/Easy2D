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
    const char *src;
    const char *name;
    int (*update)(struct EZSprite *sprite);
    int (*start)(struct EZSprite *sprite);
};

struct EZScriptManager {
    struct EZSprite *parent;
    EZVector *scripts;
    EZVector *libs;
};

typedef struct EZScriptManager EZScriptManager;
typedef struct EZScript EZScript;

void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager);
struct EZScript *ezInitScript(const char *path, const char *name);

void ezStartScripts(const struct EZScriptManager *manager);
void ezUpdateScripts(const struct EZScriptManager *manager);

void ezDeleteScript(struct EZScript *script);
void ezDeleteManager(struct EZScriptManager *manager);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SCRIPT_H
