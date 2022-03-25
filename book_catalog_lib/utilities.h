// Copyright 2022 by Artem Ustsov

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>

char input_char(FILE *file);
int input_int(FILE *file);
char *input_string(FILE *file);
void print_string(const char *symbol);

#endif // UTILITIES_H
