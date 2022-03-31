// Copyright 2022 by Artem Ustsov

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lib.h"

// Finds local extremums in ECG sequence
static void findLocalMax(const int* signals_data, const size_t size,
                         size_t* shared_memory, const size_t size_column,
                         const size_t process_number,
                         const size_t count_processes) {
  size_t part_begin =
      process_number == 0 ? 1 : (size / count_processes) * process_number;
  size_t part_end = process_number == count_processes - 1
                        ? size - 1
                        : (size / count_processes) * (process_number + 1);

  // проверка на экстремум в первом элементе
  if (process_number == 0 && abs(signals_data[0]) > abs(signals_data[1])) {
    ++(*(shared_memory + 0 * size_column + 0));
    *(shared_memory + 0 * size_column + 1) = 1;
  }

  // проверка на локальный экстремум
  for (size_t i = part_begin; i < part_end; ++i) {
    if (abs(signals_data[i]) > abs(signals_data[i - 1]) &&
        abs(signals_data[i]) > abs(signals_data[i + 1])) {
      ++(*(shared_memory + (process_number)*size_column + 0));
      size_t size_local_max =
          *(shared_memory + (process_number)*size_column + 0);
      *(shared_memory + (process_number)*size_column + size_local_max) = i;
    }
  }

  // проверка на экстремум в последнем элементе
  if (process_number == count_processes - 1 &&
      abs(signals_data[size - 1]) > abs(signals_data[size - 2])) {
    ++(*(shared_memory + (count_processes - 1) * size_column + 0));
    size_t size_local_max =
        *(shared_memory + (count_processes - 1) * size_column + 0);
    *(shared_memory + (count_processes - 1) * size_column + size_local_max) =
        size - 1;
  }
}

// Counts local extremums
static size_t countLocalMax(const size_t* shared_memory,
                            const size_t size_column,
                            const size_t count_processes,
                            const size_t R_window) {
  size_t count = 0;
  size_t last_max = -R_window - 1;  // изначально бесконечность для недостижения

  for (size_t i = 0; i < count_processes; ++i) {
    size_t size_local_max = *(shared_memory + i * size_column + 0);
    for (size_t j = 1; j < size_local_max + 1; ++j) {
      if (*(shared_memory + i * size_column + j) >= (last_max + R_window + 1)) {
        last_max = *(shared_memory + i * size_column + j);
        ++count;
      }
    }
  }
  return count;
}

size_t count_R_peaks(const ECG* ecg, const size_t user_cores) {
  if (ecg == NULL || ecg->signals_data == NULL || ecg->size == 0 ||
      user_cores == 0) {
    return 0;
  }

  size_t sys_free_cores = (size_t)sysconf(_SC_NPROCESSORS_ONLN);
  size_t count_processes =
      user_cores > sys_free_cores
          ? sys_free_cores
          : user_cores;  // количество доступных процессоров, возможность
                         // задания пользователем
  pid_t pids[count_processes];

  // каждый новый процесс будет интерпретироваться как столбец матрицы
  size_t size_column = ecg->size / 2 + 1;
  size_t* shared_memory =
      (size_t*)mmap(NULL, size_column * count_processes * sizeof(size_t),
                    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,
                    0);  // будем делиться памятью между процессами
  printf("Active cores: %ld\n", count_processes);
  if (shared_memory == MAP_FAILED) {
    return 0;
  }

  for (size_t i = 0; i < count_processes; ++i) {
    pids[i] = fork();
    if (pids[i] == 0) {
      // каждый процесс будет искать свой локальный экстремум
      findLocalMax(ecg->signals_data, ecg->size, shared_memory, size_column, i,
                   count_processes);
      exit(EXIT_SUCCESS);  // NOLINT
    }
  }

  int status = 0;
  for (size_t i = 0; i < count_processes; ++i) {
    if (waitpid(pids[i], &status, 0) != pids[i]) {
      return 0;
    }
  }

  // после завершения дочерних, родительский подсчитает количество локальных
  // экстремум
  size_t count =
      countLocalMax(shared_memory, size_column, count_processes, ecg->R_window);
  if (munmap(shared_memory, size_column * count_processes * sizeof(size_t)) !=
      0) {
    return 0;
  }
  return count;
}
