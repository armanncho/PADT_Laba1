#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "dynamicArray.h"
#include "ArrayAlgorithms.h"
#include "doubleType.h"
#include "complexType.h"

// Структура для удобного тестирования комплексных чисел
typedef struct {
    double real;
    double imag;
} COMPLEX_TEST;

/* ====== Вспомогательные функции ====== */

void multiplyDoubleBy2(const void *src, void *dst)
{
    *(double*)dst = (*(double*)src) * 2.0;
}

int isPositiveDouble(const void *elem)
{
    return *(double*)elem > 0.0;
}

void multiplyComplexBy2(const void *src, void *dst)
{
    const COMPLEX_TEST *s = (const COMPLEX_TEST*)src;
    COMPLEX_TEST *d = (COMPLEX_TEST*)dst;
    d->real = s->real * 2.0;
    d->imag = s->imag * 2.0;
}

int isRealPartPositive(const void *elem)
{
    return ((const COMPLEX_TEST*)elem)->real > 0.0;
}

/* ================= DOUBLE TESTS ================= */

void testInitAndPushDouble()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    assert(arr.size == 3);
    assert(*(double*)getElement(&arr, 0) == 5.5);
    assert(*(double*)getElement(&arr, 1) == 1.1);
    assert(*(double*)getElement(&arr, 2) == 3.3);

    freeDynamicArray(&arr);
}

void testPopDouble()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 1.5, b = 2.5;

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    double removed;

    assert(popBack(&arr, &removed));
    assert(removed == 2.5);

    assert(popBack(&arr, &removed));
    assert(removed == 1.5);

    assert(popBack(&arr, &removed) == 0);

    freeDynamicArray(&arr);
}

void testSortDouble()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 5.5, b = 1.1, c = 3.3;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    bubbleSort(&arr);

    assert(*(double*)getElement(&arr, 0) == 1.1);
    assert(*(double*)getElement(&arr, 1) == 3.3);
    assert(*(double*)getElement(&arr, 2) == 5.5);

    freeDynamicArray(&arr);
}

void testMapDouble()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = 1.5, b = 3.5;

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    Dynamic_array mapped;
    map(&mapped, &arr, multiplyDoubleBy2);

    assert(mapped.size == 2);
    assert(*(double*)getElement(&mapped, 0) == 3.0);
    assert(*(double*)getElement(&mapped, 1) == 7.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&mapped);
}

void testWhereDouble()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getDoubleType(), 2));

    double a = -1.0, b = 2.0, c = -3.0, d = 4.0;

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);
    pushBack(&arr, &d);

    Dynamic_array filtered;
    where(&filtered, &arr, isPositiveDouble);

    assert(filtered.size == 2);
    assert(*(double*)getElement(&filtered, 0) == 2.0);
    assert(*(double*)getElement(&filtered, 1) == 4.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&filtered);
}

void testConcatDouble()
{
    Dynamic_array a, b, result;

    assert(initDynamicArray(&a, getDoubleType(), 2));
    assert(initDynamicArray(&b, getDoubleType(), 2));

    double x = 1.1, y = 2.2, z = 3.3;

    pushBack(&a, &x);
    pushBack(&b, &y);
    pushBack(&b, &z);

    concat(&result, &a, &b);

    assert(result.size == a.size + b.size);
    assert(*(double*)getElement(&result, 0) == 1.1);
    assert(*(double*)getElement(&result, 1) == 2.2);
    assert(*(double*)getElement(&result, 2) == 3.3);

    freeDynamicArray(&a);
    freeDynamicArray(&b);
    freeDynamicArray(&result);
}

/* ================= COMPLEX TESTS ================= */

void testInitAndPushComplex()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getComplexType(), 2));

    COMPLEX_TEST a = {1.0, 2.0}, b = {3.0, 4.0}, c = {5.0, 6.0};

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    assert(arr.size == 3);
    assert(((COMPLEX_TEST*)getElement(&arr, 0))->real == 1.0);
    assert(((COMPLEX_TEST*)getElement(&arr, 0))->imag == 2.0);
    assert(((COMPLEX_TEST*)getElement(&arr, 1))->real == 3.0);
    assert(((COMPLEX_TEST*)getElement(&arr, 2))->imag == 6.0);

    freeDynamicArray(&arr);
}

void testPopComplex()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getComplexType(), 2));

    COMPLEX_TEST a = {1.0, 1.0}, b = {2.0, 2.0};

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    COMPLEX_TEST removed;

    assert(popBack(&arr, &removed));
    assert(removed.real == 2.0 && removed.imag == 2.0);

    assert(popBack(&arr, &removed));
    assert(removed.real == 1.0 && removed.imag == 1.0);

    assert(popBack(&arr, &removed) == 0);

    freeDynamicArray(&arr);
}

