// Copyright 2022 by Artem Ustsov

#ifndef LIB_UTILITIES_H_
#define LIB_UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>

char input_char(FILE *file);
int input_int(FILE *file);
char *input_string(FILE *file);
void print_string(const char *symbol);

#endif // LIB_UTILITIES_H_
