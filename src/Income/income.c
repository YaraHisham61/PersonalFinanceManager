//
// Created by Yara on 8/4/2023.
//

#include "income.h"
#include "../Data Structures/DS_income/linkedList_income.h"
#include <strings.h>
#include <time.h>



const char * getSource(source s){
    switch (s) {
        case salary: return "salary";
        case partTimeJob: return "partTimeJob";
        case freelancing: return "freelancing";
        case overtime: return "overtime";
        case investment: return "investment";
    }
}
int setSource(const char * str){
    if(strcasecmp(str,"salary\n") == 0)
        return 0;
    if(strcasecmp(str,"partTimeJob\n") == 0)
        return 1;
    if(strcasecmp(str,"freelancing\n")==0)
        return 2;
    if(strcasecmp(str,"overtime\n")==0)
        return 3;
    if(strcasecmp(str,"investment\n")==0)
        return 4;
    return -1;
}

bool addIncome(){
    //todo return false?
    char str[50];
    struct income i;
    printf("Enter your new income description(100 characters max): \n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(i.des,100,stdin);
    strtok(i.des,"\n");
    printf("Enter your new income value: \n");
    char * ptr;
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    i.value =strtod(str, &ptr);
    if(i.value == 0){
        printf("The input isn't a double value");
        return false;
    }
    printf("Do you want to enter the date manually? (y/n)\n");
    char c= getchar();
    char date[11];
    if(c == 'y'){
        printf("Enter your new income date in the format dd/mm/yyyy: \n");
        fseek(stdin, 0, SEEK_END); //Ignoring any past input
        fgets(date, 11, stdin);
        if(!checkDateFormat(date)){
            printf("Wrong date format\n");
            return false;
            }
        strcpy_s(i.date,11,date);
    }

    else {
        time_t t = time(NULL);
        struct tm autoTime = *localtime(&t);
        strftime(i.date, sizeof(i.date), "%m/%d/%Y", &autoTime);
    }

    printf("Enter the new income source from the following:\n");
    printf("salary partTimeJob freelancing overtime investment\n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    int x = setSource(str);
    if( x == -1 ) {
        printf("This source doesn't exists in the system");
        return false;
    }
    i.s= x;
    i_insert(&i);
    return true;
}

bool editIncome(int id) {
    struct i_node * temp = i_searchList( id);
    char str[50];
    char *ptr;
    if(temp == NULL){
        printf("Income not found (wrong id)");
        return false;
    }
    printf("What do you want to edit?\n"
           "1: Value\n"
           "2: Date\n"
           "3: Description\n"
           "4: Source\n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    char c = getchar();
    switch(c){
        case '1':
            printf("Enter the new value: \n");
            fseek(stdin, 0, SEEK_END); //Ignoring any past input
            fgets(str, 50, stdin);
            temp->data.value = strtod(str, &ptr);
            break;
        case'2':
            printf("Do you want to enter the date manually? (y/n)\n");
            fseek(stdin, 0, SEEK_END); //Ignoring any past input
            c= getchar();
            char date[11];
            if(c == 'y'){
                printf("Enter your new income date in the format dd/mm/yyyy: \n");
                fseek(stdin, 0, SEEK_END); //Ignoring any past input
                fgets(date, 11, stdin);
                if(checkDateFormat(date))
                    strcpy_s(temp->data.date,11,date);
                else printf("Wrong date format\n");
            }
            else{

                time_t t = time(NULL);
                struct tm autoTime = *localtime(&t);
                strftime(temp->data.date, sizeof(temp->data.date), "%m/%d/%Y", &autoTime);
            }
            break;
        case '3' :
            printf("Enter the new description(100 characters max): \n");
            fgets(temp->data.des,100,stdin);
            strtok(temp->data.des,"\n");
            break;
        case'4':
            printf("Enter the new income source:\n");
            fseek(stdin, 0, SEEK_END); //Ignoring any past input
            fgets(str, 50, stdin);
            int x = setSource(str);
            if(x == -1)
            {
                printf("This source doesn't exists in the system\n");
                return false;
            }
            temp->data.s= x;
            break;
        default:
            printf("Invalid input\n");
            break;
    }
    return 1;
}
bool deleteIncome(){
    char str[50];
    printf("Enter the id of the income you want to delete: ");
    char * ptr;
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    fgets(str, 50, stdin);
    int id = strtol(str, &ptr, 10);
    return i_deleteNode(id);
}

void printIncome(){
    printf("\n          Incomes:\n");
    printf("--------------------------------\n");
    i_printList();
}
void readIncomes(FILE *filePtr) {
    i_initialize(filePtr);
}
bool i_exit(){
    if(i_printFile()){
        printf("Data saved Successfully\n");
        i_deleteList();
        return true;
    }
    else {
        printf("Can't save data\n");
        return false;
    }
}
