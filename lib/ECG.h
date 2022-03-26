// Copyright 2022 by Artem Ustsov

#ifndef LIB_ECG_H_
#define LIB_ECG_H_

#include "stdbool.h"
#include "stdio.h"

typedef struct ECG {
    int* signals_data;
    size_t size;
    size_t R_window;
} ECG;

bool create_ECG(ECG** ecg_p, FILE* stream);
void delete_ecg(ECG* ecg);

#endif //LIB_ECG_H_
