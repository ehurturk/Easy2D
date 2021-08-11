//
// Created by Emir Hürtürk on 10.08.2021.
//

#include "stl/vector.h"

int ezVectorTotal(EZVector *v)
{
    int totalCount = V_UNDEFINED;
    if(v)
    {
        totalCount = v->total;
    }
    return totalCount;
}
int ezVectorResize(EZVector *v, int capacity)
{
    int  status = V_UNDEFINED;
    if(v)
    {
        void **items = realloc(v->items, sizeof(void *) * capacity);
        if (items)
        {
            v->items = items;
            v->capacity = capacity;
            status = V_SUCCESS;
        }
    }
    return status;
}
int ezVectorPushBack(EZVector *v, void *item)
{
    int  status = V_UNDEFINED;
    if(v)
    {
        if (v->capacity == v->total)
        {
            status = ezVectorResize(v, v->capacity * 2);
            if(status != V_UNDEFINED)
            {
                v->items[v->total++] = item;
            }
        }
        else
        {
            v->items[v->total++] = item;
            status = V_SUCCESS;
        }
    }
    return status;
}
int ezVectorSet(EZVector *v, int index, void *item)
{
    int  status = V_UNDEFINED;
    if(v)
    {
        if ((index >= 0) && (index < v->total))
        {
            v->items[index] = item;
            status = V_SUCCESS;
        }
    }
    return status;
}
void *ezVectorGet(EZVector *v, int index)
{
    void *readData = NULL;
    if(v)
    {
        if ((index >= 0) && (index < v->total))
        {
            readData = v->items[index];
        }
    }
    return readData;
}
int ezVectorDelete(EZVector *v, int index)
{
    int  status = V_UNDEFINED;
    int i = 0;
    if(v)
    {
        if ((index < 0) || (index >= v->total))
            return status;
        v->items[index] = NULL;
        for (i = index; (i < v->total - 1); ++i)
        {
            v->items[i] = v->items[i + 1];
            v->items[i + 1] = NULL;
        }
        v->total--;
        if ((v->total > 0) && ((v->total) == (v->capacity / 4)))
        {
            ezVectorResize(v, v->capacity / 2);
        }
        status = V_SUCCESS;
    }
    return status;
}
int ezVectorFree(EZVector *v)
{
    int  status = V_UNDEFINED;
    if(v)
    {
        free(v->items);
        v->items = NULL;
        status = V_SUCCESS;
    }
    return status;
}
void ez_vector_init(EZVector *v)
{
    //initialize the capacity and allocate the memory
    v->capacity = V_VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}