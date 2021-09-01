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
//    printf("hmm - started\n");
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        if (script != NULL)
            script->update(manager->parent);
    }
//    printf("hmm - finished\n");
}

void ezDestroyScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->destroy(manager->parent);
    }
}

void ezCallInputScripts(const struct EZScriptManager *manager, int key, int action) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->key_input(key, action);
    }
}

void ezDeleteManager(struct EZScriptManager *manager) {
    ezVectorFree(manager->scripts);
    free(manager->scripts);
    free(manager);
}