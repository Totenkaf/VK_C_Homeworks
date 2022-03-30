// Copyright 2021 Artem Ustsov
#include "matrix.h"
#include "stress_test_utils.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  size_t number_of_iterations = DEFAULT_NUMBER_OF_ITERATIONS;
  if (argc < 5) {
    return EXIT_FAILURE;
  }

  int cols = (int)strtol(argv[1], NULL, BASIS);
  int rows = (int)strtol(argv[2], NULL, BASIS);

  if (cols < 1 || rows < 1) {
    return EXIT_FAILURE;
  }

  const char *filename = argv[3];
  if (!filename) {
    return EXIT_FAILURE;
  }

  int *matrix = (int *)calloc(rows * cols, sizeof(int));
  if (!matrix) {
    return EXIT_FAILURE;
  }

  FILE *fd = fopen(filename, "r");
  if (!fd) {
    free(matrix);
    return EXIT_FAILURE;
  }

  if (!create_matrix(matrix, &cols, &rows, fd)) {
    free(matrix);
    return EXIT_FAILURE;
  }
  fclose(fd);

  double time_avg = 0;
  double time_min = RAND_MAX;
  double time_max = 0;
  bool errflag = false;

  for (size_t i = 0; i < number_of_iterations; ++i) {
    double time = get_time();
    if (!serial_side_matrix_reflection(matrix, cols, rows)) {
      errflag = true;
      break;
    }
    time = get_time() - time;

    if (time < time_min) {
      time_min = time;
    }
    if (time > time_max) {
      time_max = time;
    }
    time_avg += time;
  }
  if (errflag) {
    free(matrix);
    return EXIT_FAILURE;
  }
  time_avg = time_avg / number_of_iterations;
  time_stat stat = {.iterations = number_of_iterations,
                    .min = time_min,
                    .max = time_max,
                    .avg = time_avg,
                    .matrix_rows = rows,
                    .matrix_cols = cols};
  save_stat(stat, "statistic.txt");

  const char *output_file = argv[4];
  if (!output_file) {
    return EXIT_FAILURE;
  }
  if (strcmp(output_file, "write_off") != 0) {
    FILE *outfd = fopen(output_file, "w+");
    if (!outfd) {
      free(matrix);
      return EXIT_FAILURE;
    }
    if (!write_matrix_output_file(matrix, cols, rows, outfd)) {
      free(matrix);
      fclose(outfd);
    }
    fclose(outfd);
  }

  free(matrix);
  return EXIT_SUCCESS;
}