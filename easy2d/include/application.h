//
// Created by Emir Hürtürk on 10.07.2021.
//

#ifndef EASY2D_APPLICATION_H
#define EASY2D_APPLICATION_H

#ifdef __cplusplus
extern "C" { /* name mangling */
#endif

#include "window.h"

struct EZApplication {
    struct EZWindow *window;

    void (*init)();
    void (*update)(); /* float for timestep */
    void (*destroy)();
};

struct EZApplication *ezCreateApplication();

void ezBindAppInitCallback(void (*init)());
void ezBindAppUpdateCallback(void (*update)());
void ezBindAppDestroyCallback(void (*destroy)());
void ezRegisterAsApplication(struct EZApplication *app);
void ezFreeApp(struct EZApplication *app);
void ezStart();

#ifdef __cplusplus
}
#endif

#endif//EASY2D_APPLICATION_H