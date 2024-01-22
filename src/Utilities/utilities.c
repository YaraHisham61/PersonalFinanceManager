//
// Created by Yara on 8/6/2023.
//

#include "utilities.h"

bool checkDateFormat(char date[]){
    if (date == NULL  || date[2] != '/'|| date[5] != '/' ) //Checking length & format
        return 0;
    short i=0;
    while(date[i++] != '\0' && i<15)
        ;
    if(i != 11)
        return false;
    for (i = 0; i < 10; i++) //Checking there is no extra '/'
    {
        if (i == 2 || i ==5)
            continue;
        if (date[i] == '/')
            return 0;
    }
    char * temp;
    int d = strtol(date, &temp, 10);
    int m = strtol(++temp, &temp, 10);
    int y = strtol(++temp, &temp, 10);
    if (d <= 0 || m <= 0 || y <= 0 || d > 31 || m > 12) //Checking range of day,month and year
        return 0;
    if (m == 2) //handling of Feb. month
    {
        if ((date[8] == '0' &&  date[9] == '0')) //End of century years that ends with 00
            i=0;
        if ((i==0 && y % 400 == 0) ||(i !=0 && y % 4 == 0)) //Leap year
            if (d > 29)
                return false;
        if (y % 4 != 0 && d > 28)
            return false;
    }
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) //Months with 30 days only
        return false;
    if(y > 2023)
        return false;
    return true;
}

bool cmpDate(const char *date1, const char *date2) {
    char * temp;
    int d1 = strtol(date1, &temp, 10);
    int m1 = strtol(++temp, &temp, 10);
    int y1 = strtol(++temp, &temp, 10);

    int d2 = strtol(date2, &temp, 10);
    int m2 = strtol(++temp, &temp, 10);
    int y2 = strtol(++temp, &temp, 10);

    if(y1>y2)
        return true;
    if(y1 == y2 && m1>m2)
        return true;
    if(y1 == y2 && m1 == m2 && d1>d2)
        return true;
    return false;
}