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
    int width;
    int height;
};

struct EZWindow {
    GLFWwindow *nativeWindow;
    struct EZWindowConfig config; /* no need for a pointer - a basic struct which serves as a config */
};

struct EZWindow *ezCreateWindowWithConfig(struct EZWindowConfig config);
struct EZWindow *ezCreateWindow(const char *title, int width, int height);
void ezToggleVSync(int value);
void ezSetWindowTitle(const struct EZWindow *window, const char *title);
int ezIsWindowOpen(const struct EZWindow *window);
void ezCloseWindow(const struct EZWindow *window);
void ezUpdateWindow(const struct EZWindow *window);
void ezGetFPS();

#ifdef __cplusplus
}
#endif

#endif//EASY2D_WINDOW_H
