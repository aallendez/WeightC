#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdbool.h>

bool validateEmail(const char *email);
bool validatePhoneNumber(const char *phoneNumber);
bool validateDate(const char *date);
bool validateString(const char *str);

#endif /* VALIDATION_H */
