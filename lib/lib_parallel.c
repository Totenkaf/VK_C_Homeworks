// Copyright 2022 by Artem Ustsov

#include "lib.h"
#include <stdlib.h>

// Count R extremums and ECG sequence
size_t count_R_peaks(const ECG* ecg) {
  if (ecg == NULL || ecg->signals_data == NULL || ecg->size == 0) {
    return 0;
  }