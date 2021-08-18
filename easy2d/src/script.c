//
// Created by Emir Hürtürk on 15.08.2021.
//

#include "script.h"
#include "sprite.h"
#include "log.h"
#include <stdio.h>
#include <dlfcn.h>

/* NOTE: This assumes that the project structure is like the following:
 *
 * your_project_dir:
 *     -> your_build_dir:
 *         -> executable
 *         -> other stuff
 *     -> your_scripts_or_other_dirs
 *
 *  Note that the executable must be in the build directory.
 *  The program would generate the runtime_libs folder inside the build directory to place the dynamic libraries
 *
 *  The updated project structure would be:
 *
 *  your_project_dir:
 *     -> your_build_dir:
 *         -> executable
 *         -> runtime_libs:
 *             -> the dynamic libraries
 *         -> other stuff
 *     -> your_scripts_or_other_dirs
 *
*/
void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager) {
    manager->parent = parent;

    system("mkdir -p ./runtime_libs");
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        char cmd[100], libname[100];
        sprintf(cmd, CC" -shared ../%s -o ./runtime_libs/lib%s.so -lEasy2D", script->src, script->name);
        sprintf(libname, "./runtime_libs/lib%s.so", script->name);

//        FILE *file;
//        if ((file = fopen(libname, "r")))
//        {
//            /* file exists */
//            fclose(file);
//        }
//        else
//        {
//            system(cmd);
//        }
        /* TODO:
         *  System call is expensive, so use some kind of caching system to decrease the usage of system
        */
        system(cmd);

        void *lib = dlopen(libname, RTLD_LAZY);
        if (lib) {
            ezVectorPushBack(manager->libs, lib);
            int (*update)(struct EZSprite *) = (int (*)(struct EZSprite *)) dlsym ( lib, "update" );
            if (update) {
                // use function
                script->update = update;
            }

            int (*start)(struct EZSprite *) = (int (*)(struct EZSprite *)) dlsym(lib, "start");
            if (start) {
                script->start = start;
            }

        }
        else {
            EZ_ERRORF_RAW("[EZ2D:ERROR]: Dynamic library not found at path: %s\n", libname);
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
        script->start(manager->parent);
    }
}

void ezUpdateScripts(const struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *script = (struct EZScript *) ezVectorGet(manager->scripts, i);
        script->update(manager->parent);
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