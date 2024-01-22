//
// Created by Yara on 8/7/2023.
//

#include "reports.h"
#include "../Data Structures/DS_expense/linkedList_expense.h"
#include "../Data Structures/DS_income//linkedList_income.h"

void e_Summary(){
    double total=0;
    struct e_node * fptr = NULL, *tptr=NULL,*uptr=NULL,*eptr=NULL,*optr=NULL;
    e_catogrize(&fptr,&tptr,&uptr,&eptr,&optr);
    printf("\n         Expenses Summary\n");
    printf("-------------------------------------\n");

    printf("Food Category:\n");
    e_printCat(fptr,&total);
    printf("Food Total Expenses= %lf\n",total);
    
    total=0;
    printf("Transportation Category:\n");
    e_printCat(tptr,&total);
    printf("Transportation Total Expenses= %lf\n",total);

    total=0;
    printf("Utilities Category:\n");
    e_printCat(uptr,&total);
    printf("Utilities Total Expenses= %lf\n",total);

    total=0;
    printf("Entertainment Category:\n");
    e_printCat(eptr,&total);
    printf("Entertainment Total Expenses= %lf\n",total);

    total=0;
    printf("Others:\n");
    e_printCat(optr,&total);
    printf("Others Total Expenses= %lf\n",total);

}

void i_Summary(){
    double total=0;
    struct i_node * sptr=NULL, *pptr=NULL, *fptr=NULL,*optr=NULL, *iptr=NULL;
    i_catogrize(&sptr,&pptr,&fptr,&optr,&iptr);

    printf("\n         Incomes Summary\n");
    printf("------------------------------------\n");

    printf("Salary incomes:\n");
    i_printCat(sptr,&total);
    printf("Total Salary Income = %lf\n",total);

    total=0;
    printf("\nPart-time job incomes:\n");
    i_printCat(pptr,&total);
    printf("Total Part-time job Income = %lf\n",total);

    total=0;
    printf("\nFreelancing incomes:\n");
    i_printCat(fptr,&total);
    printf("Total Freelancing Income = %lf\n",total);

    total=0;
    printf("\nOvertime incomes:\n");
    i_printCat(optr,&total);
    printf("Total Overtime Income = %lf\n",total);

    total=0;
    printf("\nInvestment income:\n");
    i_printCat(iptr,&total);
    printf("Total Investment Income = %lf\n",total);
}

struct map * i_insertToDays(){
    if (incomes_ll == NULL)
        return NULL;
    struct i_node *i_ptr = incomes_ll;
    char *temp;
    int prevD=strtol(i_ptr->data.date, &temp, 10);
    int prevM = strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map *m = malloc(sizeof(struct map)), *m_ptr = m;
    char d[3];
    char mo[3];
    char y [20];
    sprintf(d, "%d", prevD);
    sprintf(mo, "%d", prevM);
    sprintf(y, "%d", prevY);

    if(prevD< 10 ) {
        d[1]=d[0];
        d[0]='0';
    }

    if(prevM < 10 ) {
        mo[1]=mo[0];
        mo[0]='0';
    }
    // Concatenate both strings
    strcat(y, mo);
    strcat(y,d);

    m->p.key = strtol(y,&temp,10);
    m->p.value = i_ptr->data.value;
    m->next = NULL;
    i_ptr = i_ptr->next;
    m_ptr = m;
    while (i_ptr != NULL) {
        int da=strtol(i_ptr->data.date, &temp, 10);
        int mon = strtol(++temp, &temp, 10);
        int ye = strtol(++temp, &temp, 10);
        if (ye == prevY && mon == prevM && da == prevD) //add to prev value
        {
            m_ptr->p.value += i_ptr->data.value;
        } else {
            struct map *newnode = malloc(sizeof(struct map));
            newnode->p.value = i_ptr->data.value;
            sprintf(mo, "%d", mon);
            sprintf(y, "%d", ye);
            sprintf(d, "%d", da);
            if(da< 10 ) {
                d[1]=d[0];
                d[0]='0';
            }
            if(mon < 10 ) {
                mo[1]=mo[0];
                mo[0]='0';
            }
            strcat(y, mo);
            strcat(y, d);
            newnode->p.key = strtol(y,&temp,10);
            newnode->next = NULL;
            m_ptr->next = newnode;
        }
        prevD=da;
        prevY=ye;
        prevM=mon;
        i_ptr = i_ptr->next;
    }
    return m;
}

