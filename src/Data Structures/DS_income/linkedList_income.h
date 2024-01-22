//
// Created by Yara on 8/6/2023.
//

#ifndef INC_1_LINKEDLIST_INCOME_H
#define INC_1_LINKEDLIST_INCOME_H

#include "../../Income/income.h"
#include "../../Utilities/utilities.h"
#include <stdio.h>


struct i_node {
    struct income data;
    struct i_node * next;
};

extern struct  i_node * incomes_ll;
extern int i_count;

bool cmpDate(const char *date1, const char *date2);
void i_initialize(FILE* filePtr);
void i_printList();
void i_printCat(struct i_node * head,double * total);
bool i_printFile();
void i_insert(struct income * data);
void i_insertToCat(struct i_node **head , struct income * data );
void i_catogrize(struct i_node **sptr, struct i_node **pptr, struct i_node **fptr, struct i_node **optr,
                 struct i_node **iptr);
bool i_deleteNode(int key);
struct i_node * i_searchList(int key);
void i_deleteList();


#endif //INC_1_LINKEDLIST_INCOME_H
