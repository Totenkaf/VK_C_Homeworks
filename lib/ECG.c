// Copyright 2022 by Artem Ustsov
#include "ECG.h"
#include "utils/utilities.h"
#include <stdlib.h>

/*Allocates memory in heap to ECG sequence*/
bool create_ECG(ECG** ecg_p, FILE* stream) {
    if (!ecg_p) {
        return false;
    }

    *ecg_p = (ECG *)malloc(sizeof(ECG));
    ECG *ecg = *ecg_p;
    if (!ecg) {
        return false;
    }

    int integer_input = input_number(stream);
    ecg->size = integer_input;

    ecg->signals_data = NULL;
    ecg->signals_data = (int*) calloc(ecg->size, sizeof(int));
    if (!ecg->signals_data) {
        return false;
    }
    
    for (size_t i = 0; i < ecg->size; ++i) {
        integer_input = input_number(stream);
        ecg->signals_data[i] = integer_input;
    }
    return true;
}

/* Deletes allocated memory under ECG sequence */
void delete_ecg(ECG* ecg) {
    if (!ecg) {
        return;
    }
    free(ecg->signals_data);
    free(ecg);
}
