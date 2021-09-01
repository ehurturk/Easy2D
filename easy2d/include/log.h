//
// Created by Emir Hürtürk on 9.07.2021.
//

#ifndef EASY2D_LOG_H
#define EASY2D_LOG_H

//#define EZ_DEBUG_ENABLED /* TODO: Undef this */

#include <stdio.h>
#include <string.h>

#ifndef __WIN32
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#define EZ_COLOR_BLACK     "\033[0;30m"
#define EZ_COLOR_RED   "\033[0;31m"
#define EZ_COLOR_GREEN   "\033[0;32m"
#define EZ_COLOR_YELLOW    "\033[0;33m"
#define EZ_COLOR_BLUE    "\033[0;34m"
#define EZ_COLOR_PURPLE "\033[0;35m"
#define EZ_COLOR_CYAN  "\033[0;36m"
#define EZ_COLOR_WHITE   "\033[0;37m"

#define EZ_COLOR_BOLD_BLACK     "\033[1;30m"
#define EZ_COLOR_BOLD_RED   "\033[1;31m"
#define EZ_COLOR_BOLD_GREEN   "\033[1;32m"
#define EZ_COLOR_BOLD_YELLOW    "\033[1;33m"
#define EZ_COLOR_BOLD_BLUE    "\033[1;34m"
#define EZ_COLOR_BOLD_PURPLE "\033[1;35m"
#define EZ_COLOR_BOLD_CYAN  "\033[1;36m"
#define EZ_COLOR_BOLD_WHITE   "\033[1;37m"

#define EZ_COLOR_RESET "\033[0m"

#ifdef EZ_DEBUG_ENABLED
#define EZ_DEBUG(fmtStr)       printf("%s:%d> " fmtStr, __FILENAME__, __LINE__)
#define EZ_DEBUGF(fmtStr, ...) printf("%s:%d> " fmtStr, __FILENAME__, __LINE__, __VA_ARGS__)
#define EZ_DEBUGC(fmtStr)                                                    \
    do {                                                                     \
        printf(EZ_COLOR_BLUE "%s:%d> " fmtStr, __FILENAME__, __LINE__); \
        printf(EZ_COLOR_RESET);                                                \
    } while (0)
#define EZ_DEBUGCF(fmtStr, ...)                                                           \
    do {                                                                                  \
        printf(EZ_COLOR_BLUE "%s:%d> " fmtStr, __FILENAME__, __LINE__, __VA_ARGS__); \
        printf(EZ_COLOR_RESET);                                                             \
    } while (0)
#define EZ_DEBUG_RAW(fmtStr)       printf("%s", fmtStr)
#define EZ_DEBUGF_RAW(fmtStr, ...) printf("" fmtStr, __VA_ARGS__)
#define EZ_DEBUGC_RAW(fmtStr) \
    do {                      \
        printf("" fmtStr);    \
        printf(EZ_COLOR_RESET); \
    } while (0)
#define EZ_DEBUGCF_RAW(fmtStr, ...)     \
    do {                                \
        printf("" fmtStr, __VA_ARGS__); \
        printf(EZ_COLOR_RESET);           \
    } while (0)
#define EZ_ERRORF_RAW(fmtStr, ...)                             \
    do {                                                       \
        EZ_DEBUGCF_RAW(EZ_COLOR_BOLD_RED fmtStr, __VA_ARGS__); \
    } while (0)

#define EZ_ERROR_RAW(fmtStr)                     \
    do {                                         \
        EZ_DEBUGC_RAW(EZ_COLOR_BOLD_RED fmtStr); \
    } while (0)


#else
#define EZ_DEBUGF(fmtStr, ...)
#define EZ_DEBUG(fmtStr)
#define EZ_DEBUGC(color, fmtStr)
#define EZ_DEBUGCF(color, fmtStr, ...)
#define EZ_DEBUG_RAW(fmtStr)
#define EZ_DEBUGC_RAW(fmtStr)
#define EZ_DEBUGC(fmtstr)
#define EZ_DEBUGF_RAW(fmtStr, ...)
#define EZ_DEBUGCF_RAW(fmtStr, ...)
#define EZ_ERRORF_RAW(fmtStr, ...)
#define EZ_ERROR_RAW(fmtStr)
#endif

#endif//EASY2D_LOG_H
