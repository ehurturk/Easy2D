//
// Created by Emir Hürtürk on 9.07.2021.
//

#include "window.h"
#include "log.h"
#include "input.h"

int frames = 0;
double t, t0, fps;

struct EZWindow {
    GLFWwindow *nativeWindow;
    struct EZWindowConfig config; /* no need for a pointer - a basic struct which serves as a config */
};

void ezGLFWErrorCallback(int code, const char *error) {
    EZ_ERRORF_RAW("[GLFW ERROR:%i]: %s", code, error);
}

void ezFrameBufferSizeCallback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

struct EZWindow *ezCreateWindowWithConfig(struct EZWindowConfig config) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow((int)config.width, (int)config.height, config.title, NULL, NULL);
    if (window == NULL) {
        EZ_ERROR_RAW("[GLFW ERROR]: Could not initialize the window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        EZ_ERROR_RAW("[GLAD ERROR]: Could not initialize glad.\n");
        return NULL;
    }
    t0 = glfwGetTime();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); /* Cout = C1 * A1 + C2 * (1-A2) */

    glfwSetErrorCallback(ezGLFWErrorCallback);
    glfwSetFramebufferSizeCallback(window, ezFrameBufferSizeCallback);

    glfwSetKeyCallback(window, ezGLFWKeyInputCallback);
    glfwSetMouseButtonCallback(window, ezGLFWMBInputCallback);
    glfwSetCursorPosCallback(window, ezGLFWMouseInputCallback);

    struct EZWindow *ez_window = malloc(sizeof(struct EZWindow));
    ez_window->nativeWindow    = window;
    ez_window->config          = config;

    return ez_window;
}

struct EZWindow *ezCreateWindow(const char *title, float width, float height, int resizable) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, resizable);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        EZ_ERROR_RAW("[GLFW ERROR]: Could not initialize the window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    t0 = glfwGetTime();
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        EZ_ERROR_RAW("[GLAD ERROR]: Could not initialize glad.\n");
        return NULL;
    }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); /* Cout = C1 * A1 + C2 * (1-A2) */

    glfwSetErrorCallback(ezGLFWErrorCallback);
    glfwSetFramebufferSizeCallback(window, ezFrameBufferSizeCallback);

    glfwSetKeyCallback(window, ezGLFWKeyInputCallback);
    glfwSetMouseButtonCallback(window, ezGLFWMBInputCallback);
    glfwSetCursorPosCallback(window, ezGLFWMouseInputCallback);

    struct EZWindow *ez_window = malloc(sizeof(struct EZWindow));
    ez_window->nativeWindow    = window;
    ez_window->config          = (struct EZWindowConfig){.title = title, .width = width, .height = height};

    return ez_window;
}

inline struct EZWindowConfig ezGetWindowConfig(const struct EZWindow *win) {
    return win->config;
}

GLFWwindow *ezGetNativeWindow(const struct EZWindow *win) {
    return win->nativeWindow;
}

inline void ezToggleVSync(int value) {
    glfwSwapInterval(value);
}

void ezToggleWindowResize(int value) {
    glfwWindowHint(GLFW_RESIZABLE, value);
}

inline void ezSetWindowTitle(const struct EZWindow *window, const char *title) {
    glfwSetWindowTitle(window->nativeWindow, title);
}

inline int ezIsWindowOpen(const struct EZWindow *window) {
    return glfwWindowShouldClose(window->nativeWindow);
}

inline void ezCloseWindow(const struct EZWindow *window) {
    glfwSetWindowShouldClose(window->nativeWindow, 1);
}

void ezUpdateWindow(const struct EZWindow *window) {
    glfwSwapBuffers(window->nativeWindow);
    glfwPollEvents();
}

float ezGetFPS() {
    t = glfwGetTime();
    if ((t - t0) > 1.0 || frames == 0)
    {
        fps = (double)frames / (t - t0);
        t0 = t;
        frames = 0;
    }
    frames++;
    return fps;
}