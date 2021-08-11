//
// Created by Emir Hürtürk on 11.07.2021.
//

#ifndef EASY2D_UTIL_H
#define EASY2D_UTIL_H

#include "log.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ASSERTF(x, msg, ...)                                   \
    do {                                                      \
        if (!(x)) {                                           \
            EZ_ERRORF_RAW(msg, __VA_ARGS__); \
            assert(x);                                        \
        }                                                     \
    } while (0)

#define ASSERT(x, msg)                                   \
    do {                                                      \
        if (!(x)) {                                           \
            EZ_ERROR_RAW(msg); \
            assert(x);                                        \
        }                                                     \
    } while (0)

#define EZ_VEC3(a, x, y, z) vec3 a; \
a[0] = x;                           \
a[1] = y;                           \
a[2] = z;

#ifdef __cplusplus
}
#endif

#endif//EASY2D_UTIL_H
