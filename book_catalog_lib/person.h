// Copyright 2022 by Artem Ustsov
#include "utils.h"

typedef struct PersonTookedBook {
  char *surname;
  char *date_taken;
  size_t num_of_taken;
} PersonTookedBook;

void print_person(const PersonTookedBook *person, size_t num_of_persons);
