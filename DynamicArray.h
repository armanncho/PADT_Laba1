#ifndef LABA1_DYNAMICARRAY_H
#define LABA1_DYNAMICARRAY_H

#include <stddef.h>
#include "TypesInfo.h"

typedef struct {
    void *data;
    size_t size;
    size_t capacity; // вместимость
    const Type_info *type;
} Dynamic_array;

int initDynamicArray(Dynamic_array *dynamic_array, const Type_info *type, size_t initialCapacity);
void freeDynamicArray(Dynamic_array *dynamic_array);
int pushBack(Dynamic_array *dynamic_array, const void *element);
int popBack(Dynamic_array *dynamic_array, void *save_data);
void* getElement(const Dynamic_array *dynamic_array, size_t index); // Добавлен const для безопасности
void printArray(const Dynamic_array *dynamic_array);

typedef void(*FuncForMap)(const void*, void*);
typedef int (*Predicate)(const void*);

#endif //LABA1_DYNAMICARRAY_H
