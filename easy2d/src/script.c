//
// Created by Emir Hürtürk on 15.08.2021.
//

#include "script.h"
#include "sprite.h"
#include <stdio.h>
#include <dlfcn.h>

void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager) {
    manager->parent = parent;
    system("mkdir -p ./runtime_libs");
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        char cmd[100], libname[100];
        sprintf(cmd, CC" -shared ../%s -o ./runtime_libs/lib%s.so -lEasy2D", script->src, script->name);
        system(cmd);
        sprintf(libname, "./runtime_libs/lib%s.so", script->name);


        void *lib = dlopen(libname, RTLD_LAZY);
        if (lib) {
            ezVectorPushBack(manager->libs, lib);
            int (*update)(void) = (int (*)()) dlsym ( lib, "update" );
            if (update) {
                // use function
                script->update = update;
                update();
            }

            int (*start)(struct EZSprite *) = (int (*)(struct EZSprite *)) dlsym(lib, "start");
            if (start) {
                script->start = start;
            }

        }
        else {
            printf("lib not found at path: %s\n", libname);
        }
    }
}

struct EZScript *ezInitScript(const char *path, const char *name) {
    struct EZScript *script = malloc(sizeof(struct EZScript));
    script->src = path;
    script->name = name;
    return script;
}

void ezStartScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->start(manager->parent); /* seg fault */
    }
}

void ezUpdateScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->update();
    }
}

void ezDeleteScript(struct EZScript *script) {
    free(script);
}

void ezDeleteManager(struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->libs); i++) {
        dlclose((void *)ezVectorGet(manager->libs, i));
    }
    ezVectorFree(manager->scripts);
    ezVectorFree(manager->libs);
    free(manager->scripts);
    free(manager->libs);
    free(manager);
}