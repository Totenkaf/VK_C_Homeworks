// Copyright 2022 by Artem Ustsov
#include "utilities.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Gets a chunk of data from stream and returns the correct string
char *input_string(FILE *stream) {
  size_t buffer_capacity = BUFFER_SIZE;
  char *buffer = (char *)malloc(sizeof(char) * buffer_capacity);
  if (!buffer) {
    return NULL;
  }

  char *chunk = (char *)malloc(sizeof(char) * CHUNK_SIZE);
  if (!chunk) {
    free(buffer);
    return NULL;
  }

  char *buffer_p = buffer;
  size_t buffer_real_size = 0;

  size_t chunksize = 1;
  chunk[0] = '\0';

  while (chunk[chunksize - 1] != '\n' && fgets(chunk, CHUNK_SIZE, stream)) {
    chunksize = strlen(chunk);
    if (buffer_real_size + chunksize >= buffer_capacity) {
      buffer_capacity *= SIZE_FACTOR;
      char *new_buffer_p =
          (char *)realloc(buffer, sizeof(char) * buffer_capacity);
      if (!new_buffer_p) {
        free(chunk);
        free(buffer);
        return NULL;
      }
      buffer = new_buffer_p;
      buffer_p = buffer + buffer_real_size;
    }
    buffer_real_size += chunksize;
    memcpy(buffer_p, chunk, chunksize);
    buffer_p += chunksize;
  }
  free(chunk);

  char *new_string =
      (char *)realloc(buffer, sizeof(char) * (buffer_real_size + 1));
  if (!new_string) {
    free(buffer);
    return 0;
  }
  if (!buffer_real_size) {
    new_string[buffer_real_size] = '\n';
  } else {
    new_string[buffer_real_size] = '\0';
  }
  return new_string;
}

// Converts input data from string format to numeric format
int input_number(FILE *stream) {
  char *string = input_string(stream);
  char *end = NULL;
  if (!string) {
    return 0;
  }
  int number = (int)strtol(string, &end, 0);
  if (string == end) {
    free(string);
    return 0;
  }
  free(string);
  return number;
}

// creates a random sequence ECG for program and writes into .txt file
bool create_random_sequence_file(const char *file_name, const size_t size, const size_t R_window) {
  if (size < 1 || R_window < 1) {
    return false;
  }

  FILE *sequence = fopen(file_name, "w");
  if (!sequence) {
    return false;
  }

  srandom(time(NULL));

  fprintf(sequence, "%ld\n", size);
  for (size_t i = 0; i < size; ++i) {
    int buf = (int)(random() % (LOWER_BOUND_OF_VALUES - TOP_BOUND_OF_VALUES + 1) + LOWER_BOUND_OF_VALUES);
    fprintf(sequence, "%d\n", buf);
  }
  fprintf(sequence, "%ld", R_window);
  fclose(sequence);
  return true;
}
