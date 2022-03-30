// Copyright 2022 by Artem Ustsov


#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "utils/utilities.h"


int main(int argc, char* argv[]) {
  FILE* stream = NULL;
  size_t user_cores = 0;
  stream = get_stream(&user_cores, argc, argv);
  if (!stream) {
    return _EXIT_FAILURE;
  }

  ECG* ecg = NULL;
  bool success = create_ECG(&ecg, stream);
  if (success) {
    size_t result = 0;
    result = count_R_peaks(ecg, user_cores);
    printf("Total count of R-extremums: %ld. {R-window = %ld}\n", result,
           ecg->R_window);
  }
  fclose(stream);
  delete_ecg(ecg);
  return _EXIT_SUCCESS;
}
