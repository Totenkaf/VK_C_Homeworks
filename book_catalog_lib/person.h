// Copyright 2022 by Artem Ustsov

#ifndef LIB_PERSON_H_
#define LIB_PERSON_H_


#include <stdio.h>
#include <stdlib.h>

typedef struct PersonTookedBook {
  char *surname;
  char *date_taken;
  size_t num_of_taken;
} PersonTookedBook;

void print_person(const PersonTookedBook *person, size_t num_of_persons);

#endif // LIB_PERSON_H_
