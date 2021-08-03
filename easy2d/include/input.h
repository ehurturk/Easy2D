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

/* cuz why not lmao */
#define EZ_KEY_A GLFW_KEY_A
#define EZ_KEY_B GLFW_KEY_B
#define EZ_KEY_C GLFW_KEY_C
#define EZ_KEY_D GLFW_KEY_D
#define EZ_KEY_E GLFW_KEY_E
#define EZ_KEY_F GLFW_KEY_F
#define EZ_KEY_G GLFW_KEY_G
#define EZ_KEY_H GLFW_KEY_H
#define EZ_KEY_I GLFW_KEY_I
#define EZ_KEY_J GLFW_KEY_J
#define EZ_KEY_K GLFW_KEY_K
#define EZ_KEY_L GLFW_KEY_L
#define EZ_KEY_L GLFW_KEY_L
#define EZ_KEY_M GLFW_KEY_M
#define EZ_KEY_N GLFW_KEY_N
#define EZ_KEY_O GLFW_KEY_O
#define EZ_KEY_P GLFW_KEY_P
#define EZ_KEY_S GLFW_KEY_S
#define EZ_KEY_R GLFW_KEY_R
#define EZ_KEY_Q GLFW_KEY_Q
#define EZ_KEY_T GLFW_KEY_T
#define EZ_KEY_U GLFW_KEY_U
#define EZ_KEY_V GLFW_KEY_V
#define EZ_KEY_W GLFW_KEY_W
#define EZ_KEY_X GLFW_KEY_X
#define EZ_KEY_Y GLFW_KEY_Y
#define EZ_KEY_Z GLFW_KEY_Z

#define EZ_KEY_ESCAPE GLFW_KEY_ESCAPE

#define EZ_KEY_CLICK GLFW_PRESS
#define EZ_KEY_HOLD GLFW_REPEAT
#define EZ_KEY_RELEASE GLFW_RELEASE

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
