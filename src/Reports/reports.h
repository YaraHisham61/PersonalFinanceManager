//
// Created by Yara on 8/7/2023.
//

#ifndef INC_1_REPORTS_H
#define INC_1_REPORTS_H

struct pair{
    int key;
    double value;
};

struct map {
    struct pair p;
    struct map *next;
};

void e_Summary();
void i_Summary();
void e_Report(char c);
void dailyReport();
void monthlyReport();
void yearlyReport();
struct map * i_insertToYears();
struct map * i_insertToMonths();
struct map * e_insertToMonths();
struct map * i_insertToDays();
struct map * e_insertToDays();
#endif //INC_1_REPORTS_H
