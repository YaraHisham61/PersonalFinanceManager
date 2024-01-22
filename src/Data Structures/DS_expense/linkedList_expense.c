//
// Created by Yara on 8/6/2023.
//

#include "linkedList_expense.h"
#include <stdio.h>
#include <stdlib.h>

struct  e_node * expenses_ll = NULL;
int e_count=0;

void e_printList(){
    struct e_node *p = expenses_ll;
    while(p != NULL) {
        printf("Expense:%d\tvalue= %lf\tDate: %s\nDescription: %s\tCategory: %s\n",p->data.index,p->data.value,p->data.date,p->data.des,
               getCategory(p->data.c));
        p = p->next;
    }
}
void e_printCat(struct e_node * head,double * total){
    if(head == NULL){
        printf("No Expanses in this category\n");
    }
    struct e_node *p = head;
    while(p != NULL) {
        printf("Expense:%d\tvalue= %lf\tDate: %s\nDescription: %s\tCategory: %s\n",p->data.index,p->data.value,p->data.date,p->data.des,
               getCategory(p->data.c));
        (*total)+=p->data.value;
        p = p->next;
    }
}
bool e_printFile(){
    struct e_node *p = expenses_ll;
    FILE * filePtr = fopen("D:\\Trainings\\EmbeddedSystems\\Labs\\1\\Data\\expenses.txt","w");
    if (filePtr == NULL) {
        printf("Error opening the expenses file.\n");
        return false;
    }
    while(p != NULL) {
        fprintf(filePtr,"%d - %lf - %s - %s - %s\n",p->data.index,p->data.value,p->data.date,p->data.des,
               getCategory(p->data.c));
        p = p->next;
    }
    return true;
}

void e_insert(struct expense * data){
    struct e_node *lk = (struct e_node*) malloc(sizeof(struct e_node));
    lk->data = *data;
    lk->next = NULL;
    lk->data.index=++e_count;
    
    if(expenses_ll == NULL || cmpDate(expenses_ll->data.date,data->date))
    {
        lk->next=expenses_ll;
        expenses_ll = lk;
        return;
    }

    struct e_node *ptr = expenses_ll;
    while(ptr->next != NULL && !cmpDate(ptr->data.date,data->date))
        ptr = ptr->next;
    
    lk->next=ptr->next;
    ptr->next = lk;
}

void e_initialize(FILE* filePtr ){
    struct expense *temp=(struct expense*) malloc(sizeof(struct expense));
    char buffer[1000];
    char * t,*ptr;
    
    while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
        t = strtok(buffer, " - ");
        temp->index=strtol(t,&ptr,10);

        t = strtok(NULL, " - ");
        temp->value= strtod(t,&ptr);

        t = strtok(NULL, " - ");
        strcpy_s(temp->date,11,t);

        t = strtok(NULL, " - ");
        strcpy_s(temp->des,100,t);

        t = strtok(NULL, " - ");
        temp->c= setCategory(t);

        e_insert(temp);
    }
    fclose(filePtr);
}


void e_insertToCat(struct e_node **head , struct expense * data){
    
    struct e_node *lk = (struct e_node*) malloc(sizeof(struct e_node));
    lk->data = *data;
    lk->next = NULL;
    if(*head == NULL)
    {
        *head = lk;
        return;
    }

    struct e_node *ptr = *head;
    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = lk;
}

void e_catogrize(struct e_node **fptr,struct e_node **tptr,struct e_node **uptr,struct e_node **eptr,struct e_node **optr){
    struct e_node *ptr = expenses_ll;
    struct expense tempData;
    while(ptr != NULL){
        switch(ptr->data.c){
            case food :
                e_insertToCat(fptr,&tempData);
                break;
            case transportation :
                e_insertToCat(tptr,&tempData);
                break;
            case utilities :
                e_insertToCat(uptr,&tempData);
                break;
            case entertainment:
                e_insertToCat(eptr,&tempData);
                break;
            case others:
                e_insertToCat(optr,&tempData);
                break;
            default:break;
        }
        ptr=ptr->next;
    }
}


bool e_deleteNode(int key){

    struct e_node *temp = expenses_ll, *prev;
    if (temp != NULL && temp->data.index == key) {
        expenses_ll = temp->next;
        free(temp);
        return true;
    }

    // Find the key to be deleted
    while (temp != NULL && temp->data.index != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not present
    if (temp == NULL) {
        printf("id not found\n");
        return false; }

    // Remove the e_node
    prev->next = temp->next;
    free(temp);
    return true;
}
struct e_node * e_searchList(int key){
    struct e_node *temp = expenses_ll;
    while(temp != NULL) {
        if (temp->data.index == key) {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void e_deleteList(){
    struct e_node *temp = expenses_ll;
    while(temp) {
        e_deleteNode(temp->data.index);
        temp=temp->next;
    }
}
