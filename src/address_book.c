#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "validation.h"
#include "time.h"
#define MAX_LINE_SIZE 1024 

void modifyEntry(FILE *file) {
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
            int num;
            printf("Modify entry:\n");
            printf("Name: ");
            scanf("%s", entry.name);
            printf("Last Name: ");
            scanf("%s", entry.lastName);
            printf("Weight: ");
            scanf("%d", &entry.weight);
            printf("To Use current date Press 1: ");
            printf("To enter old date Press 2: ");
           scanf("%d", &num); // Fixed scanf statement to properly read num.

            if (num == 2) { // Corrected the else block syntax.
                scanf("%s", entry.date);
            } else { // Corrected the else block syntax.
                time_t currentTime;
                time(&currentTime);
                struct tm *localTime = localtime(&currentTime);
                int year = localTime->tm_year + 1900;
                int month = localTime->tm_mon + 1;
                int day = localTime->tm_mday;
                fprintf(tempFile, "date of the recording: %d, %d, %d\n", day, month, year); // Writing to tempFile instead of file.
            }
           
            printf("Email: ");
            scanf("%s", entry.email);
            while (!validateEmail(entry.email)) {
                printf("Invalid email format. Enter a valid email: ");
                scanf("%s", entry.email);
            }
            printf("Phone Number: ");
            scanf("%s", entry.phoneNumber);
            while (!validatePhoneNumber(entry.phoneNumber)) {
                printf("Invalid phone number format. Enter a valid phone number: ");
                scanf("%s", entry.phoneNumber);
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

    remove("database.csv");

    rename("temp.csv", "database.csv");

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
        printf("Last Name: ");
        scanf("%s", newEntry.lastName);
        printf("Weight: ");
        scanf("%d", &newEntry.weight);
       

        int num; // Declare num variable.
printf("To Use current date Press 1: ");
printf("To enter old date Press 2: ");
scanf("%d", &num); // Fixed scanf statement to properly read num.

if (num == 2) { // Corrected the else block syntax.
    scanf("%s", newEntry.date);
} else { // Corrected the else block syntax.
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    fprintf(file, "date of the recording: %d, %d, %d\n", day, month, year); // Writing to file instead of tempFile.
}
        while (!validateDate(newEntry.date)) {
            printf("Invalid date format. Enter a valid date (DDMMYYYY): ");
            scanf("%s", newEntry.date);
        };
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
        printf("Modify existing entry feature is under construction.\n");
        modifyEntry(file);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}


void retrieveInformation(FILE *file) { 
    
    rewind(file);
    printf("%s \n \n", "This are Your stats G");
  

    char line[MAX_LINE_SIZE];

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
}