struct map * e_insertToDays(){
    if (expenses_ll == NULL)
        return NULL;
    struct e_node *e_ptr = expenses_ll;
    char *temp;
    int prevD=strtol(e_ptr->data.date, &temp, 10);
    int prevM = strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map *m = malloc(sizeof(struct map)), *m_ptr = m;
    char d[3];
    char mo[3];
    char y [20];
    sprintf(mo, "%d", prevM);
    sprintf(y, "%d", prevY);
    sprintf(d, "%d", prevD);
    if(prevD< 10 ) {
        d[1]=d[0];
        d[0]='0';
    }
    if(prevM < 10 ) {
        mo[1]=mo[0];
        mo[0]='0';
    }
    // Concatenate both strings
    strcat(y, mo);
    strcat(y, d);
    m->p.key = strtol(y,&temp,10);
    m->p.value = e_ptr->data.value;
    m->next = NULL;
    e_ptr = e_ptr->next;
    m_ptr = m;
    while (e_ptr != NULL) {
        int da = strtol(e_ptr->data.date, &temp, 10);
        int mon = strtol(++temp, &temp, 10);
        int ye = strtol(++temp, &temp, 10);
        if (ye == prevY && mon == prevM) //add to prev value
        {
            m_ptr->p.value += e_ptr->data.value;
        } else {
            struct map *newnode = malloc(sizeof(struct map));
            newnode->p.value = e_ptr->data.value;
            sprintf(mo, "%d", mon);
            sprintf(y, "%d", ye);
            sprintf(d, "%d", da);
            if(da< 10 ) {
                d[1]=d[0];
                d[0]='0';
            }
            if(mon < 10 ) {
                mo[1]=mo[0];
                mo[0]='0';
            }
            strcat(y, mo);
            strcat(y, d);
            newnode->p.key = strtol(y,&temp,10);
            newnode->next = NULL;
            m_ptr->next = newnode;
        }
        prevD=da;
        prevY=ye;
        prevM=mon;
        e_ptr = e_ptr->next;
    }
    return m;
}


struct map * i_insertToMonths(){
    if (incomes_ll == NULL)
        return NULL;
    struct i_node *i_ptr = incomes_ll;
    char *temp;
    strtol(i_ptr->data.date, &temp, 10);
    int prevM = strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map *m = malloc(sizeof(struct map)), *m_ptr = m;
    char mo[3];
    char y [20];
    sprintf(mo, "%d", prevM);
    sprintf(y, "%d", prevY);
    if(prevM < 10 ) {
        mo[1]=mo[0];
        mo[0]='0';
    }
    // Concatenate both strings
    strcat(y, mo);
    m->p.key = strtol(y,&temp,10);
    m->p.value = i_ptr->data.value;
    m->next = NULL;
    i_ptr = i_ptr->next;
    m_ptr = m;
    while (i_ptr != NULL) {
        strtol(i_ptr->data.date, &temp, 10);
        int mon = strtol(++temp, &temp, 10);
        int ye = strtol(++temp, &temp, 10);
        if (ye == prevY && mon == prevM) //add to prev value
        {
            m_ptr->p.value += i_ptr->data.value;
        } else {
            struct map *newnode = malloc(sizeof(struct map));
            newnode->p.value = i_ptr->data.value;
            sprintf(mo, "%d", mon);
            sprintf(y, "%d", ye);
            if(mon < 10 ) {
                mo[1]=mo[0];
                mo[0]='0';
            }
            strcat(y, mo);
            newnode->p.key = strtol(y,&temp,10);
            newnode->next = NULL;
            m_ptr->next = newnode;
        }
        prevY=ye;
        prevM=mon;
        i_ptr = i_ptr->next;
    }
    return m;
}

struct map * e_insertToMonths(){
    if (expenses_ll == NULL)
        return NULL;
    struct e_node *e_ptr = expenses_ll;
    char *temp;
    strtol(e_ptr->data.date, &temp, 10);
    int prevM = strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map *m = malloc(sizeof(struct map)), *m_ptr = m;
    char mo[3];
    char y [20];
    sprintf(mo, "%d", prevM);
    sprintf(y, "%d", prevY);
    if(prevM < 10 ) {
        mo[1]=mo[0];
        mo[0]='0';
    }
    // Concatenate both strings
    strcat(y, mo);
    m->p.key = strtol(y,&temp,10);
    m->p.value = e_ptr->data.value;
    m->next = NULL;
    e_ptr = e_ptr->next;
    m_ptr = m;
    while (e_ptr != NULL) {
        strtol(e_ptr->data.date, &temp, 10);
        int mon = strtol(++temp, &temp, 10);
        int ye = strtol(++temp, &temp, 10);
        if (ye == prevY && mon == prevM) //add to prev value
        {
            m_ptr->p.value += e_ptr->data.value;
        } else {
            struct map *newnode = malloc(sizeof(struct map));
            newnode->p.value = e_ptr->data.value;
            sprintf(mo, "%d", mon);
            sprintf(y, "%d", ye);
            if(mon < 10 ) {
                mo[1]=mo[0];
                mo[0]='0';
            }
            strcat(y, mo);
            newnode->p.key = strtol(y,&temp,10);
            newnode->next = NULL;
            m_ptr->next = newnode;
        }
        prevY=ye;
        prevM=mon;
        e_ptr = e_ptr->next;
    }
    return m;
}


