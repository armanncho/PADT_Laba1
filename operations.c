#include "operations.h"
#include <stdlib.h>
#include <string.h>

void concat(DYNAMIC_ARRAY *result, const DYNAMIC_ARRAY *arr1, const DYNAMIC_ARRAY *arr2) {
    if (!arr1 || !arr2 || !result)
        return;
    if (arr1->type != arr2->type)
        return; // Защита: нельзя склеивать double и complex

    // Инициализируем результирующий массив суммарной вместимостью
    if (!initDynamicArray(result, arr1->type, arr1->size + arr2->size))
        return;

    size_t element_size = arr1->type->elementSize;

    // Копируем данные первого массива
    memcpy(result->data, arr1->data, arr1->size * element_size);
    // Копируем данные второго массива сразу после первого
    memcpy((char*)result->data + arr1->size * element_size, arr2->data, arr2->size * element_size);

    result->size = arr1->size + arr2->size;
}

SORT_SIGNAL bubbleSort(DYNAMIC_ARRAY* dynamic_array) {
    if (!dynamic_array || dynamic_array->size < 2)
        return SORT_ERROR;

    size_t elementSize = dynamic_array->type->elementSize;

    // Выделяем память под временный элемент для обмена
    void *swap = malloc(elementSize);
    if (!swap)
        return SORT_ERROR;

    int was_swap = 0;
    for (size_t i = 0; i < dynamic_array->size - 1; i++) {
        int cycle_swap = 0;
        for (size_t j = 0; j < dynamic_array->size - i - 1; j++) {
            void *element1 = (char*)dynamic_array->data + j * elementSize;
            void *element2 = (char*)dynamic_array->data + (j + 1) * elementSize;

            // Полиморфный вызов функции сравнения (работает и для double, и для complex)
            if (dynamic_array->type->compare(element1, element2) > 0) {
                memcpy(swap, element1, elementSize);
                memcpy(element1, element2, elementSize);
                memcpy(element2, swap, elementSize);
                cycle_swap = 1;
                was_swap = 1;
            }
        }
        if (!cycle_swap)
            break; // Массив уже отсортирован, можно прервать цикл
    }

    free(swap); // Не забываем освободить память

    if (!was_swap)
        return SORT_ALREADY_WAS;

    return SORT_COMPLETE;
}

void map(DYNAMIC_ARRAY *result_array, const DYNAMIC_ARRAY *dynamic_array, FuncForMap function) {
    if (!dynamic_array || !function || !result_array)
        return;

    // Инициализируем массив той же вместимостью
    if (!initDynamicArray(result_array, dynamic_array->type, dynamic_array->capacity))
        return;

    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element_i = (char*)dynamic_array->data + i * dynamic_array->type->elementSize;
        void *dest = (char*)result_array->data + i * dynamic_array->type->elementSize;

        // Применяем переданную функцию к элементу
        function(element_i, dest);
    }
    // Устанавливаем правильный размер после обхода
    result_array->size = dynamic_array->size;
}

void where(DYNAMIC_ARRAY *result, const DYNAMIC_ARRAY *dynamic_array, Predicate p) {
    if (!dynamic_array || !p || !result)
        return;

    // Выделяем память с запасом (в худшем случае пройдут все элементы)
    // Функция initDynamicArray автоматически установит result->size = 0
    if (!initDynamicArray(result, dynamic_array->type, dynamic_array->size))
        return;

    for (size_t i = 0; i < dynamic_array->size; i++) {
        void *element = (char*)dynamic_array->data + i * dynamic_array->type->elementSize;

        // Если предикат вернул true, добавляем элемент в результат
        if (p(element)) {
            pushBack(result, element);
        }
    }
}