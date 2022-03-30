// Copyright 2021 Artem Ustsov
#include <stdlib.h>
#include <string.h>

#include "../lib/lib.h"
#include "../utils/utilities.h"
#include "stress_test.h"

int main(int argc, char* argv[]) {
  const size_t number_of_iterations = DEFAULT_NUMBER_OF_ITERATIONS;
  FILE* stream = NULL;
  size_t user_cores = 0;
  stream = get_stream(&user_cores, argc, argv);
  if (!stream) {
    return _EXIT_FAILURE;
  }

  ECG* ecg = NULL;
  bool success = create_ECG(&ecg, stream);

  if (success) {
    double time_avg = 0;
    double time_min = RAND_MAX;
    double time_max = 0;
    size_t result = 0;

    for (size_t i = 0; i < number_of_iterations; ++i) {
      double time = get_time();
      result = count_R_peaks(ecg, user_cores);
      time = get_time() - time;

      if (time < time_min) {
        time_min = time;
      }
      if (time > time_max) {
        time_max = time;
      }
      time_avg += time;
    }

    time_avg = time_avg / number_of_iterations;
    time_stat stat = {.iterations = number_of_iterations,
                      .min = time_min,
                      .max = time_max,
                      .avg = time_avg,
                      .sequence_size = ecg->size};

    save_stat(stat, result, "statistic.txt");
    const char* output_file = "result.txt";
    FILE* outfd = fopen(output_file, "w+");
    if (!outfd) {
      delete_ecg(ecg);
      return _EXIT_FAILURE;
    }

    if (!write_sequence_output_file(ecg->signals_data, ecg->size, ecg->R_window,
                                    outfd)) {
      delete_ecg(ecg);
      fclose(outfd);
    }
    fclose(outfd);
  }
  delete_ecg(ecg);
  return _EXIT_SUCCESS;
}
