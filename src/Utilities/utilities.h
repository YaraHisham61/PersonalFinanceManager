//
// Created by Yara on 8/4/2023.
//

#ifndef INC_1_UTILITIES_H
#define INC_1_UTILITIES_H
#include <string.h>
#include <stdlib.h>
typedef  enum {
    false,
    true
}bool;

bool checkDateFormat(char date[]);
bool cmpDate(const char *date1, const char *date2);
#endif //INC_1_UTILITIES_H