void testSortComplex()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getComplexType(), 2));

    // Сортировка по модулю: c(25) < a(26) < b(50)
    COMPLEX_TEST a = {1.0, 5.0}; // mod = 26
    COMPLEX_TEST b = {5.0, 5.0}; // mod = 50
    COMPLEX_TEST c = {3.0, 4.0}; // mod = 25

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);

    bubbleSort(&arr);

    assert(((COMPLEX_TEST*)getElement(&arr, 0))->real == 3.0); // c
    assert(((COMPLEX_TEST*)getElement(&arr, 1))->real == 1.0); // a
    assert(((COMPLEX_TEST*)getElement(&arr, 2))->real == 5.0); // b

    freeDynamicArray(&arr);
}

void testMapComplex()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getComplexType(), 2));

    COMPLEX_TEST a = {1.0, 2.0}, b = {-3.0, 4.0};

    pushBack(&arr, &a);
    pushBack(&arr, &b);

    Dynamic_array mapped;
    map(&mapped, &arr, multiplyComplexBy2);

    assert(mapped.size == 2);
    assert(((COMPLEX_TEST*)getElement(&mapped, 0))->real == 2.0);
    assert(((COMPLEX_TEST*)getElement(&mapped, 0))->imag == 4.0);
    assert(((COMPLEX_TEST*)getElement(&mapped, 1))->real == -6.0);
    assert(((COMPLEX_TEST*)getElement(&mapped, 1))->imag == 8.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&mapped);
}

void testWhereComplex()
{
    Dynamic_array arr;
    assert(initDynamicArray(&arr, getComplexType(), 2));

    COMPLEX_TEST a = {-1.0, 2.0}, b = {2.0, 3.0}, c = {-3.0, -1.0}, d = {4.0, 0.0};

    pushBack(&arr, &a);
    pushBack(&arr, &b);
    pushBack(&arr, &c);
    pushBack(&arr, &d);

    Dynamic_array filtered;
    where(&filtered, &arr, isRealPartPositive);

    assert(filtered.size == 2);
    assert(((COMPLEX_TEST*)getElement(&filtered, 0))->real == 2.0);
    assert(((COMPLEX_TEST*)getElement(&filtered, 1))->real == 4.0);

    freeDynamicArray(&arr);
    freeDynamicArray(&filtered);
}

void testConcatComplex()
{
    Dynamic_array a, b, result;

    assert(initDynamicArray(&a, getComplexType(), 2));
    assert(initDynamicArray(&b, getComplexType(), 2));

    COMPLEX_TEST x = {1.0, 1.0}, y = {2.0, 2.0}, z = {3.0, 3.0};

    pushBack(&a, &x);
    pushBack(&b, &y);
    pushBack(&b, &z);

    concat(&result, &a, &b);

    assert(result.size == a.size + b.size);
    assert(((COMPLEX_TEST*)getElement(&result, 0))->real == 1.0);
    assert(((COMPLEX_TEST*)getElement(&result, 1))->real == 2.0);
    assert(((COMPLEX_TEST*)getElement(&result, 2))->real == 3.0);

    freeDynamicArray(&a);
    freeDynamicArray(&b);
    freeDynamicArray(&result);
}

void testConcatDifferentTypes()
{
    Dynamic_array arrDouble, arrComplex, result;

    assert(initDynamicArray(&arrDouble, getDoubleType(), 2));
    assert(initDynamicArray(&arrComplex, getComplexType(), 2));

    // Пытаемся склеить массивы разных типов.
    // Предполагается, что твоя функция concat оставляет result неинициализированным или size = 0.
    result.size = 0;
    concat(&result, &arrDouble, &arrComplex);

    // Размер должен остаться 0, так как типы не совпадают
    assert(result.size == 0);

    freeDynamicArray(&arrDouble);
    freeDynamicArray(&arrComplex);
}

int main()
{
    testInitAndPushDouble();
    testPopDouble();
    testSortDouble();
    testMapDouble();
    testWhereDouble();
    testConcatDouble();

    testInitAndPushComplex();
    testPopComplex();
    testSortComplex();
    testMapComplex();
    testWhereComplex();
    testConcatComplex();

    testConcatDifferentTypes(); // Проверка на защиту от смешивания типов

    printf("All tests passed successfully!\n");
    return 0;
}