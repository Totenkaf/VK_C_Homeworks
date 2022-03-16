// Copyright 2022 by Artem Ustsov
#include "person.h"
#include "utilities.h"

void print_person(const PersonTookedBook *person, size_t num_of_persons) {
  printf("Persons: \n");
  for (size_t i = 0; i < num_of_persons; ++i) {
    print_string(person[i].surname);
    printf(" (");
    print_string(person[i].date_taken);
    printf(") : ");
    printf("%ld", person[i].num_of_taken);
    printf(" copies");
    printf("\n");
  }
}
