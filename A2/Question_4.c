#include <stdio.h>

#define MAX_SIZE 5

int push(int stack[], int top) {
    int value;
    if (top == MAX_SIZE - 1) {
        printf("\nStack Overflow! Cannot push more elements.\n");
        return top;
    }

    printf("\nEnter value to push: ");
    scanf("%d", &value);

    top++;
    stack[top] = value;
    printf("Element %d pushed successfully.\n", value);

    return top;
}

int pop(int stack[], int top) {
    if (top == -1) {
        printf("\nStack Underflow! No element to pop.\n");
        return top;
    }

    printf("\nElement %d popped successfully.\n", stack[top]);
    top--;

    return top;
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("\nStack is empty.\n");
        return;
    }

    printf("\nTop element: %d\n", stack[top]);
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("\nStack is empty.\n");
        return;
    }

    printf("\n=========== CURRENT STACK ===========\n");
    for (int i = top; i >= 0; i--) {
        printf("|  %d  |\n", stack[i]);
    }
    printf("=====================================\n");
}

int main() {
    int stack[MAX_SIZE];
    int top = -1;
    int choice;

    do {
        printf("\n=====================================\n");
        printf("        STACK IMPLEMENTATION MENU     \n");
        printf("=====================================\n");
        printf("1. PUSH (Insert Element)\n");
        printf("2. POP (Remove Element)\n");
        printf("3. PEEK (View Top Element)\n");
        printf("4. DISPLAY (View All Elements)\n");
        printf("5. EXIT\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                top = push(stack, top);
                break;
            case 2:
                top = pop(stack, top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("\nExiting program... Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
