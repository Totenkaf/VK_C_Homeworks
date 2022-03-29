// Copyright 2022 by Artem Ustsov

#ifndef STRESS_TEST_STRESS_TEST_H_
#define STRESS_TEST_STRESS_TEST_H_

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define MS_IN_SEC 1e3
#define NS_IN_MS 1e6
#define MAX_NUMBER_OF_POSSIBLE_VALUES 100

enum exit_status { _EXIT_SUCCESS = 0, _EXIT_FAILURE };

typedef struct {
  char* test_type;
  size_t iterations;
  size_t sequence_size;
  double min;
  double max;
  double avg;
} time_stat;

double get_time();
void save_stat(time_stat stat, uint64_t result, const char* filename);
int create_random_sequence_file(const char* file_name, size_t sequence_size,
                                size_t R_window);

#endif  // STRESS_TEST_STRESS_TEST_H_
