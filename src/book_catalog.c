// Copyright 2022 by Artem Ustsov
#include "book.h"

int create_catalog(BookCatalog** book_catalog_p, FILE* file) {
    if (!book_catalog_p) {
        return false;
    }
    *book_catalog_p = (BookCatalog *)malloc(sizeof(BookCatalog));

    BookCatalog *book_catalog = *book_catalog_p;
    if (!book_catalog) {
        return false;
    }

    book_catalog->books = NULL;
    book_catalog->size = 0;
    book_catalog->capacity = 0;
    
    size_t i = 0;
    char* string = NULL;
    int integer = 0;
    bool error = false;

    while(!feof(file) && !error) {
        if(book_catalog->size + 1 >= book_catalog->capacity) {
            size_t new_capacity = !book_catalog->capacity ? 1 : book_catalog->capacity * 2;
            Book *tmp = (Book *)realloc(book_catalog->books, new_capacity * sizeof(Book));
            if (!tmp) {
                error = true;
            } else {
                book_catalog->books = tmp;
                book_catalog->capacity = new_capacity;
            }
        }

        if(!error) {
            book_catalog->books[i].ISBN_code = NULL;
            book_catalog->books[i].name = NULL;
            book_catalog->books[i].publication_year = 0;
            book_catalog->books[i].num_of_stored = 0;
            book_catalog->books[i].is_tooked = false;
            book_catalog->books[i].num_of_taken = 0;
            book_catalog->books[i].num_of_persons_tooked = 0;
            book_catalog->books[i].persons = NULL;

            string = input_string(file);
            book_catalog->books[i].ISBN_code = string;
            
            string = input_string(file);
            book_catalog->books[i].name = string;   

            integer = input_int(file);
            book_catalog->books[i].publication_year = (size_t)integer;
            
            integer = input_int(file);
            book_catalog->books[i].num_of_stored = (size_t)integer;
        }
        if(!feof(file)) {
            ++i;
            ++book_catalog->size;
        }
    }
    free(string);
    if (error) {
        return false;
    }
    return true;
}

void delete_catalog(BookCatalog* book_catalog) {
    if(!book_catalog) {
        return;
    }
    for (size_t i = 0; i < book_catalog->size; ++i) {
        if (book_catalog->books[i].ISBN_code) {
            free(book_catalog->books[i].ISBN_code);
        }
        if (book_catalog->books[i].name) {
            free(book_catalog->books[i].name);
        }
        if(book_catalog->books[i].persons) {
            for (size_t j = 0; j < book_catalog->books[i].num_of_persons_tooked; ++j) {
                if (book_catalog->books[i].is_tooked) {
                    if (book_catalog->books[i].persons[j].surname) {
                        free(book_catalog->books[i].persons[j].surname);
                    }
                    if (book_catalog->books[i].persons[j].date_taken) {
                        free(book_catalog->books[i].persons[j].date_taken);
                    }
                }
            }
            free(book_catalog->books[i].persons);
        }
    }
    free(book_catalog->books);
    free(book_catalog);
}


void print_catalog(const BookCatalog* book_catalog, size_t catalog_size) {
    printf("BOOK CATALOG: \n");
    for (size_t i = 0; i < catalog_size; ++i) {
        print_book(&book_catalog->books[i], i+1);
    }
    printf("=================\n\n");
}


void get_info_of_taken_books(const BookCatalog *book_catalog) {
    if(!book_catalog) {
        return;
    }

    printf("Total taken books:\n");
    for (size_t i = 0; i < book_catalog->size; ++i) {
        if(book_catalog->books[i].is_tooked) {
            print_string(book_catalog->books[i].name);
            printf(":\t %ld copies\n", book_catalog->books[i].num_of_taken);
        }
    }
}
