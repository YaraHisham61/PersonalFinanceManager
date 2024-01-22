//
// Created by Yara on 8/4/2023.
//
#include <stdio.h>
#include "expense.h"
#include "../Data Structures/DS_expense/linkedList_expense.h"
#include <time.h>

const char * getCategory(category c){
    switch (c) {
        case food: return "food";
        case transportation: return "transportation";
        case utilities: return "utilities";
        case entertainment: return "entertainment";
        case others: return "others";
    }
}
int setCategory(const char * str){
    if(strcasecmp(str,"food\n") ==0) return 0;
    if(strcasecmp(str,"transportation\n") == 0) return 1;
    if(strcasecmp(str,"utilities\n")==0) return 2;
    if(strcasecmp(str,"entertainment\n")==0) return 3;
    if(strcasecmp(str,"others\n")==0) return 4;
    return -1;
}
bool addExpense(){
    char str [50];
    struct expense e;
    printf("Enter your new expense description (100 characters max): \n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(e.des,100,stdin); //So we don't ignore spaces
    strtok(e.des,"\n");

    printf("Enter your new expense value: \n");
    char * ptr;
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    e.value = strtod(str, &ptr);
    printf("Do you want to enter the date manually? (y/n)");
    char c = getchar();
    if(c == 'y'){
    printf("Enter your new expense date in the format dd/mm/yyyy: \n");
    char date[11];
    scanf("%s",date);
        if(!checkDateFormat(date)){
            printf("Wrong date format\n");
            return false;
        }
    strcpy_s(e.date,11,date);
    }

    else {
        time_t t = time(NULL);
        struct tm autoTime = *localtime(&t);
        strftime(e.date, sizeof(e.date), "%m/%d/%Y", &autoTime);
    }
    printf("Enter your new expense category: \n");
    printf("1: food,\n"
           "2: transportation,\n"
           "3: utilities,\n"
           "4: Entertainment,\n"
           "5: others \n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 2, stdin);
    int cat = strtol(str, &ptr, 10);
    while(cat>5){
        printf("Wrong value!");
        printf("Enter your new expense category: \n");
        printf("1: food,\n"
               "2: transportation,\n"
               "3: utilities,\n"
               "4: Entertainment,\n"
               "5: others \n");
        fseek(stdin, 0, SEEK_END); //Ignoring any past input
        fgets(str, 2, stdin);
        cat = strtol(str, &ptr, 10);
    }
    e.c=cat-1;
    e_insert(&e);
    return 1;
}
bool editExpense() {
    char str[50];
    printf("Enter the id of the expense you want to edit");
    char * ptr;
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    int id = strtol(str, &ptr, 10);
    struct e_node * temp = e_searchList(id);
    if(temp == NULL){
        printf("Expense not found");
        return 0;
    }
    //TODO edit
return 1;
}
bool deleteExpense() {
    char str[50];
    printf("Enter the id of the expense you want to delete");
    char * ptr;
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    int id = strtol(str, &ptr, 10);
   return e_deleteNode(id);
}
void printExpense(){
    printf("\n          Expenses:\n");
    printf("-------------------------------\n");
    e_printList();
}
void readExpenses(FILE *filePtr){
    e_initialize(filePtr);
}

bool e_exit() {
    if (e_printFile()) {
        printf("Data saved Successfully\n");
        e_deleteList();
        return true;
    }
    else {
        printf("Can't save data\n");
        return false;
    }
}