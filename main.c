// Copyright 2022 by Artem Ustsov

#include "lib.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum exit_status {_EXIT_SUCCESS = 0, _EXIT_FAILURE};

int main(int argc, char* argv[]) {
    int c = 0;
    int input_mode = 0;
    int opt_idx = 0;
    const char *filename = NULL;

    struct option options[] = { {"input_mode", required_argument, NULL, 'i'},
                                {NULL, 0, NULL, 0}
                              };
    while ((c = getopt_long(argc, argv, ":i:", options, &opt_idx)) != -1) { // NOLINT
      switch (c) {
        case 0:
          printf("long option %s", options[opt_idx].name);
          if (optarg) {
            printf(" with arg %s", optarg);
          }
          printf("\n");
          break;

        case 1:
          printf("non-option argument %s\n", optarg);
          break;

        case 'i':
          input_mode = atoi(optarg); // NOLINT
          break;

        case '?':
          printf("Unknown option %c\n", optopt);
          break;

        default:
          break;
      }
  }

  FILE *file = NULL;
  if (input_mode == 1) {
    filename = argv[optind];
    file = fopen(filename, "r");
  } else {
    file = stdin;
  }
  if (!file) {
    return _EXIT_FAILURE;
  }

  ECG *ecg = NULL;
  bool success = create_ECG(&ecg, file);
  if (success) {
      size_t result = 0;
      size_t R_window = 0;
      printf("Enter the R-window: ");
      if ((scanf("%lu", &R_window)) != -1) {
          result = count_R_peaks(ecg, R_window);
          printf("Total count of R-extremums: %ld. {R-window = %ld}\n", result, R_window);
      }
  }
  fclose(file);
  delete_ecg(ecg);
  return _EXIT_SUCCESS;
}
