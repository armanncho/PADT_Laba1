#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int initDynamicArray(DYNAMIC_ARRAY *dynamic_array, const TYPE_INFO *type, size_t initialCapacity) {
    if (!dynamic_array || !type)
        return 0;

    dynamic_array->capacity = initialCapacity;
    dynamic_array->type = type;
    dynamic_array->size = 0;

    if (initialCapacity > 0) {
        dynamic_array->data = malloc(initialCapacity * type->elementSize);
        if (!dynamic_array->data) {
            dynamic_array->capacity = 0;
            return 0;
        }
    } else {
        dynamic_array->data = NULL;
    }

    return 1;
}

void freeDynamicArray(DYNAMIC_ARRAY *dynamic_array) {
    if (!dynamic_array)
        return;
    free(dynamic_array->data);
    dynamic_array->data = NULL;
    dynamic_array->capacity = 0;
    dynamic_array->size = 0;
}

int pushBack(DYNAMIC_ARRAY *dynamic_array, const void *element) {
    if (!dynamic_array || !element)
        return 0;

    if (dynamic_array->size == dynamic_array->capacity) {
        size_t newCapacity = (dynamic_array->capacity == 0) ? 1 : dynamic_array->capacity * 2;
        void *newData = malloc(newCapacity * dynamic_array->type->elementSize);

        if (!newData)
            return 0;

        if (dynamic_array->data) { // если старые данные есть, то копируем их
            memcpy(newData, dynamic_array->data, dynamic_array->size * dynamic_array->type->elementSize);
        }

        free(dynamic_array->data);
        dynamic_array->data = newData;
        dynamic_array->capacity = newCapacity;
    }

    void *dest = (char *)dynamic_array->data + dynamic_array->size * dynamic_array->type->elementSize;
    memcpy(dest, element, dynamic_array->type->elementSize);
    dynamic_array->size++;
    return 1;
}

int popBack(DYNAMIC_ARRAY *dynamic_array, void *save_data) {
    if (!dynamic_array || !save_data || dynamic_array->size == 0)
        return 0;

    void *dest = (char*)dynamic_array->data + (dynamic_array->size - 1) * dynamic_array->type->elementSize;
    memcpy(save_data, dest, dynamic_array->type->elementSize);
    dynamic_array->size--;
    return 1;
}

void* getElement(const DYNAMIC_ARRAY *dynamic_array, size_t index) {
    if (index >= dynamic_array->size)
        return NULL;
    return (char*)dynamic_array->data + index * dynamic_array->type->elementSize;
}

void printArray(const DYNAMIC_ARRAY *dynamic_array) {
    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *elem = getElement(dynamic_array, i);
        dynamic_array->type->print(elem);
    }
    printf("\n");
}