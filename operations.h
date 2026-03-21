#ifndef LAB1_OPERATIONS_H
#define LAB1_OPERATIONS_H


#include "DynamicArray.h"

// Перечисление для статуса сортировки
typedef enum {
    SORT_ERROR = -1,
    SORT_ALREADY_WAS = 0,
    SORT_COMPLETE = 1
} SORT_SIGNAL;

// Прототипы функций (сортировка, map, where, конкатенация для 8 варианта)
void concat(DYNAMIC_ARRAY *result, const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2);
SORT_SIGNAL bubbleSort(DYNAMIC_ARRAY* dynamic_array);
void map(DYNAMIC_ARRAY *result_array, const DYNAMIC_ARRAY *dynamic_array, FuncForMap function);
void where(DYNAMIC_ARRAY *result, const DYNAMIC_ARRAY *dynamic_array, Predicate p);

#endif //LAB1_OPERATIONS_H
