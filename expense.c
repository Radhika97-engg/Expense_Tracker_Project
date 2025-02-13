#include "expense.h"

Expense *head = NULL;  // Global linked list head for expenses
Category_Summary *categoryhead = NULL;  // Linked list for category-wise summary

// Function to add an expense
void Add_Expense() {
    Expense *new_expense = malloc(sizeof(Expense));
    if (!new_expense) {
        printf("Memory allocation Failed\n");
        return;
    }

    new_expense->Category = malloc(50);
    new_expense->Date = malloc(20);

    if (!new_expense->Category || !new_expense->Date) {
        printf("Memory allocation failed\n");
        free(new_expense);
        return;
    }

    clear_input_buffer();

    printf("Enter the Category: ");
    fgets(new_expense->Category, 50, stdin);
    new_expense->Category[strcspn(new_expense->Category, "\n")] = '\0';

    printf("Enter the Amount: ");
    scanf("%f", &new_expense->Amount);
    clear_input_buffer();

    printf("Enter the Date (Format: DD-MM-YYYY): ");
    fgets(new_expense->Date, 20, stdin);
    new_expense->Date[strcspn(new_expense->Date, "\n")] = '\0';

    new_expense->next = head;
    head = new_expense;

    printf("Expense Added: %s under %s of amount %.2f\n",
           new_expense->Date, new_expense->Category, new_expense->Amount);
}

// Function to view all expenses
void View_Expense() {
    Expense *temp = head;
    if (temp == NULL) {
        printf("No expenses recorded yet\n");
        return;
    }
    printf("\nDate        | Category        | Amount\n");
    printf("--------------------------------------\n");
    while (temp != NULL) {
        printf("%-12s | %-15s | %.2f\n", temp->Date, temp->Category, temp->Amount);
        temp = temp->next;
    }
}

// Function to delete an expense
void Delete_an_entry() {
    if (head == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    char category[50];
    float amount;
    
    printf("Enter the Expense Category you want to remove: ");
    clear_input_buffer();
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0';

    printf("Enter the amount to be deleted: ");
    scanf("%f", &amount);

    Expense *current = head;
    Expense *prev = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcasecmp(category, current->Category) == 0 && current->Amount == amount) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->Category);
            free(current->Date);
            free(current);

            printf("The expense in category '%s' of amount %.2f deleted successfully.\n", category, amount);
            found = 1;
            break;
        }

        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("No matching expense found for category '%s' with amount %.2f\n", category, amount);
    }
}

// Function to calculate total expenses by category
void Calculate_Total_by_category() {
    if (head == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    char category_name[50];
    float total = 0.0;
    int found = 0;

    printf("Enter the category for which you want the total expense: ");
    clear_input_buffer();
    fgets(category_name, 50, stdin);
    category_name[strcspn(category_name, "\n")] = '\0';

    Expense *temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->Category, category_name) == 0) {
            total += temp->Amount;
            found = 1;
        }
        temp = temp->next;
    }

    if (found) {
        printf("Total spending on %s: %.2f\n", category_name, total);
    } else {
        printf("No expenses found for the given category.\n");
    }
}

// Function to generate spending report by month
void Generate_Report() {
    if (head == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    char month_year[10];
    printf("Enter the Month and Year (Format: MM-YYYY): ");
    clear_input_buffer();
    fgets(month_year, 10, stdin);
    month_year[strcspn(month_year, "\n")] = '\0';

    float total = 0.0;
    Expense *temp = head;

    printf("\nDate        | Category        | Amount\n");
    printf("--------------------------------------\n");

    while (temp != NULL) {
        char date_copy[20];
        strcpy(date_copy, temp->Date);

        char *day = strtok(date_copy, "-");
        char *month = strtok(NULL, "-");
        char *year = strtok(NULL, "-");

        if (month == NULL || year == NULL) {
            temp = temp->next;
            continue;  // Skip if date format is incorrect
        }

        char temp_month_year[10];
        sprintf(temp_month_year, "%s-%s", month, year);

        if (strcmp(temp_month_year, month_year) == 0) {
            printf("%-12s | %-15s | %.2f\n", temp->Date, temp->Category, temp->Amount);
            total += temp->Amount;
        }
        temp = temp->next;
    }

    printf("--------------------------------------\n");
    printf("Total spending for %s: %.2f\n", month_year, total);
}

// Function to sort expenses by amount (descending order)
void sorting_by_amount() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough expenses to sort.\n");
        return;
    }

    Expense *ptr1, *last_node = NULL;
    int swapped;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != last_node) {
            if (ptr1->Amount < ptr1->next->Amount) {
                float temp_amount = ptr1->Amount;
                ptr1->Amount = ptr1->next->Amount;
                ptr1->next->Amount = temp_amount;

                char *temp_category = ptr1->Category;
                ptr1->Category = ptr1->next->Category;
                ptr1->next->Category = temp_category;

                char *temp_date = ptr1->Date;
                ptr1->Date = ptr1->next->Date;
                ptr1->next->Date = temp_date;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        last_node = ptr1;
    } while (swapped);

    printf("Expenses sorted by amount in descending order.\n");
}

// Function to sort expenses by category (alphabetical order)
void sorting_by_category() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough expenses to sort.\n");
        return;
    }

    Expense *ptr1, *last_node = NULL;
    int swapped;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != last_node) {
            if (strcmp(ptr1->Category, ptr1->next->Category) > 0) {
                char *temp_category = ptr1->Category;
                ptr1->Category = ptr1->next->Category;
                ptr1->next->Category = temp_category;
            }
            ptr1 = ptr1->next;
        }
        last_node = ptr1;
    } while (swapped);

    printf("Expenses sorted by category alphabetically.\n");
}

// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
