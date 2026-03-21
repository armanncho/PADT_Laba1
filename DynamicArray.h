#ifndef LABA1_DYNAMICARRAY_H
#define LABA1_DYNAMICARRAY_H

#include <stddef.h>
#include "TypesInfo.h"

typedef struct {
    void *data;
    size_t size;
    size_t capacity; // вместимость
    const TYPE_INFO *type;
} DYNAMIC_ARRAY;

int initDynamicArray(DYNAMIC_ARRAY *dynamic_array, const TYPE_INFO *type, size_t initialCapacity);
void freeDynamicArray(DYNAMIC_ARRAY *dynamic_array);
int pushBack(DYNAMIC_ARRAY *dynamic_array, const void *element);
int popBack(DYNAMIC_ARRAY *dynamic_array, void *save_data);
void* getElement(const DYNAMIC_ARRAY *dynamic_array, size_t index); // Добавлен const для безопасности
void printArray(const DYNAMIC_ARRAY *dynamic_array);

typedef void(*FuncForMap)(const void*, void*);
typedef int (*Predicate)(const void*);

#endif //LABA1_DYNAMICARRAY_H