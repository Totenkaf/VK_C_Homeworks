// Copyright 2022 by Artem Ustsov

#include "stress_test.h"

#include "ECG.h"

/* Get the systme time to measure*/
double get_time() {
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);

  return (double)time.tv_sec * MS_IN_SEC + time.tv_nsec / NS_IN_MS;
}

/*Logging the time stats into stdout*/
void save_stat(time_stat stat, uint64_t result, const char* filename) {
  FILE* file = fopen(filename, "a");
  if (!file) {
    return;
  }

  fprintf(
      file,
      "=================================================================\n");
  fprintf(file, "\tTEST TYPE: %s\n", stat.test_type);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tNUMBER OF ITERATIONS: %zu\n", stat.iterations);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tSEQUENCE SIZE: %zu\n", stat.sequence_size);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tDNUM OF R-PEAKS: %zu\n", result);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tMIN TIME: %lf ms\n", stat.min);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tMAX TIME: %lf ms\n", stat.max);
  fprintf(
      file,
      "-----------------------------------------------------------------\n");
  fprintf(file, "\tAVG TIME: %lf ms\n", stat.avg);
  fprintf(
      file,
      "=================================================================\n\n");

  fclose(file);
}

static size_t calculate_matrix_size(const size_t size) {
  return (size * (size + 1)) >> (size_t)1;
}

int create_random_sequece_file(const char* file_name,
                               const size_t sequence_size,
                               const size_t R_window) {
  FILE* sequence = fopen(file_name, "w");
  if (!sequence) {
    return _EXIT_FAILURE;
  }
  srand(time(NULL)); /* random seed initialisation */

  fprintf(sequence, "%c\n", sequence_size);
  for (size_t i = 0; i < sequence_size; ++i) {
    char buf = (char)(random() % 100 + '0'); /* change to constant value */
    fprintf(sequence, "%c\n", buf);
  }
  fprintf(sequence, "%c\n", R_window);
  fclose(sequence);
  return _EXIT_SUCCESS;
}
