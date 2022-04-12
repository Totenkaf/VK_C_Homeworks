// Copyright 2022 by Artem Ustsov

#include <stdlib.h>

#include "ECG.h"
#include "utilities.h"

// Allocates memory in heap to ECG sequence
bool create_ECG(ECG** ecg_p, FILE* stream) {
  if (!ecg_p) {
    return false;
  }

  *ecg_p = (ECG*)malloc(sizeof(ECG));
  ECG* ecg = *ecg_p;
  if (!ecg) {
    return false;
  }

  ecg->size = 0;
  ecg->signals_data = NULL;
  ecg->R_window = 0;
  int integer_input = 0;

  integer_input = input_number(stream);
  ecg->size = integer_input;

  ecg->signals_data = (int*)calloc(ecg->size, sizeof(int));
  if (!ecg->signals_data) {
    return false;
  }

  for (size_t i = 0; i < ecg->size; ++i) {
    integer_input = input_number(stream);
    ecg->signals_data[i] = integer_input;
  }

  integer_input = input_number(stream);
  ecg->R_window = integer_input;

  return true;
}

// Deletes allocated memory under ECG sequence
void delete_ecg(ECG* ecg) {
  if (!ecg) {
    return;
  }
  free(ecg->signals_data);
  free(ecg);
}
