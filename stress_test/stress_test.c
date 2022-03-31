// Copyright 2022 by Artem Ustsov

#include "stress_test.h"

#include "../lib/ECG.h"

/* Get the systme time to measure*/
double get_time() {
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  return (double)time.tv_sec * MS_IN_SEC + time.tv_nsec / NS_IN_MS;
}

/*Logging the time stats into stdout*/
void save_stat(time_stat stat, const size_t result, const char* filename) {
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
  fprintf(file, "\tNUMBER OF PROCESSES: %zu\n", stat.num_of_cores);
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

bool write_sequence_output_file(const int* sequence, const size_t size,
                                const size_t R_window, FILE* stream) {
  if (!stream || !sequence) {
    return false;
  }
  fprintf(stream, "%ld\n", size);
  for (size_t i = 0; i < size; ++i) {
    fprintf(stream, "%d\n", sequence[i]);
  }
  fprintf(stream, "%ld", R_window);
  return true;
}
