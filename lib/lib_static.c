// Copyright 2022 by Artem Ustsov
#include "lib.h"
#include <stdlib.h>

/*Count R extremums and ECG sequence */
size_t count_R_peaks(const ECG* ecg, const size_t R_window) {
  if (ecg == NULL || ecg->signals_data == NULL || ecg->size == 0) {
    return 0;
  }

  bool end_status = false;
  size_t count = 0;
  size_t i = 1;
  
  if (abs(ecg->signals_data[0]) > abs(ecg->signals_data[1])) { /* проверка на экстремум в первом элементе */
    printf("%d: %d\n", 0, ecg->signals_data[0]);
    ++count;
    i = R_window + 1;
  }

  while (!end_status && i < ecg->size) {
    if (i == ecg->size - 1 && abs(ecg->signals_data[i]) > abs(ecg->signals_data[i-1])) { /* проверка на экстремум в последнем элементе */
        printf("%ld: %d\n", i, ecg->signals_data[i]);
        ++count;
        end_status = true;
    }
    if(!end_status) {
        if (abs(ecg->signals_data[i]) > abs(ecg->signals_data[i-1]) && abs(ecg->signals_data[i]) > abs(ecg->signals_data[i+1])) { /* проверка локального экстремума */
            printf("%ld: %d\n", i, ecg->signals_data[i]);
            ++count;
            i += R_window + 1;
        }
        else {
            ++i;
        }
    }
  }
  return count;
}