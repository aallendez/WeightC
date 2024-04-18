#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <stdio.h>

struct AddressBookEntry {
    char name[50];
    char lastName[50];
    char weight[100];
    char date[10];
};

void saveNewEntry(FILE *file);
void retrieveInformation(FILE *file);

#endif /* ADDRESS_BOOK_H */
