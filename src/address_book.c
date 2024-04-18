#include <stdio.h>
#include "address_book.h"
#define MAX_LINE_SIZE 1024 // Change the value as per your requirement
void saveNewEntry(FILE *file) {
    struct AddressBookEntry newEntry;

    printf("\nEnter details for the new entry:\n");
    printf("Name: ");
    scanf("%s", newEntry.name);
    printf("Last Name: ");
    scanf("%s", newEntry.lastName);
     printf("weight: ");
    scanf("%s", newEntry.weight);
    printf("date: ");
    scanf("%s", newEntry.date);


    fprintf(file, "%s,%s,%s, %s \n", newEntry.name, newEntry.lastName, newEntry.weight, newEntry.date);

    printf("New entry saved successfully!\n");
}

void retrieveInformation(FILE *file) { 
    
    // Rewind the file pointer to the beginning of the file
    rewind(file);
    printf("%s \n \n", "This are Your stats G");
  

    char line[MAX_LINE_SIZE];

    // Read and process each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Print each line to the console
        printf("%s", line);
    }
}