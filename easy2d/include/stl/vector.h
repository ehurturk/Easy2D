/*
 * VECTOR IMPLEMENTATION TAKEN FROM https://aticleworld.com/implement-vector-in-c/
 * MAINLY BECAUSE I WANTED TO FOCUS ON CREATING GAMEDEV RELATED CONTENT, NOT WORK WITH STL STUFF
 *
*/

#ifndef EASY2D_VECTOR_H
#define EASY2D_VECTOR_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define V_VECTOR_INIT_CAPACITY 6
#define V_UNDEFINED  -1
#define V_SUCCESS 0

#define EZ_VECTOR_INIT(vec) EZVector vec;\
 ez_vector_init(&vec)

//Store and track the stored data
typedef struct
{
    void **items;
    int capacity;
    int total;
} EZVector;

//structure contain the function pointer

int ezVectorTotal(EZVector *v);
int ezVectorResize(EZVector *v, int capacity);
int ezVectorPushBack(EZVector *v, void *item);
int ezVectorSet(EZVector *v, int index, void *item);
void *ezVectorGet(EZVector *v, int index);
int ezVectorIndexOf(EZVector *v, void *item);
int ezVectorDelete(EZVector *v, int index);
int ezVectorFree(EZVector *v);
void ez_vector_init(EZVector *v);

#ifdef __cplusplus
};
#endif

#endif//EASY2D_VECTOR_H
