//
// Created by Emir Hürtürk on 25.07.2021.
//

#include "input.h"
#include "application.h"
#include "scene.h"
#include "sprite.h"
#include <stdio.h>

struct EZInputManager {
    EZKeyInputFunc kfunc;
    EZMousePosInputFunc mpfunc;
    EZMouseButtonInputFunc mbfunc;
};

struct EZInputManager manager;

/* Input registers */
void ezBindKeyInputFunc(EZKeyInputFunc func) {
    manager.kfunc = func;
}

void ezBindMouseInputFunc(EZMousePosInputFunc func) {
    manager.mpfunc = func;
}

void ezBindMouseButtonInputFunc(EZMouseButtonInputFunc func) {
    manager.mbfunc = func;
}

/* Non-API Function that registers the glfw input callback - needs window */
void ezGLFWKeyInputCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    extern struct EZScene *scene;
    for (int i = 0; i< ezVectorTotal(scene->vec); i++)
    {
        struct EZSprite *spr = ezVectorGet(scene->vec, i);
        ezUpdateSpriteInput(spr, key, action);
    }
//    if (manager.kfunc != NULL)
//        manager.kfunc(key, action);
}

void ezGLFWMouseInputCallback(GLFWwindow *window, double xpos, double ypos) {
    if (manager.mpfunc != NULL)
        manager.mpfunc(xpos, ypos);
}

void ezGLFWMBInputCallback(GLFWwindow *window, int button, int action, int mods) {
    if (manager.mbfunc != NULL)
        manager.mbfunc(button, action);
}

int ezIsKeyDown(int key) {
    extern struct EZApplication *app;
    return glfwGetKey(ezGetNativeWindow(app->window), key) == GLFW_PRESS || glfwGetKey(ezGetNativeWindow(app->window), key) == GLFW_REPEAT;
}
