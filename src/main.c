#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "validation.h"

char fileName[100];

int startup(const char *fileName) {
    int choice;
    FILE *file;
    strcpy(initialFileName, fileName);
    file = fopen(fileName, "a+"); // Open file in append mode

    // Error handling
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    do {
        // Print instructions to user
        printf("\nSelect an option:\n");
        printf("1. Save/Edit new entry\n");
        printf("2. Retrieve existing information from the file that is open\n");
        printf("3. Exit\n");
        printf("4. Change the file\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Switch to decide which action to take with the dataset
        switch (choice) {
            case 1:
                saveNewEntry(file);
                break;
            case 2:
                retrieveInformation(file);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            case 4:
                printf("Enter the new file name: ");
                scanf("%s", fileName);
                fclose(file);
                return startup(fileName);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    // Close the file
    fclose(file);
    return 0;
}

int main() {
    printf("Welcome to Alpha weightlifters \nEnter a new secret space to store your weight (or choose existing one (e.g., database.csv)): ");
    scanf("%s", fileName);
    return startup(fileName);
}

// To compile and execute, type the following code on your terminal ---> gcc -o address_book main.c address_book.c validation.c 
