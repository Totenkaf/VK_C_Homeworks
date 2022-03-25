// Copyright 2022 by Artem Ustsov
#ifndef COUNT_R_PEAKS_STRESS_TEST_H
#define COUNT_R_PEAKS_STRESS_TEST_H

#include <stdio.h>
#include <time.h>

#define MS_IN_SEC 1e3
#define NS_IN_MS 1e6
#define MAX_NUMBER_OF_POSSIBLE_VALUES 100

enum exit_status {_EXIT_SUCCESS = 0, _EXIT_FAILURE};

typedef struct {
    char* test_type;
    size_t iterations;
    size_t sequence_size;
    double min;
    double max;
    double avg;
} time_stat;

double get_time();
void save_stat(time_stat stat, unsigned long int result, const char* filename);
int create_random_sequence_file(const char* file_name, size_t sequence_size, size_t R_window);

#endif //COUNT_R_PEAKS_STRESS_TEST_H
