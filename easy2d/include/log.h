//
// Created by Emir Hürtürk on 9.07.2021.
//

#ifndef EASY2D_LOG_H
#define EASY2D_LOG_H

#define EZ_DEBUG_ENABLED /* TODO: Undef this */

#include <stdio.h>
#include <string.h>

#ifndef __WIN32
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#define EZ_ANSI_COLOR_RED     "\\u001b[31m"
#define EZ_ANSI_COLOR_BLACK   "\\u001b[30m"
#define EZ_ANSI_COLOR_GREEN   "\\u001b[32m"
#define EZ_ANSI_COLOR_CYAN    "\\u001b[36m"
#define EZ_ANSI_COLOR_BLUE    "\\u001b[34m"
#define EZ_ANSI_COLOR_MAGENTA "\\u001b[35m"
#define EZ_ANSI_COLOR_YELLOW  "\\u001b[33m"
#define EZ_ANSI_COLOR_WHITE   "\\u001b[37m"

#define EZ_ANSI_COLOR(x) "\\u001b[38;5;"##x "m"

#define EZ_ANSI_BOLD      "\\u001b[1m"
#define EZ_ANSI_UNDERLINE "\\u001b[4m"


#ifdef EZ_DEBUG_ENABLED
#define EZ_DEBUG(fmtStr)       printf("%s:%d> " fmtStr, __FILENAME__, __LINE__)
#define EZ_DEBUGF(fmtStr, ...) printf("%s:%d> " fmtStr, __FILENAME__, __LINE__, __VA_ARGS__)
#define EZ_DEBUGC(fmtStr)                                                          \
    do {                                                                           \
        printf(EZ_DEBUG_COLOR_BOLD_BLUE "%s:%d> " fmtStr, __FILENAME__, __LINE__); \
        printf("\\u001b[0m");                                                      \
    } while (0)
#define EZ_DEBUGCF(fmtStr, ...)                                                                 \
    do {                                                                                        \
        printf(EZ_DEBUG_COLOR_BOLD_BLUE "%s:%d> " fmtStr, __FILENAME__, __LINE__, __VA_ARGS__); \
        printf("\\u001b[0m");                                                                   \
    } while (0)
#define EZ_DEBUG_RAW(fmtStr)       printf("%s", fmtStr)
#define EZ_DEBUGF_RAW(fmtStr, ...) printf("" fmtStr, __VA_ARGS__)
#define EZ_DEBUGC_RAW(fmtStr) \
    do {                      \
        printf("" fmtStr);    \
        printf("\\u001b[0m"); \
    } while (0)
#define EZ_DEBUGCF_RAW(fmtStr, ...)     \
    do {                                \
        printf("" fmtStr, __VA_ARGS__); \
        printf("\\u001b[0m");           \
    } while (0)
#else
#define EZ_DEBUGF(fmtStr, ...)
#define EZ_DEBUG(fmtStr)
#define EZ_DEBUGC(color, fmtStr)
#define EZ_DEBUGCF(color, fmtStr, ...)
#define EZ_DEBUG_RAW(fmtStr)
#define EZ_DEBUGC_RAW(fmtStr)
#define EZ_DEBUGF_RAW(fmtStr, ...)
#define EZ_DEBUGCF_RAW(fmtStr, ...)
#endif

#endif//EASY2D_LOG_H
