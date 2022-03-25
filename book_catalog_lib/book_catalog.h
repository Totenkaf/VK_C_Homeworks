// Copyright 2022 by Artem Ustsov

#ifndef LIB_BOOK_CATALOG_H_
#define LIB_BOOK_CATALOG_H_

#include "book.h"

typedef struct BookCatalog {
  size_t size;
  size_t capacity;
  Book *books;
} BookCatalog;

int create_catalog(BookCatalog **book_catalog_p, FILE *file);
void delete_catalog(BookCatalog *book_catalog);
void get_info_of_taken_books(const BookCatalog *book_catalog);
void print_catalog(const BookCatalog *book_catalog, size_t catalog_size);
bool take_the_book(BookCatalog **book_catalog_p, FILE *file);

#endif // LIB_BOOK_CATALOG_H_
