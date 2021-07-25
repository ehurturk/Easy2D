//
// Created by Emir Hürtürk on 25.07.2021.
//

#include "input.h"

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
    manager.kfunc(key, action);
}

void ezGLFWMouseInputCallback(GLFWwindow *window, double xpos, double ypos) {
    manager.mpfunc(xpos, ypos);
}

void ezGLFWMBInputCallback(GLFWwindow *window, int button, int action, int mods) {
    manager.mbfunc(button, action);
}