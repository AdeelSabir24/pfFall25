#include <stdio.h>
#include <string.h>

#define TOGGLE_MASK ((1 << 1) | (1 << 4))  

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void encodeMessage(char message[]) {
    reverseString(message);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= TOGGLE_MASK;
    }
    printf("\nEncoded Message: %s\n", message);
}

void decodeMessage(char message[]) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= TOGGLE_MASK;
    }
    reverseString(message);
    printf("\nDecoded Message: %s\n", message);
}

int main() {
    char message[200];
    int choice;

    do {
        printf("\n=============================================\n");
        printf("     TCS SECURE MESSAGE ENCODER / DECODER     \n");
        printf("=============================================\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printf("\nEnter the message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                encodeMessage(message);
                break;

            case 2:
                printf("\nEnter the message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decodeMessage(message);
                break;

            case 3:
                printf("\nExiting system... Stay secure!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}
