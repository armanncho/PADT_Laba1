#ifndef LAB1_TYPESINFO_H
#define LAB1_TYPESINFO_H

#include <stddef.h>

// Структура для комплексных чисел (требование 8 варианта)
typedef struct {
    double real;
    double imag;
} Complex;

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
} TYPE_INFO;

// Функции для получения статических экземпляров TYPE_INFO
TYPE_INFO* get_double_type_info(void);
TYPE_INFO* get_complex_type_info(void);

#endif //LAB1_TYPESINFO_H
