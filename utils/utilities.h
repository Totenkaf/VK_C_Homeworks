// Copyright 2022 by Artem Ustsov

#ifndef UTILS_UTILITIES_H_
#define UTILS_UTILITIES_H_

#include <stdbool.h>
#include <stdio.h>

#define BASIS 10
#define BUFFER_SIZE 512
#define CHUNK_SIZE 64
#define LOWER_BOUND_OF_VALUES -1000
#define SIZE_FACTOR 2
#define TOP_BOUND_OF_VALUES 1000

enum exit_status { _EXIT_SUCCESS = 0, _EXIT_FAILURE };

bool create_random_sequence_file(const char *file_name, size_t size,
                                 size_t R_window);
char *input_string(FILE *stream);
int input_number(FILE *stream);

#endif  // UTILS_UTILITIES_H_
