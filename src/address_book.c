#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "time.h"
#include "validation.h"

#define MAX_LINE_SIZE 1024 

char initialFileName[100];

void modifyEntry(FILE *file, const char *fileName) {
    strcpy(initialFileName, fileName);

    printf("Existing entries:\n");
    int index = 1;
    struct AddressBookEntry entry;
    rewind(file);
    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        printf("%d. %s %s\n", index, entry.name, entry.lastName);
        index++;
    }

    int entryNumber;
    printf("\nEnter the index of the entry you want to modify: ");
    scanf("%d", &entryNumber);

    rewind(file);

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        exit(EXIT_FAILURE);
    }

    int currentEntry = 1;
    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
        if (currentEntry == entryNumber) {
            // Modify selected entry
            printf("Modify entry:\n");
            printf("Select the field you want to modify:\n");
            printf("1. Name\n");
            printf("2. Last Name\n");
            printf("3. Weight\n");
            printf("4. Date\n");
            printf("5. Email\n");
            printf("6. Phone Number\n");
            int fieldChoice;
            scanf("%d", &fieldChoice);

            switch (fieldChoice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", entry.name);
                    while (!validateString(entry.name)) {
                        printf("Invalid name format. Enter a name with only letters: ");
                        scanf("%s", entry.name);
                    }
                    break;
                case 2:
                    printf("Enter new last name: ");
                    scanf("%s", entry.lastName);
                    while (!validateString(entry.lastName)) {
                        printf("Invalid last name format. Enter a last name with only letters: ");
                        scanf("%s", entry.lastName);
                    }
                    break;
                case 3:
                    printf("Enter new weight (Integer): ");
                    scanf("%d", &entry.weight);
                    break;
                case 4:
                    printf("To use current date, press 1. To enter an old date, press 2: ");
                    int dateChoice;
                    scanf("%d", &dateChoice);
                    if (dateChoice == 2) {
                        printf("Enter the old date (DD-MM-YYYY): ");
                        scanf("%s", entry.date);
                    } else {
                        // Get current date
                        time_t currentTime;
                        time(&currentTime);
                        struct tm *localTime = localtime(&currentTime);
                        sprintf(entry.date, "%02d-%02d-%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
                    }
                    break;
                case 5:
                    printf("Enter new email: ");
                    scanf("%s", entry.email);
                    while (!validateEmail(entry.email)) {
                        printf("Invalid email format. Enter a valid email: ");
                        scanf("%s", entry.email);
                    }
                    break;
                case 6:
                    printf("Enter new phone number: ");
                    scanf("%s", entry.phoneNumber);
                    while (!validatePhoneNumber(entry.phoneNumber)) {
                        printf("Invalid phone number format. Enter a valid phone number: ");
                        scanf("%s", entry.phoneNumber);
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
            
            // Check if any field is empty
            if (strlen(entry.name) == 0 || strlen(entry.lastName) == 0 || entry.weight <= 0 || strlen(entry.date) == 0 ||
                strlen(entry.email) == 0 || strlen(entry.phoneNumber) == 0) {
                printf("Error: All fields are required. Please fill in all the fields.\n");
                fclose(tempFile);
                remove("temp.csv");
                return;
            }
        }
        fprintf(tempFile, "%s,%s,%d,%s,%s,%s\n", entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
        currentEntry++;
    }

    fclose(file);
    fclose(tempFile);

    remove(initialFileName); // Use the initial file name variable
    rename("temp.csv", initialFileName); // Use the initial file name variable

    printf("Entry modified successfully!\n");
}


void saveNewEntry(FILE *file) {
    struct AddressBookEntry newEntry;
    int option;

    printf("\nEnter details for the new entry:\n");
    printf("1. Add new entry\n");
    printf("2. Modify existing entry\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    if (option == 1) {
        printf("Name: ");
        scanf("%s", newEntry.name);
        while (!validateString(newEntry.name)) {
            printf("Invalid name format. Enter a name with only letters: ");
            scanf("%s", newEntry.name);
        }

        printf("Last Name: ");
        scanf("%s", newEntry.lastName);
        while (!validateString(newEntry.lastName)) {
            printf("Invalid last name format. Enter a last name with only letters: ");
            scanf("%s", newEntry.lastName);
        }
        
        printf("Weight (Integer): ");
        scanf("%d", &newEntry.weight);
        
        int num; // Declare num variable.
        printf("To Use current date Press 1:\n");
        printf("To enter old date Press 2:\n");
        printf("Enter your choice:");
        scanf("%d", &num); 

        if (num == 2) {
            printf("Enter the old date (DD-MM-YYYY): ");
            scanf("%s", newEntry.date);
        } else {
            time_t currentTime;
            time(&currentTime);
            struct tm *localTime = localtime(&currentTime);
            sprintf(newEntry.date, "%02d-%02d-%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
        }

        while (!validateDate(newEntry.date)) {
            printf("Invalid date format. Enter a valid date (DD-MM-YYYY): ");
            scanf("%s", newEntry.date);
        }

        printf("Email: ");
        scanf("%s", newEntry.email);
        while (!validateEmail(newEntry.email)) {
            printf("Invalid email format. Enter a valid email: ");
            scanf("%s", newEntry.email);
        }

        printf("Phone Number: ");
        scanf("%s", newEntry.phoneNumber);
        while (!validatePhoneNumber(newEntry.phoneNumber)) {
            printf("Invalid phone number format. Enter a valid phone number: ");
            scanf("%s", newEntry.phoneNumber);
        }

        if (strlen(newEntry.name) == 0 || strlen(newEntry.lastName) == 0 || newEntry.weight <= 0 || strlen(newEntry.date) == 0 ||
            strlen(newEntry.email) == 0 || strlen(newEntry.phoneNumber) == 0) {
            printf("Error: All fields are required. Please fill in all the fields.\n");
            return;
        }

        fprintf(file, "%s,%s,%d,%s,%s,%s\n", newEntry.name, newEntry.lastName, newEntry.weight, newEntry.date, newEntry.email, newEntry.phoneNumber);
        printf("New entry added successfully!\n");

    } else if (option == 2) {  
        modifyEntry(file, initialFileName);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}


void retrieveInformation(FILE *file) {
    int choice;
    printf("How would you like to search for the data?\n");
    printf("1. Specify field and criteria\n");
    printf("2. Display pertinent information for retrieved entries\n");
    printf("3. Display all information\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            // Retrieve information based on specified field and criteria
            char field[50];
            char criteria[50];

            printf("Enter the field for retrieval (e.g., name, lastName, weight, date, email, phoneNumber): ");
            scanf("%s", field);
            printf("Enter the criteria for %s: ", field);
            scanf("%s", criteria);

            rewind(file);

            int found = 0;

            struct AddressBookEntry entry;
            while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
                if (strcmp(field, "name") == 0 && strcmp(entry.name, criteria) == 0) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    printf("-------------------------\n");
                } else if (strcmp(field, "lastName") == 0 && strcmp(entry.lastName, criteria) == 0) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    printf("-------------------------\n");
                } else if (strcmp(field, "weight") == 0 && entry.weight == atoi(criteria)) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                }else if (strcmp(field, "date") == 0 && strcmp(entry.date, criteria) == 0) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    printf("-------------------------\n");
                } else if (strcmp(field, "email") == 0 && strcmp(entry.email, criteria) == 0) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    printf("-------------------------\n");
                } else if (strcmp(field, "phoneNumber") == 0 && strcmp(entry.phoneNumber, criteria) == 0) {
                    found = 1;
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    printf("-------------------------\n");
                }
            }

            // Check if any matching entry is found
            if (!found) {
                printf("No matching entry found for the specified criteria.\n");
            }
            break;

        case 2:
            char field[50];
            char criteria[50];

            printf("Enter the field for retrieval (e.g., name, lastName, weight, date, email, phoneNumber): ");
            scanf("%s", field);
            printf("Enter the criteria for %s: ", field);
            scanf("%s", criteria);

            rewind(file);

            int found = 0;

            struct AddressBookEntry entry;
            while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
                if ((strcmp(field, "name") == 0 && strcmp(entry.name, criteria) == 0) ||
                    (strcmp(field, "lastName") == 0 && strcmp(entry.lastName, criteria) == 0) ||
                    (strcmp(field, "weight") == 0 && entry.weight == atoi(criteria)) ||
                    (strcmp(field, "date") == 0 && strcmp(entry.date, criteria) == 0) ||
                    (strcmp(field, "email") == 0 && strcmp(entry.email, criteria) == 0) ||
                    (strcmp(field, "phoneNumber") == 0 && strcmp(entry.phoneNumber, criteria) == 0)) {

                    found = 1;

                    printf("Entry found:\n");
                    printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                        entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                    
                    printf("Do you want to view comprehensive information for this entry? (yes/no): ");
                    char choice[4];
                    scanf("%s", choice);

                    if (strcmp(choice, "yes") == 0) {
                        // Display comprehensive information
                        printf("Comprehensive Information:\n");
                        printf("Name: %s\n", entry.name);
                        printf("Last Name: %s\n", entry.lastName);
                        printf("Weight: %d\n", entry.weight);
                        printf("Date: %s\n", entry.date);
                        printf("Email: %s\n", entry.email);
                        printf("Phone Number: %s\n", entry.phoneNumber);
                    }
                    printf("-------------------------\n");
                }
            }

            // Check if any matching entry is found
            if (!found) {
                printf("No matching entry found for the specified criteria.\n");
            }
            break;

        case 3:
            // Display all information
            rewind(file);
            while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", entry.name, entry.lastName, &entry.weight, entry.date, entry.email, entry.phoneNumber) != EOF) {
                printf("Name: %s\nLast Name: %s\nWeight: %d\nDate: %s\nEmail: %s\nPhone Number: %s\n", 
                    entry.name, entry.lastName, entry.weight, entry.date, entry.email, entry.phoneNumber);
                printf("-------------------------\n");
            }
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}