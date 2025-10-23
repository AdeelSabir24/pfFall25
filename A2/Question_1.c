#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

int findBookIndex(int isbns[], int totalBooks, int searchISBN) {
    for (int i = 0; i < totalBooks; i++) {
        if (isbns[i] == searchISBN)
            return i;
    }
    return -1;
}

void addNewBook(int isbns[], char titles[][50], float prices[], int stock[], int *totalBooks) {
    if (*totalBooks >= MAX_BOOKS) {
        printf("\nInventory is full. Cannot add more books.\n");
        return;
    }

    int newISBN;
    printf("\nEnter ISBN: ");
    scanf("%d", &newISBN);

    if (findBookIndex(isbns, *totalBooks, newISBN) != -1) {
        printf("\nA book with this ISBN already exists.\n");
        return;
    }

    getchar();
    printf("Enter Book Title: ");
    fgets(titles[*totalBooks], 50, stdin);
    titles[*totalBooks][strcspn(titles[*totalBooks], "\n")] = '\0';

    printf("Enter Price (PKR): ");
    scanf("%f", &prices[*totalBooks]);

    printf("Enter Quantity in Stock: ");
    scanf("%d", &stock[*totalBooks]);

    isbns[*totalBooks] = newISBN;
    (*totalBooks)++;

    printf("\nBook added successfully!\n");
}

void processBookSale(int isbns[], int stock[], int totalBooks) {
    if (totalBooks == 0) {
        printf("\nNo books in inventory yet.\n");
        return;
    }

    int saleISBN, quantitySold;
    printf("\nEnter ISBN of the book to sell: ");
    scanf("%d", &saleISBN);

    int index = findBookIndex(isbns, totalBooks, saleISBN);
    if (index == -1) {
        printf("\nBook not found in inventory.\n");
        return;
    }

    printf("Enter quantity to sell: ");
    scanf("%d", &quantitySold);

    if (quantitySold > stock[index]) {
        printf("\nNot enough copies available. Current stock: %d\n", stock[index]);
    } else {
        stock[index] -= quantitySold;
        printf("\nSale successful. Remaining stock: %d\n", stock[index]);
    }
}

void showLowStockBooks(int isbns[], char titles[][50], float prices[], int stock[], int totalBooks) {
    if (totalBooks == 0) {
        printf("\nNo books in inventory.\n");
        return;
    }

    printf("\n===== LOW STOCK REPORT (Less than 5 copies) =====\n");
    int found = 0;

    for (int i = 0; i < totalBooks; i++) {
        if (stock[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: Rs. %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], stock[i]);
            found = 1;
        }
    }

    if (!found)
        printf("All books have sufficient stock.\n");
}

int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int stock[MAX_BOOKS];
    int totalBooks = 0;
    int choice;

    do {
        printf("\n=============================================\n");
        printf("         LIBERTY BOOKS INVENTORY SYSTEM       \n");
        printf("=============================================\n");
        printf("1. Add a New Book\n");
        printf("2. Process a Book Sale\n");
        printf("3. View Low Stock Books\n");
        printf("4. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewBook(isbns, titles, prices, stock, &totalBooks);
                break;

            case 2:
                processBookSale(isbns, stock, totalBooks);
                break;

            case 3:
                showLowStockBooks(isbns, titles, prices, stock, totalBooks);
                break;

            case 4:
                printf("\nExiting program. Have a nice day!\n");
                break;

            default:
                printf("\nInvalid option. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
