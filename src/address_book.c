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


   fprintf(file, "first name of the person: %s \n", newEntry.name);
    fprintf(file, "Last name of the person: %s \n", newEntry.lastName);
     fprintf(file, "weight of the person: %s\n ", newEntry.weight);
      fprintf(file, "date of the recording: %s \n", newEntry.date);
     
    printf("New entry saved successfully!\n");
}

void retrieveInformation(FILE *file) { 
    rewind(file);
  fseek(file, 0, SEEK_END); // Move file pointer to the end
    if (ftell(file) == 0) { // Check if file pointer is at the beginning
        printf("The file does not contain any information yet.\n");        // This code is from chatgpt please if you can, change it!!!
        return;
    }
    printf("%s \n \n", "This are Your stats G");
  

    char line[MAX_LINE_SIZE];

    // Read and process each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Print each line to the console
        printf("%s", line);
    }
}