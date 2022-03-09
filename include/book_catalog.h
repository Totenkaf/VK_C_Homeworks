// Copyright 2022 by Artem Ustsov

typedef struct BookCatalog {
    size_t size;
    size_t capacity;
    Book* books;
} BookCatalog;


int create_catalog(BookCatalog** book_catalog_p, FILE* file);
void delete_catalog(BookCatalog* book_catalog);
void get_info_of_taken_books(const BookCatalog *book_catalog);
void print_catalog(const BookCatalog* book_catalog, size_t catalog_size);
