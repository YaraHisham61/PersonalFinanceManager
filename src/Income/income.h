//
// Created by Yara on 8/4/2023.
//

#ifndef INC_1_INCOME_H
#define INC_1_INCOME_H

#include "../Utilities/utilities.h"
#include <stdio.h>

typedef enum{
    salary,
    partTimeJob,
    freelancing,
    overtime,
    investment
} source;
struct income{
    char des [100];
    char date[11];
    double value;
    int id;
    source s;
};
const char * getSource(source s);
int setSource(const char * str);
bool addIncome();
bool editIncome(int id);
bool deleteIncome();
void printIncome();
void readIncomes(FILE *filePtr);
bool i_exit();
#endif //INC_1_INCOME_H
