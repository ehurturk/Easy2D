//
// Created by Emir Hürtürk on 25.07.2021.
//

#ifndef EASY2D_INPUT_H
#define EASY2D_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "window.h"
#include <GLFW/glfw3.h>

typedef void (*EZKeyInputFunc)(int, int);
typedef void (*EZMousePosInputFunc)(double, double);
typedef void (*EZMouseButtonInputFunc)(int, int);

/* Input registers */
void ezBindKeyInputFunc(EZKeyInputFunc);
void ezBindMouseInputFunc(EZMousePosInputFunc);
void ezBindMouseButtonInputFunc(EZMouseButtonInputFunc);

/* Non-API Function that registers the glfw input callback - needs window */
void ezGLFWKeyInputCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void ezGLFWMouseInputCallback(GLFWwindow *window, double xpos, double ypos);
void ezGLFWMBInputCallback(GLFWwindow *window, int button, int action, int mods);



#ifdef __cplusplus
}
#endif

#endif//EASY2D_INPUT_H
