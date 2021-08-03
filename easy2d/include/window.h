//
// Created by Emir Hürtürk on 9.07.2021.
//

#ifndef EASY2D_WINDOW_H
#define EASY2D_WINDOW_H

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" { /* name mangling */
#endif

struct EZWindowConfig {
    const char *title;
    float width;
    float height;
    int resizable;
};

typedef struct EZWindow EZWindow;

struct EZWindow *ezCreateWindowWithConfig(struct EZWindowConfig config);
struct EZWindow *ezCreateWindow(const char *title, float width, float height, int resizable);
struct EZWindowConfig ezGetWindowConfig(const struct EZWindow *win);
GLFWwindow *ezGetNativeWindow(const struct EZWindow *win);
void ezToggleVSync(int value);
void ezSetWindowTitle(const struct EZWindow *window, const char *title);
int ezIsWindowOpen(const struct EZWindow *window);
void ezCloseWindow(const struct EZWindow *window);
void ezUpdateWindow(const struct EZWindow *window);

float ezGetFPS();

#ifdef __cplusplus
}
#endif

#endif//EASY2D_WINDOW_H
