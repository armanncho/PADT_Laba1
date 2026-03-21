#ifndef LAB1_ARRAYALGORITHMS_H
#define LAB1_ARRAYALGORITHMS_H


#include "DynamicArray.h"

// Перечисление для статуса сортировки
typedef enum {
    SORT_ERROR = -1,
    SORT_ALREADY_WAS = 0,
    SORT_COMPLETE = 1
} SORT_SIGNAL;

// Прототипы функций (сортировка, map, where, конкатенация для 8 варианта)
void concat(Dynamic_array *result, const Dynamic_array *arr1, const Dynamic_array *arr2);
SORT_SIGNAL bubbleSort(Dynamic_array* dynamic_array);
void map(Dynamic_array *result_array, const Dynamic_array *dynamic_array, FuncForMap function);
void where(Dynamic_array *result, const Dynamic_array *dynamic_array, Predicate p);

#endif //LAB1_ARRAYALGORITHMS_H
