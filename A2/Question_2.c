#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_CART 10

void customerInfo(char name[], char cnic[]) {
    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", name);

    printf("Enter Customer CNIC: ");
    scanf(" %[^\n]", cnic);

    printf("\nCustomer information saved successfully.\n");
}

void displayInventory(int codes[], int quantity[], float price[], int totalProducts) {
    printf("\n================ CURRENT INVENTORY ================\n");
    printf("Product Code      Quantity in Stock     Price per Product\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < totalProducts; i++) {
        printf("%03d                %5d                  Rs. %.2f\n", codes[i], quantity[i], price[i]);
    }
}

int findProduct(int codes[], int totalProducts, int code) {
    for (int i = 0; i < totalProducts; i++) {
        if (codes[i] == code)
            return i;
    }
    return -1;
}

void addToCart(int codes[], int quantity[], float price[], int cartCodes[], int cartQty[], int *cartCount, int totalProducts) {
    int code, qty;

    displayInventory(codes, quantity, price, totalProducts);

    printf("\nEnter Product Code to add to cart: ");
    scanf("%d", &code);

    int index = findProduct(codes, totalProducts, code);
    if (index == -1) {
        printf("Invalid Product Code!\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &qty);

    if (qty > quantity[index]) {
        printf("Not enough stock available!\n");
        return;
    }

    cartCodes[*cartCount] = code;
    cartQty[*cartCount] = qty;
    (*cartCount)++;

    quantity[index] -= qty;
    printf("\nProduct added to cart successfully.\n");
}

float displayTotalBill(int codes[], float price[], int cartCodes[], int cartQty[], int cartCount) {
    char promo[20];
    float total = 0.0;

    for (int i = 0; i < cartCount; i++) {
        int index = findProduct(codes, MAX_PRODUCTS, cartCodes[i]);
        total += price[index] * cartQty[i];
    }

    printf("\nEnter promocode (if any): ");
    scanf(" %[^\n]", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        printf("\nPromocode applied! You received a 25%% discount.\n");
        total *= 0.75;
    } else {
        printf("\nNo valid promocode applied.\n");
    }

    printf("\nYour total bill is: Rs. %.2f\n", total);
    return total;
}

void showInvoice(char name[], char cnic[], int codes[], float price[], int cartCodes[], int cartQty[], int cartCount, float total) {
    printf("\n===================== CUSTOMER INVOICE =====================\n");
    printf("Customer Name : %s\n", name);
    printf("Customer CNIC : %s\n", cnic);
    printf("------------------------------------------------------------\n");
    printf("Product Code         Qty         Total Price\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        int index = findProduct(codes, MAX_PRODUCTS, cartCodes[i]);
        printf("%03d                  %d          Rs. %.2f\n", cartCodes[i], cartQty[i], price[index] * cartQty[i]);
    }

    printf("------------------------------------------------------------\n");
    printf("Final Bill Amount: Rs. %.2f\n", total);
    printf("============================================================\n");
}

int main() {
    int codes[MAX_PRODUCTS] = {1, 2, 3, 4, 5};
    int quantity[MAX_PRODUCTS] = {20, 30, 25, 15, 40};
    float price[MAX_PRODUCTS] = {250.0, 120.0, 400.0, 550.0, 200.0};

    int cartCodes[MAX_CART], cartQty[MAX_CART];
    int cartCount = 0;
    char customerName[50], customerCNIC[30];
    int choice;
    float total = 0.0;

    do {
        printf("\n===================================================\n");
        printf("          SUPERMARKET INVENTORY SYSTEM              \n");
        printf("===================================================\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Product to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("===================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerInfo(customerName, customerCNIC);
                break;
            case 2:
                displayInventory(codes, quantity, price, MAX_PRODUCTS);
                break;
            case 3:
                addToCart(codes, quantity, price, cartCodes, cartQty, &cartCount, MAX_PRODUCTS);
                break;
            case 4:
                total = displayTotalBill(codes, price, cartCodes, cartQty, cartCount);
                break;
            case 5:
                showInvoice(customerName, customerCNIC, codes, price, cartCodes, cartQty, cartCount, total);
                break;
            case 6:
                printf("\nExiting system... Thank you for shopping with us!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
