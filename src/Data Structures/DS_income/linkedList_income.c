//
// Created by Yara on 8/6/2023.
//

#include "linkedList_income.h"
#include <stdio.h>
#include <stdlib.h>

struct  i_node * incomes_ll=NULL;
int i_count = 0;



void i_initialize(FILE* filePtr){
    struct income *temp=(struct income*) malloc(sizeof(struct income));
    char buffer[1000];
    char * t,*ptr;
    //TODO: assign to ll
    while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
        t = strtok(buffer, " - ");
        temp->id=strtol(t,&ptr,10);

        t = strtok(NULL, " - ");
        temp->value= strtod(t,&ptr);

        t = strtok(NULL, " - ");
        strcpy_s(temp->date,11,t);

        t = strtok(NULL, " - ");
        strcpy_s(temp->des,100,t);

        t = strtok(NULL, " - ");
        temp->s=setSource(t);

        i_insert(temp);
    }
    fclose(filePtr);
}

void i_printList(){
    struct i_node *p = incomes_ll;
    while(p != NULL) {
        printf("Income %d\tvalue = %lf\tDate:%s\nDescription:%s\tSource:%s\n",p->data.id,p->data.value,p->data.date,p->data.des,
               getSource(p->data.s));
        p = p->next;
    }
}
void i_printCat(struct i_node * head,double * total){
    if(head == NULL){
        printf("No Income from this source\n");
    }
    struct i_node *p = head;
    while(p != NULL) {
        printf("Income %d\tvalue = %lf\tDate:%s\nDescription:%s\t Source:%s\n",p->data.id,p->data.value,p->data.date,p->data.des,
               getSource(p->data.s) );
        (*total)+=p->data.value;
        p = p->next;
    }
}

bool i_printFile(){
    struct i_node *p = incomes_ll;
    FILE * filePtr = fopen("D:\\Trainings\\EmbeddedSystems\\Labs\\1\\Data\\incomes.txt","w");
    if (filePtr == NULL) {
        printf("Error opening the income file.\n");
        return false;
    }

    while(p != NULL) {
        fprintf(filePtr, "%d - %lf - %s - %s - %s\n",p->data.id,p->data.value,p->data.date,p->data.des,
                getSource(p->data.s) );
        p = p->next;
    }
    return true;
}

void i_insert(struct income * data){
    struct i_node *lk = (struct i_node*) malloc(sizeof(struct i_node));
    lk->data = *data;
    lk->next=NULL;
    lk->data.id=++i_count;
    if(incomes_ll == NULL || cmpDate(incomes_ll->data.date,data->date))
    {
        lk->next=incomes_ll;
        incomes_ll = lk;
        return;
    }

    struct i_node *ptr = incomes_ll;
    while(ptr->next != NULL && !cmpDate(ptr->data.date,data->date))
        ptr = ptr->next;

    lk->next = ptr->next;
    ptr->next = lk;
}

void i_insertToCat(struct i_node **head , struct income * data ){

    struct i_node *lk = (struct i_node*) malloc(sizeof(struct i_node));
    lk->data = *data;
    lk->next=NULL;
    if(*head == NULL)
    {
        *head = lk;
        return;
    }

    struct i_node *ptr = *head;
    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = lk;
}

void i_catogrize(struct i_node **sptr, struct i_node **pptr, struct i_node **fptr, struct i_node **optr,
                 struct i_node **iptr){
    struct i_node *ptr = incomes_ll;
    struct income tempData;
    while(ptr != NULL){
        switch(ptr->data.s){
            case salary :
                tempData=ptr->data;
                i_insertToCat(sptr,&tempData);
                break;
            case partTimeJob :
                tempData=ptr->data;
                i_insertToCat(pptr,&tempData);
                break;
            case freelancing :
                tempData=ptr->data;
                i_insertToCat(fptr,&tempData);
                break;
            case overtime:
                tempData=ptr->data;
                i_insertToCat(optr,&tempData);
                break;
            case investment:
                tempData=ptr->data;
                i_insertToCat(iptr,&tempData);
                break;
            default:break;
        }
        ptr=ptr->next;
    }
}

bool i_deleteNode(int key){
    //TODO Handle memory
    struct i_node *temp = incomes_ll, *prev;
    if (temp != NULL && temp->data.id == key) {
        incomes_ll = temp->next; //Node to be deleted is head
        return true;
    }
    while (temp != NULL && temp->data.id != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not present
    if (temp == NULL) {
        printf("id not found\n");
        return false; }

    // Remove the i_node
    prev->next = temp->next;
    return true;
}

struct i_node * i_searchList(int key){
    struct i_node *temp = incomes_ll;
    while(temp != NULL) {
        if (temp->data.id == key) {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void i_deleteList(){
    struct i_node *temp = incomes_ll;
    while(temp) {
        i_deleteNode(temp->data.id);
        temp=temp->next;
    }
}
