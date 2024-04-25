#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char initialFileName[100];

struct AddressBookEntry {
    char name[50];
    char lastName[50];
    int weight;
    char date[12];
    char email[320];
    char phoneNumber[20];
};

void saveNewEntry(FILE *file);
void retrieveInformation(FILE *file);
void modifyEntry(FILE *file, const char *fileName);

#endif /* ADDRESS_BOOK_H */
