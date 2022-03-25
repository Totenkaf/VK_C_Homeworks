// Copyright 2022 by Artem Ustsov

#ifndef ECG_H
#define ECG_H

#include "stdbool.h"
#include "stdio.h"

typedef struct ECG {
    int* signals_data;
    size_t size;
} ECG;

bool create_ECG(ECG** ecg_p, FILE* stream);
void delete_ecg(ECG* ecg);

#endif //ECG_H
