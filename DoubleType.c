#include "DoubleType.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct double_type {
    double value;
} DOUBLE;

int compareDoubles(const void *arg1, const void *arg2) {
    const DOUBLE *a1 = (const DOUBLE*) arg1;
    const DOUBLE *a2 = (const DOUBLE*) arg2;
    if (a1->value > a2->value)
        return 1;
    if (a1->value < a2->value)
        return -1;
    return 0;
}

void printDouble(const void *elem) {
    const DOUBLE *a = (const DOUBLE*) elem;
    printf("%.2lf ", a->value);
}

int setDoubleValue(void *elem) {
    DOUBLE *a = (DOUBLE*) elem;
    return scanf("%lf", &a->value);
}

TYPE_INFO *doubleType = NULL;
const TYPE_INFO *getDoubleType(void) {
    if (!doubleType) {
        doubleType = malloc(sizeof(TYPE_INFO));
        doubleType->compare = compareDoubles;
        doubleType->elementSize = sizeof(DOUBLE);
        doubleType->print = printDouble;
        doubleType->set_value = setDoubleValue;
    }
    return doubleType;
}