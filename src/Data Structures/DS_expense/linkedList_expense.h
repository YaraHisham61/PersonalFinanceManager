//
// Created by Yara on 8/6/2023.
//

#ifndef INC_1_LINKEDLIST_EXPENSE_H
#define INC_1_LINKEDLIST_EXPENSE_H
#include "../../Expense/expense.h"
#include <stdio.h>

extern struct  e_node * expenses_ll;
extern int e_count;

struct e_node {
    struct expense data;
    struct e_node *next;
};
void e_initialize(FILE* filePtr);
void e_printList();
void e_printCat(struct e_node * head,double * total);
bool e_printFile();
void e_insert(struct expense * data);
void e_insertToCat(struct e_node **head , struct expense * data );
void e_catogrize(struct e_node **fptr,struct e_node **tptr,struct e_node **uptr,struct e_node **eptr,struct e_node **optr);
bool e_deleteNode(int key);
struct e_node * e_searchList(int key);
void e_deleteList();

#endif //INC_1_LINKEDLIST_EXPENSE_H
