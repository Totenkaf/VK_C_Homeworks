// Copyright 2022 by Artem Ustsov

#ifndef STRESS_TEST_STRESS_TEST_H_
#define STRESS_TEST_STRESS_TEST_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define DEFAULT_NUMBER_OF_ITERATIONS 1000
#define MS_IN_SEC 1e3
#define NS_IN_MS 1e6
#define MAX_NUMBER_OF_POSSIBLE_VALUES 100

typedef struct {
  char* test_type;
  size_t iterations;
  size_t sequence_size;
  double min;
  double max;
  double avg;
} time_stat;

double get_time();
void save_stat(time_stat stat, size_t result, const char* filename);
bool write_sequence_output_file(const int* sequence, size_t size,
                                size_t R_window, FILE* stream);

#endif  // STRESS_TEST_STRESS_TEST_H_
