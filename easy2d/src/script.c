//
// Created by Emir Hürtürk on 15.08.2021.
//

#include "script.h"
#include "sprite.h"
#include "log.h"
#include <stdio.h>

#include <sys/dir.h>
#include <sys/dirent.h>
#include <dlfcn.h>
#include <unistd.h>

DIR *dir;
struct dirent *ent;

void ezLoadPluginFunctions(struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        EZScript *plugin = ezVectorGet(manager->scripts, i);
        plugin->dll_handle = dlopen(plugin->w_lib_path, RTLD_NOW);
        if (plugin->dll_handle == NULL) {
            fprintf(stderr, "Failed to load library: %s\n", plugin->w_lib_path);
            return;
        }
        plugin->get_instance_size =
                (get_instance_size_func)dlsym(plugin->dll_handle, "GetInstanceSize");
        plugin->on_plugin_reload =
                (on_plugin_reload_func)dlsym(plugin->dll_handle, "OnReload");
        plugin->on_plugin_update =
                (on_plugin_update_func)dlsym(plugin->dll_handle, "OnUpdate");

        if (plugin->get_instance_size == NULL)
            EZ_ERRORF_RAW("Function named GetInstanceSize does not exist inside the lib %s.\n", plugin->w_lib_path);
        if (plugin->on_plugin_reload == NULL)
            EZ_ERRORF_RAW("Function named OnReload does not exist inside the lib %s.\n", plugin->w_lib_path);
        if (plugin->on_plugin_update == NULL)
            EZ_ERRORF_RAW("Function named OnUpdate does not exist inside the lib %s.\n", plugin->w_lib_path);
    }
}

void ezCopyPluginLibraries(struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        EZScript *plug = ezVectorGet(manager->scripts, i);
        FILE *src, *dst;
        size_t size, read, j;
        char buffer[2048];

        src = fopen(plug->s_lib_path, "rb");
        dst = fopen(plug->w_lib_path, "wb");

        fseek(src, 0, SEEK_END);
        size = ftell(src);
        fseek(src, 0, SEEK_SET);

        for (j = 0; j < size; j += 2048) {
            read = fread(buffer, 1, 2048, src);
            fwrite(buffer, read, 1, dst);
        }

        fclose(src);
        fclose(dst);
    }
}


void ezUpdatePlugins(struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        struct EZScript *plug = ezVectorGet(manager->scripts, i);
        if (stat(plug->s_lib_path, &plug->lib_stat) == 0) {
            if (plug->lib_stat.st_mtime > plug->lib_mod_time) {
                // if multiple sprites use the same dll, the update function doesn't work.
                if (plug->dll_handle)
                    dlclose(plug->dll_handle);

                ezCopyPluginLibraries(manager);
                ezLoadPluginFunctions(manager);

                size_t new_size = plug->get_instance_size();

                if (new_size != plug->instance_size) {
                    plug->instance = realloc(plug->instance, new_size);

                    if (new_size > plug->instance_size)
                        memset((char *)plug->instance + plug->instance_size, 0,
                               new_size - plug->instance_size);
                    plug->instance_size = new_size;
                }

                plug->lib_mod_time = plug->lib_stat.st_mtime;
                plug->on_plugin_reload(plug->instance, manager->parent);
            }

        }
        plug->on_plugin_update();
    }
}

void ezInitScriptManager(struct EZSprite *parent, struct EZScriptManager *manager) {
    manager->parent = parent;
    /* get the name of all plugins and then initialize them and add to the vector
   */

    if ((dir = opendir("./bin/compiled_libs/")) != NULL) {
        int i = 0;
        while ((ent = readdir(dir)) != NULL) {
          i++;
          const char *libname = ent->d_name;
          if (i > 2) {
              for (int j = 0; j < ezVectorTotal(manager->names); j++) {
                  if (strcmp(ezVectorGet(manager->names, j), libname) == 0) { // if the name is equal to the lib name
                      char *w_rel_path = malloc(sizeof(char) * 60),
                              *s_rel_path = malloc(sizeof(char) * 60);
                      strcpy(w_rel_path, "./bin/runtime_libs/");
                      strcpy(s_rel_path, "./bin/compiled_libs/");
                      strcat(w_rel_path, libname);
                      strcat(s_rel_path, libname);
                      EZScript *plugin = malloc(sizeof(EZScript));
                      plugin->w_lib_path = w_rel_path;
                      plugin->s_lib_path = s_rel_path;
                      plugin->dll_handle = NULL;
                      plugin->lib_mod_time = 0;
                      plugin->get_instance_size = NULL;
                      plugin->on_plugin_reload = NULL;
                      plugin->on_plugin_update = NULL;
                      plugin->instance_size=1; /* default 1 byte plugin */
                      plugin->instance = malloc(plugin->instance_size);
                      plugin->name = libname;
                      ezVectorPushBack(manager->scripts, plugin);
                  }
              }

          }
        }
        closedir(dir);
    } 
    else {
        printf("No plugin is found...\n");
        exit(1);
    }
}

void ezScriptAddScriptName(struct EZScriptManager *manager, const char *name) {
    // TODO: Script Filtering system.
    // Ex: add this script to only one sprite.
    // I am thinking about storing all names and comparing these names with the script names.
    // ezSpriteAddScript(sprite, "libscript1.so");
    ezVectorPushBack(manager->names, (void*) name);
}

void ezDeleteManager(struct EZScriptManager *manager) {
    for (int i = 0; i < ezVectorTotal(manager->scripts); i++) {
        free((void*)((EZScript *)ezVectorGet(manager->scripts, i))->w_lib_path);
        free((void*)((EZScript *)ezVectorGet(manager->scripts, i))->s_lib_path);
        free(((EZScript *)ezVectorGet(manager->scripts, i))->instance);
        free(((EZScript *)ezVectorGet(manager->scripts, i)));
    }

    ezVectorFree(manager->scripts);
    ezVectorFree(manager->names);
    free(manager->scripts);
    free(manager->names);
    free(manager);
}
