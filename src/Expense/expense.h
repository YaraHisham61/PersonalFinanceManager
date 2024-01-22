//
// Created by Yara on 8/4/2023.
//

#ifndef INC_1_EXPENSE_H
#define INC_1_EXPENSE_H

#include "../Utilities/utilities.h"
#include <stdio.h>

typedef enum{
    food,
    transportation,
    utilities,
    entertainment,
    others
} category;

struct expense {
    int index; // To Edit & delete ?
    char des [100];
    double value;
    char date [11];
    category c;
};
const char * getCategory(category c);
int setCategory(const char * str);
bool addExpense ();
bool editExpense();
bool deleteExpense();
void printExpense();
void readExpenses(FILE *filePtr);
bool e_exit();
#endif //INC_1_EXPENSE_H
