// Copyright 2022 by Artem Ustsov

#include "lib.h"
#include "utils/utilities.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum exit_status {_EXIT_SUCCESS = 0, _EXIT_FAILURE};

static FILE* get_stream(long int* user_cores, FILE* stream, int argc, char* argv[]) {
    long int input_mode = 0;
    int opt_idx = 0;
    int c = 0;
    struct option options[] = { {"input_mode", required_argument, NULL, 'i'},
                                {"cores", required_argument, NULL, 'j'},
                                {NULL, 0, NULL, 0}
                              };
    while ((c = getopt_long(argc, argv, ":j:i:", options, &opt_idx)) != -1) { // NOLINT
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
          input_mode = strtol(optarg, NULL, BASIS); // NOLINT
          break;

        case 'j':
          *user_cores = strtol(optarg, NULL, BASIS); // NOLINT
          break;

        case '?':
          printf("Unknown option %c\n", optopt);
          break;

        default:
          break;
      }
  }

  if (input_mode == 1) {
    const char *filename = NULL;
    filename = argv[optind++];
    size_t size = (size_t)strtol(argv[optind++], NULL, BASIS);
    size_t R_window = (size_t)strtol(argv[optind], NULL, BASIS);

    bool success = create_random_sequence_file(filename, size, R_window);
    if (!success) {
      return NULL;
    }
    stream = fopen(filename, "r");
  } else {
    stream = stdin;
  }
  return stream;
}

int main(int argc, char* argv[]) {
  FILE *stream = NULL;
  size_t user_cores = 0;
  stream = get_stream(&user_cores, stream, argc, argv);
  if(!stream) {
    return _EXIT_FAILURE;
  }

  ECG *ecg = NULL;
  bool success = create_ECG(&ecg, stream);
  if (success) {
      size_t result = 0;
      result = count_R_peaks(ecg, user_cores);
      printf("Total count of R-extremums: %ld. {R-window = %ld}\n", result, ecg->R_window);
  }
  fclose(stream);
  delete_ecg(ecg);
  return _EXIT_SUCCESS;
}
