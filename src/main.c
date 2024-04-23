#include <stdio.h>
#include "address_book.h"

int startup() {
    int choice;
    FILE *file;
    char filename[100];

    printf("Welcome to Alpha weightlifters\n");

    printf("Enter a new secret space to store your weight (or choose existing one (that also works)) (e.g., database.csv): ");
    scanf("%s", filename);

    file = fopen(filename, "a+"); // Open file in append mode

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    do {
        printf("\nSelect an option:\n");
        printf("1. Save new entry\n");
        printf("2. Retrieve existing information from the file that is open\n");
        printf("3. Exit\n");
        printf("4. change the file");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                printf("which file do u Want to access? (if u miss Srry G u dumb)");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}

int main() {
    return startup();
}

//                                                 gcc -o address_book main.c address_book.c validation.c  
// don't judge me I don't like rewriting this shit
