#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "operations.h"
#include "DoubleType.h"
#include "ComplexType.h"

// Структура для удобной работы с комплексными числами внутри main
typedef struct {
    double real;
    double imag;
} COMPLEX_STRUCT;

// ================= ФУНКЦИИ ДЛЯ MAP =================

void doubleMultiplyBy3(const void *src, void *dst) {
    *(double*)dst = (*(double*)src) * 3.0;
}

void complexMultiplyBy3(const void *src, void *dst) {
    const COMPLEX_STRUCT *s = (const COMPLEX_STRUCT*)src;
    COMPLEX_STRUCT *d = (COMPLEX_STRUCT*)dst;
    d->real = s->real * 3.0;
    d->imag = s->imag * 3.0;
}

void doubleSquare(const void *src, void *dst) {
    double x = *(double*)src;
    *(double*)dst = x * x;
}

void complexSquare(const void *src, void *dst) {
    const COMPLEX_STRUCT *s = (const COMPLEX_STRUCT*)src;
    COMPLEX_STRUCT *d = (COMPLEX_STRUCT*)dst;
    // Формула квадрата: (a + bi)^2 = (a^2 - b^2) + 2abi
    d->real = (s->real * s->real) - (s->imag * s->imag);
    d->imag = 2.0 * s->real * s->imag;
}

// ================= ФУНКЦИИ ДЛЯ WHERE =================

int positiveDouble(const void *e) {
    return *(double*)e > 0.0;
}

int positiveComplex(const void *e) {
    // Считаем комплексное число "положительным", если его действительная часть > 0
    return ((const COMPLEX_STRUCT*)e)->real > 0.0;
}

// ================= ОСНОВНАЯ ПРОГРАММА =================

int main() {

    int typeChoice;

    printf("Выберите тип массива:\n");
    printf("1 - вещественный (double)\n");
    printf("2 - комплексный (complex)\n");

    if (scanf("%d", &typeChoice) != 1 || (typeChoice != 1 && typeChoice != 2)){
        printf("Неверный тип\n");
        return 1;
    }

    const TYPE_INFO *type =
            (typeChoice == 1) ? getDoubleType() : getComplexType();

    DYNAMIC_ARRAY array;

    if (!initDynamicArray(&array, type, 2)){
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    int running = 1;

    while (running){

        printf("\n========== МЕНЮ ==========\n");
        printf("1. Добавить элемент в конец (pushBack)\n");
        printf("2. Удалить элемент с конца (popBack)\n");
        printf("3. Получить элемент по индексу\n");
        printf("4. Отсортировать\n");
        printf("5. Показать размер (size)\n");
        printf("6. Показать вместимость (capacity)\n");
        printf("7. Map: умножить на 3\n");
        printf("8. Map: возвести в квадрат\n");
        printf("9. Where: оставить положительные (real > 0)\n");
        printf("10. Конкатенация (объединение с новым массивом)\n");
        printf("0. Выход\n");
        printf("==========================\n");
        printf("Выбор: ");

        int choice;

        if (scanf("%d", &choice) != 1){
            while (getchar() != '\n');
            continue;
        }

        switch (choice){
            case 1:
            {
                char buffer[type->elementSize]; // временное место в памяти для записи значения

                if (typeChoice == 1)
                    printf("Введите значение: ");
                else
                    printf("Введите действительную и мнимую части (через пробел): ");

                // Проверяем > 0, так как double считывает 1 число, а complex - 2 числа
                if (type->set_value(buffer) > 0)
                    pushBack(&array, buffer);
                break;
            }

            case 2:
            {
                char buffer[type->elementSize];

                if (popBack(&array, buffer)){
                    printf("Удалено: ");
                    type->print(buffer);
                    printf("\n");
                }
                else
                    printf("Массив пуст\n");
                break;
            }

            case 3:
            {
                size_t index;
                printf("Индекс: ");

                if (scanf("%zu", &index) != 1)
                    break;

                void *elem = getElement(&array, index);

                if (!elem)
                    printf("Неверный индекс\n");
                else{
                    type->print(elem);
                    printf("\n");
                }
                break;
            }

            case 4:
            {
                SORT_SIGNAL r = bubbleSort(&array);

                if (r == SORT_ERROR)
                    printf("Ошибка сортировки\n");
                else if (r == SORT_ALREADY_WAS)
                    printf("Уже отсортировано\n");
                else
                    printf("Отсортировано успешно\n");
                break;
            }

            case 5:
                printf("Размер = %zu\n", array.size);
                break;

            case 6:
                printf("Вместимость = %zu\n", array.capacity);
                break;

            case 7:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1)
                    map(&result, &array, doubleMultiplyBy3);
                else
                    map(&result, &array, complexMultiplyBy3);

                printf("Результат Map:\n");
                printArray(&result);
                freeDynamicArray(&result);
                break;
            }

            case 8:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1)
                    map(&result, &array, doubleSquare);
                else
                    map(&result, &array, complexSquare);

                printf("Результат Map:\n");
                printArray(&result);
                freeDynamicArray(&result);
                break;
            }

            case 9:
            {
                DYNAMIC_ARRAY result;

                if (typeChoice == 1)
                    where(&result, &array, positiveDouble);
                else
                    where(&result, &array, positiveComplex);

                printf("Результат Where:\n");
                printArray(&result);
                freeDynamicArray(&result);
                break;
            }

            case 10:
            {
                DYNAMIC_ARRAY second;

                if (!initDynamicArray(&second, type, 2)){
                    printf("Ошибка выделения памяти\n");
                    break;
                }

                int count;

                printf("Сколько элементов добавить во второй массив? ");

                if (scanf("%d", &count) != 1){
                    freeDynamicArray(&second);
                    break;
                }

                for (int i = 0; i < count; i++){
                    char buffer[type->elementSize];

                    if (typeChoice == 1)
                        printf("Введите значение: ");
                    else
                        printf("Введите действительную и мнимую части (через пробел): ");

                    if (type->set_value(buffer) > 0)
                        pushBack(&second, buffer);
                }

                DYNAMIC_ARRAY result;
                concat(&result, &array, &second);

                printf("Результат конкатенации:\n");
                printArray(&result);

                freeDynamicArray(&result);
                freeDynamicArray(&second);
                break;
            }

            case 0:
                running = 0;
                break;

            default:
                printf("Неверный выбор\n");
        } // switch

        printf("\nТекущий массив:\n");
        printArray(&array);
    } // while

    freeDynamicArray(&array);
    return 0;
}