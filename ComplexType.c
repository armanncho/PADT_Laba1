#include "ComplexType.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct complex_type {
    double real;
    double imag;
} COMPLEX;

int compareComplex(const void *arg1, const void *arg2) {
    const COMPLEX *c1 = (const COMPLEX*) arg1;
    const COMPLEX *c2 = (const COMPLEX*) arg2;

    // Сравнение по модулю (a^2 + b^2)
    double mod1 = c1->real * c1->real + c1->imag * c1->imag;
    double mod2 = c2->real * c2->real + c2->imag * c2->imag;

    if (mod1 > mod2)
        return 1;
    if (mod1 < mod2)
        return -1;
    return 0;
}

void printComplex(const void *elem) {
    const COMPLEX *c = (const COMPLEX*) elem;
    if (c->imag >= 0)
        printf("%.2lf+%.2lfi ", c->real, c->imag);
    else
        printf("%.2lf%.2lfi ", c->real, c->imag);
}

int setComplexValue(void *elem) {
    COMPLEX *c = (COMPLEX*) elem;
    return scanf("%lf %lf", &c->real, &c->imag);
}

TYPE_INFO *complexType = NULL;
const TYPE_INFO *getComplexType(void) {
    if (!complexType) {
        complexType = malloc(sizeof(TYPE_INFO));
        complexType->compare = compareComplex;
        complexType->elementSize = sizeof(COMPLEX);
        complexType->print = printComplex;
        complexType->set_value = setComplexValue;
    }
    return complexType;
}