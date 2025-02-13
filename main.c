#include "expense.h"

int main() {
    load_expenses_from_file();  // Load previous expenses from file at start

    int choice;
    do {
        printf("\nExpense Tracker Menu:");
        printf("\n1. Add Expense");
        printf("\n2. View Expenses");
        printf("\n3. Calculate Total by Category");
        printf("\n4. Generate Spending Report");
        printf("\n5. Sort Expenses by Amount");
        printf("\n6. Sort Expenses by Category");
        printf("\n7. Delete an Expense Entry");
        printf("\n8. Save & Exit");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: Add_Expense(); break;
            case 2: View_Expense(); break;
            case 3: Calculate_Total_by_category(); break;
            case 4: Generate_Report(); break;
            case 5: sorting_by_amount(); break;
            case 6: sorting_by_category(); break;
            case 7: Delete_an_entry(); break;
            case 8: 
                store_expenses_to_file(); 
                printf("Saving and Exiting the Expense Tracker...\n"); 
                break;
            default: 
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}
