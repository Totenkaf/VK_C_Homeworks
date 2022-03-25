// Copyright 2022 by Artem Ustsov

#ifndef BOOK_H
#define BOOK_H

#include "person.h"
#include <stdbool.h>

typedef struct Book {
  bool is_tooked;
  char *ISBN_code;
  char *name;
  size_t publication_year;
  size_t num_of_stored;
  size_t num_of_persons_tooked;
  size_t num_of_taken;
  PersonTookedBook *persons;
} Book;

void print_book(const Book *book, size_t num);

#endif // BOOK_H
