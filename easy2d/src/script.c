//
// Created by Emir Hürtürk on 15.08.2021.
//

#include "script.h"
#include "sprite.h"
#include "log.h"
#include <stdio.h>


void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager) {
    manager->parent = parent;
}

void ezStartScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->start(manager->parent);
    }
}

void ezUpdateScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->update(manager->parent);
    }
}

void ezDestroyScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->destroy(manager->parent);
    }
}


void ezDeleteManager(struct EZScriptManager *manager) {
    ezVectorFree(manager->scripts);
    free(manager->scripts);
    free(manager);
}