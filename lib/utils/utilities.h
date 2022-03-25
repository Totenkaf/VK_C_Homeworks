// Copyright 2022 by Artem Ustsov

#ifndef LIB_UTILITIES_H_
#define LIB_UTILITIES_H_

#include <stdio.h>

#define BUFFER_SIZE 512
#define CHUNK_SIZE 64
#define SIZE_FACTOR 2

char *input_string(FILE *stream);
int input_number(FILE *stream);

#endif // LIB_UTILITIES_H_
