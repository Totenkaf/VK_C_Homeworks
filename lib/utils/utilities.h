// Copyright 2022 by Artem Ustsov

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

#define BUFFER_SIZE 512
#define CHUNK_SIZE 64
#define SIZE_FACTOR 2

char *input_string(FILE *stream);
int input_number(FILE *stream);

#endif //UTILITIES_H
