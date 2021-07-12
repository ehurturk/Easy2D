//
// Created by Emir Hürtürk on 10.07.2021.
//
#include <stdio.h>

#include "application.h"
#include "log.h"

struct EZApplication *app; /* only one application can run at one time */

void ezBindAppInitCallback(void (*init)()) {
    if (app == NULL) {
        EZ_ERROR_RAW("[EZ2D:ERROR]: Application is null. First, register your application using ezRegisterAsApplication(), then run ezStart()\n");
        return;
    }
    app->init = init;
}
void ezBindAppUpdateCallback(void (*update)()) {
    if (app == NULL) {
        EZ_ERROR_RAW( "[EZ2D:ERROR]: Application is null. First, register your application using ezRegisterAsApplication(), then run ezStart()\n");
        return;
    }
    app->update = update;
}
void ezBindAppDestroyCallback(void (*destroy)()) {
    if (app == NULL) {
        EZ_ERROR_RAW("[EZ2D:ERROR]: Application is null. First, register your application using ezRegisterAsApplication(), then run ezStart()\n");
        return;
    }
    app->destroy = destroy;
}

struct EZApplication *ezCreateApplication() {
    struct EZApplication *app = malloc(sizeof(struct EZApplication));
    return app;
}

void ezRegisterAsApplication(struct EZApplication *ezApp) {
    app = ezApp;
}

void ezFreeApp(struct EZApplication *app) {
    free(app->window);
    free(app);
}

/* entry point for starting */
void ezStart() {
    EZ_DEBUGC_RAW( EZ_COLOR_BOLD_BLUE "[Easy2D]: " EZ_COLOR_GREEN
                                                  "Starting up the application....\n");
    if (app == NULL) {
        EZ_ERROR_RAW( "[EZ2D:ERROR]: Application is null. First, register your application using ezRegisterAsApplication(), then run ezStart()\n");
        return;
    }

    app->init();
    EZ_DEBUGC_RAW(EZ_COLOR_BOLD_BLUE "[Easy2D]: " EZ_COLOR_GREEN
                                                  "App has been successfully started up.\n");
    app->update(); /* while loop in this function */
    app->destroy();
}
