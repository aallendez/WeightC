#include <stdio.h>
#include "address_book.h"
#include "time.h"
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

  time_t currentTime;
    time(&currentTime);

    // Convert the time to a local time struct
    struct tm *localTime = localtime(&currentTime);

    // Extract date components
    int year = localTime->tm_year + 1900; // Years since 1900
    int month = localTime->tm_mon + 1;    // Months since January (0-11)
    int day = localTime->tm_mday;         // Day of the month (1-31)



   fprintf(file, "first name of the person: %s \n", newEntry.name);
    fprintf(file, "Last name of the person: %s \n", newEntry.lastName);
     fprintf(file, "weight of the person: %s\n ", newEntry.weight);
      fprintf(file, "date of the recording: %d, %d, %d\n", day, month, year );
     
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