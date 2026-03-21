#ifndef LAB1_DOUBLETYPE_H
#define LAB1_DOUBLETYPE_H


#include "TypesInfo.h"

const Type_info *getDoubleType(void);
int compareDoubles(const void *arg1, const void *arg2);
void printDouble(const void *elem);
int setDoubleValue(void *elem);

#endif //LAB1_DOUBLETYPE_H
