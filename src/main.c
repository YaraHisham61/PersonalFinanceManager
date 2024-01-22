#include <stdio.h>
#include <stdlib.h>
#include "Expense/expense.h"
#include "Income/income.h"
#include "Reports/reports.h"

void viewStartMsg(){
    printf("            Personal Finance Manager\n");
    printf("----------------------------------------------\n");
    printf("Starting the program .... \n\n");
}

void setup_e() {
    FILE *filePtr = fopen("../Data/expenses.txt", "r");
    if (filePtr == NULL) {
        printf("Error opening the expense file.\n");
        exit(1);
    }
    readExpenses(filePtr);
}

void setup_i(){
    FILE * filePtr=fopen("../Data/incomes.txt","r");
    if (filePtr == NULL) {
        printf("Error opening the incomes file.\n");
        exit(1);
    }
    readIncomes(filePtr);
}
void viewTransactions(){
    printIncome();
    printExpense();
}
void viewReports(){
    printf("Which report you want to generate?\n");
    printf("a: Expenses summary\n"
           "b: Income summary\n"
           "c: Daily report\n"
           "d: Monthly report\n"
           "e: Yearly report\n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    char c = getchar();
    switch(c){
        case'a':
            e_Summary();
        break;
        case'b':
            i_Summary();
        break;
        case'c':case'd':case'e':
            e_Report(c);
        break;
        default:
            printf("Invalid input .. please enter a letter between a & e\n");
            break;
    }

}
void closing(){
    i_exit();
    e_exit();
    exit(1);
}

void viewMainMenu(){
char choice;
    printf("Please, enter your choice:\n");
    printf("a:Add an expense    "
           "b:Edit an expense    "
           "c:Delete an expense    "
           "  d:Add an income\n"
           "e:Edit an income    "
           "f:Delete an income    "
           "g:View transactions    "
           "h:Generate financial reports.\n"
           "q:Quit the program\n");
    fseek(stdin, 0, SEEK_END); //Ignoring any past input
    choice = getchar();
    switch(choice){
        case'a':
            if(addExpense())
                printf("Added new expense successfully\n");
            else
                printf("Can't add new expense\n");
            break;
        case'b':
            printExpense();
            editExpense();
            break;
        case'c':
            printExpense();
            deleteExpense();
            break;
        case'd':
           if(addIncome())
               printf("Added new income successfully\n");
           else
               printf("Can't add new income\n");
           break;
        case'e':{
            printIncome();
            char str[50];
            printf("Enter the id of the income you want to edit\n");
            char * ptr;
            fseek(stdin, 0, SEEK_END); //Ignoring any past input
            fgets(str, 50, stdin);
            int id = strtol(str, &ptr, 10);
            if(editIncome(id))
                printf("The income of id %d is edited successfully\n",id);
            else
                printf("Can't edit the income of id %d\n",id);
        }
            break;
        case'f':
            printIncome();
            if(deleteIncome())
                printf("Deleted income successfully");
            else
                printf("Can't delete income");

            break;
        case'g':
            viewTransactions();
            break;
        case 'h':
            viewReports();
            break;
        case'q':
            printf("Closing the program...\n");
            closing();
        default:
            printf("Invalid input! please enter a letter between a & h or enter q to quit the program \n");
            break;
    }
}

int main() {
    viewStartMsg();
    setup_i();
    setup_e();
 while(1){
     viewMainMenu();
 }
}