struct map * i_insertToYears() {
    if (incomes_ll == NULL)
        return NULL;
    struct i_node *i_ptr = incomes_ll;
    char *temp;
    strtol(i_ptr->data.date, &temp, 10);
    strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map *m = malloc(sizeof(struct map)), *m_ptr = m;
    m->p.key = prevY;
    m->p.value = i_ptr->data.value;
    m->next = NULL;
    i_ptr = i_ptr->next;
    m_ptr = m;
    while (i_ptr != NULL) {
        strtol(i_ptr->data.date, &temp, 10);
        strtol(++temp, &temp, 10);
        int y = strtol(++temp, &temp, 10);
        if (y == prevY) //add to prev value
        {
            m_ptr->p.value += i_ptr->data.value;
        } else {
            struct map *newnode = malloc(sizeof(struct map));
            newnode->p.value = i_ptr->data.value;
            newnode->p.key = y;
            newnode->next = NULL;
            m_ptr->next = newnode;
        }
        prevY=y;
        i_ptr = i_ptr->next;
    }

    return m;
}

struct map * e_insertToYears(){
    if(expenses_ll == NULL )
        return NULL;
    struct e_node * i_ptr = expenses_ll;
    char * temp;
    strtol(i_ptr->data.date, &temp, 10);
    strtol(++temp, &temp, 10);
    int prevY = strtol(++temp, &temp, 10);
    struct map* m =  malloc(sizeof (struct map)),*m_ptr=m;
    m->p.key=prevY;
    m->p.value=i_ptr->data.value;
    m->next=NULL;
    i_ptr=i_ptr->next;
    m_ptr = m;
    while(i_ptr != NULL){
        strtol(i_ptr->data.date, &temp, 10);
        strtol(++temp, &temp, 10);
        int y = strtol(++temp, &temp, 10);
        if(y == prevY) //add to prev value
        {
            m_ptr->p.value+=i_ptr->data.value;
        }
        else{
            struct map *newnode = malloc(sizeof (struct map));
            newnode->p.value=i_ptr->data.value;
            newnode->p.key=y;
            newnode->next=NULL;
            m_ptr->next=newnode;
        }
            i_ptr=i_ptr->next;
    }

    return m;
}

void dailyReport(){
    struct map *mi = i_insertToDays();
    struct map * me = e_insertToDays();
    double total;
    printf("\n        Daily Report\n");
    printf("----------------------------------\n");
    while(mi != NULL || me != NULL){
        if(mi->p.key == me->p.key){ //same month
            total = mi->p.value - me->p.value;
            printf("Net Value in year %d month %d day %d = %lf\n",((mi->p.key)/10000),((mi->p.key)/100)%100,(mi->p.key ) % 100,total);
            mi=mi->next;
            me=me->next;
        }
        else if(mi->p.key < me->p.key){
            total = mi->p.value;
            printf("Net Value in year %d month %d day %d = %lf\n",((mi->p.key)/10000),((mi->p.key)/100)%100,(mi->p.key ) % 100,total);
            mi=mi->next;

        }
        else{
            total = - (me->p.value);
            printf("Net Value in year %d month %d day %d = %lf\n",((mi->p.key)/10000),((mi->p.key)/100)%100,(mi->p.key ) % 100,total);
            me=me->next;
        }
    }
}
void monthlyReport(){
    struct map *mi = i_insertToMonths();
    struct map * me = e_insertToMonths();
    double total;
    printf("\n        Monthly Report\n");
    printf("----------------------------------\n");
    while(mi != NULL || me != NULL){
        if(mi->p.key == me->p.key){ //same month
            total = mi->p.value - me->p.value;
            printf("Net Value in year %d month %d = %lf\n",(mi->p.key)/100,(mi->p.key ) % 100,total);
            mi=mi->next;
            me=me->next;
        }
        else if(mi->p.key < me->p.key){
            total = mi->p.value;
            printf("Net Value in year %d month %d = %lf\n",(mi->p.key)/100,(mi->p.key ) % 100,total);
            mi=mi->next;

        }
        else{
            total = - (me->p.value);
            printf("Net Value in year %d month %d = %lf\n",(mi->p.key)/100,(mi->p.key ) % 100,total);
            me=me->next;
        }
    }
}
void yearlyReport(){
    struct map *mi = i_insertToYears();
    struct map * me = e_insertToYears();
    double total;
    printf("\n        Yearly Report\n");
    printf("----------------------------------\n");
    while(mi != NULL || me != NULL){
        if(mi->p.key == me->p.key){ //same year
            total = mi->p.value - me->p.value;
            printf("Net Value in year %d = %lf\n",mi->p.key,total);
            mi=mi->next;
            me=me->next;
        }
        else if(mi->p.key < me->p.key){
            total = mi->p.value;
            printf("Net Value in year %d = %lf\n",mi->p.key,total);
            mi=mi->next;

        }
        else{
            total = - (me->p.value);
            printf("Net Value in year %d = %lf\n",me->p.key,total);
            me=me->next;
        }
    }
}
void e_Report(char c){
    switch (c) {
        case'c':
            dailyReport();
            break;
        case 'd':
            monthlyReport();
            break;
        case'e':
            yearlyReport();
            break;
        default:break;

    }
}