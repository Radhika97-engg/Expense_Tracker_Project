
#include "expense.h"

void load_expenses_from_file() {
    FILE *fp = fopen("expense.txt", "r");
    if (!fp) {
        printf("No previous expenses recorded.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        char *date = strtok(line, "|");
        char *category = strtok(NULL, "|");
        char *amount_str = strtok(NULL, "|");

        if (!date || !category || !amount_str) continue; // Skip invalid lines

        Expense *new_expense = malloc(sizeof(Expense));
        if (!new_expense) {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return;
        }

        new_expense->Date = malloc(strlen(date) + 1);
        if (new_expense->Date) strcpy(new_expense->Date, date);

        new_expense->Category = malloc(strlen(category) + 1);
        if (new_expense->Category) strcpy(new_expense->Category, category);

        new_expense->Amount = strtof(amount_str, NULL);
        new_expense->next = head;
        head = new_expense;
    }

    fclose(fp);
}

// Function to store expenses in a file
void store_expenses_to_file() {
    FILE *fp = fopen("expense.txt", "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    Expense *temp = head;
    while (temp) {
        fprintf(fp, "%s|%s|%.2f\n", temp->Date, temp->Category, temp->Amount);
        temp = temp->next;
    }

    fclose(fp);
}
