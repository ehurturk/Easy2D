//
// Created by Emir Hürtürk on 15.08.2021.
//

#ifndef EASY2D_SCRIPT_H
#define EASY2D_SCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stl/vector.h"
#include <stdint.h>
#include <sys/stat.h>

#define CC "gcc"

struct EZSprite;

typedef size_t (*get_instance_size_func)();
typedef void (*on_plugin_reload_func)(void *ptr, struct EZSprite *parent);
typedef void (*on_plugin_update_func)(void *instance);

struct EZScript {
    void *dll_handle;
    void *instance;
    const char *w_lib_path, *s_lib_path;
    uint64_t lib_mod_time;
    size_t instance_size;
    const char *name;
    struct stat lib_stat;

    get_instance_size_func get_instance_size;
    on_plugin_reload_func on_plugin_reload; /* start function */
    on_plugin_update_func on_plugin_update; /* update function */
};

struct EZScriptManager {
    struct EZSprite *parent;
    EZVector *scripts; // script objects
    EZVector *names; // script names for filtering
};

typedef struct EZScriptManager EZScriptManager;
typedef struct EZScript EZScript;

void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager);

void ezLoadPluginFunctions(struct EZScriptManager *manager);
void ezCopyPluginLibraries(struct EZScriptManager *manager);
void ezUpdatePlugins(struct EZScriptManager *manager);

void ezScriptAddScriptName(struct EZScriptManager *manager, const char *name);

void ezDeleteManager(struct EZScriptManager *manager);

#ifdef __cplusplus
}
#endif

#endif//EASY2D_SCRIPT_H
