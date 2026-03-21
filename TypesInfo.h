#ifndef LAB1_TYPESINFO_H
#define LAB1_TYPESINFO_H

#include <stddef.h>

// Описания сигнатур функций
typedef int (*ComparePtr)(const void*, const void*);
typedef void (*PrintPtr)(const void*);
typedef int (*SetValuePtr)(void *);

// Структура информации о типе
typedef struct type_info {
    ComparePtr compare;
    size_t elementSize;
    PrintPtr print;
    SetValuePtr set_value;
} Type_info;

Type_info* getDoubleType(void);
Type_info* getComplexType(void);

#endif //LAB1_TYPESINFO_H
