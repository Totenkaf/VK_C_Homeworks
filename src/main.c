// Copyright 2022 by Artem Ustsov
#include "book_catalog.h"
#include <getopt.h>
#include <string.h>
#include <unistd.h>

enum exit_result { _EXIT_SUCCESS = 0, _EXIT_FAILURE };

int main(int argc, char *argv[]) {
  int c = 0;
  int print_mode = 0;
  int input_mode = 0;
  int opt_idx = 0;
  const char *filename[2] = {NULL, NULL};

  struct option options[] = {{"print_mode", required_argument, NULL, 'p'},
                             {"input_mode", required_argument, NULL, 'i'},
                             {NULL, 0, NULL, 0}};

  while ((c = getopt_long(argc, argv, ":p:i:", options, &opt_idx)) !=
         -1) { // NOLINT
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

    case 'p':
      print_mode = atoi(optarg); // NOLINT
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

  printf("print_mode=%s, input_mode=%s\n",
         (print_mode == 0) ? "no print" : "print",
         (input_mode == 0) ? "stdin" : "file_input");
  if (input_mode == 1) {
    size_t i = 0;
    while (optind < argc) {
      filename[i++] = argv[optind];
      ++optind;
    }
  }

  FILE *file_1 = NULL;
  if (input_mode == 1) {
    file_1 = fopen(filename[0], "r");
  } else {
    file_1 = stdin;
  }
  if (!file_1) {
    return _EXIT_FAILURE;
  }

  BookCatalog *new_catalog = NULL;
  bool success = create_catalog(&new_catalog, file_1);
  if (success) {
    if (print_mode == 1) {
      print_catalog(new_catalog, new_catalog->size);
    }
  }
  fclose(file_1);

  FILE *file_2 = NULL;
  if (input_mode == 1) {
    file_2 = fopen(filename[1], "r");
  } else {
    file_2 = stdin;
  }

  if (!file_2) {
    return _EXIT_FAILURE;
  }

  success = take_the_book(&new_catalog, file_2);
  if (success) {
    if (print_mode == 1) {
      print_catalog(new_catalog, new_catalog->size);
    }
  }
  fclose(file_2);

  get_info_of_taken_books(new_catalog);
  delete_catalog(new_catalog);
  return _EXIT_SUCCESS;
}
