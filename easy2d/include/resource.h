//
// Created by Emir Hürtürk on 11.07.2021.
//

#ifndef EASY2D_RESOURCE_H
#define EASY2D_RESOURCE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#define EZ_FILE_OK 0
#define EZ_FILE_DOES_NOT_EXIST 1
#define EZ_FILE_TOO_LARGE 2

typedef struct EZResource EZResource;

struct EZResource *ezLoadFile(const char *file, int *err);
struct EZResource *ezLoadImage(const char *file, int *error);

const char *ezGetResourceContent(struct EZResource *res);
size_t ezGetResourceSize(struct EZResource *res);
int ezGetResourceLength(struct EZResource *res);

void ezReleaseResource(struct EZResource *res);


#ifdef __cplusplus
}
#endif//__cplusplus
#endif//EASY2D_RESOURCE_H
