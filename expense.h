#ifndef EXPENSE_H
#define EXPENSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an expense entry
typedef struct Expense {
    float Amount;
    char *Category;
    char *Date;
    struct Expense *next;
} Expense;

// Structure for category-wise summary
typedef struct Category_Summary {
    char Category_name[50];
    float Totals;
    struct Category_Summary *next;
} Category_Summary;

// Global pointers for linked lists
extern Expense *head;
extern Category_Summary *categoryhead;

// Function declarations
void Add_Expense();
void View_Expense();
void Delete_an_entry();
void load_expenses_from_file();
void store_expenses_to_file();
void Calculate_Total_by_category();
void sorting_by_amount();
void sorting_by_category();
void Generate_Report();
void clear_input_buffer();

#endif
