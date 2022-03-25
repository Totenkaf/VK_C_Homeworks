// Copyright 2022 by Artem Ustsov

#ifndef LIB_H
#define LIB_H

#include "ECG.h"

size_t count_R_peaks(const ECG* ecg, size_t R_window);

#endif //LIB_H
