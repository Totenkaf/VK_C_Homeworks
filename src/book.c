// Copyright 2022 by Artem Ustsov
#include "person.h"

bool take_the_book(BookCatalog** book_catalog_p, FILE* file) {
    if (!book_catalog_p) {
        return false;
    }

    BookCatalog *book_catalog = *book_catalog_p;
    if (!book_catalog) {
        return false;
    }

    bool error = false;
    size_t book_num = 0;
    char* string = NULL;
    int integer = 0;
    while(!feof(file) && !error) {
        printf("Enter number of the taking book: ");
        book_num = (size_t)input_int(file) - 1;
        printf("%ld\n", book_num + 1);
        if(book_num > book_catalog->size) {
            error = true;
        } 
        else {
            printf("Enter the number of taking persons: ");
            int num_of_persons = input_int(file);
            printf("%d\n", num_of_persons);
            book_catalog->books[book_num].num_of_persons_tooked = (size_t)num_of_persons;
            book_catalog->books[book_num].is_tooked = true;
            PersonTookedBook*  persons_p = (PersonTookedBook *)malloc(num_of_persons * sizeof(PersonTookedBook));
            if(!persons_p) {
                error = true;
            }
            if (!error) {
                book_catalog->books[book_num].persons = persons_p;
                for (size_t i = 0; i < num_of_persons; ++i) {
                    printf("Enter surname: ");
                    string = input_string(file);
                    print_string(string);
                    printf("\n");
                    book_catalog->books[book_num].persons[i].surname = string;

                    printf("Enter date taking like dd/mm/yyyy: ");
                    string = input_string(file);
                    print_string(string);
                    printf("\n");
                    book_catalog->books[book_num].persons[i].date_taken = string;
                    
                    printf("Enter num of taking copies: ");
                    integer = input_int(file);
                    printf("%d\n", integer);
                    book_catalog->books[book_num].persons[i].num_of_taken = (size_t)integer;
                    book_catalog->books[book_num].num_of_taken += book_catalog->books[book_num].persons[i].num_of_taken;
                    printf("\n");
                }
                
            }
        }
    }
    if(error) {
        return false;
    }
    return true;
}

void print_book(const Book* book, size_t num) {
    printf("\n");
    printf("%s %ld\n", "Book", num);
    printf("ISBN: ");
    print_string(book->ISBN_code);
    printf("\n");
    printf("Name: ");
    print_string(book->name);
    printf("\n");
    printf("Published in: ");
    printf("%ld\n", book->publication_year);
    printf("Stored copies: ");
    printf("%ld\n", book->num_of_stored);

    if(!book->is_tooked) {
        printf("--------\n");
        printf("The book is not taken\n");
    } else {
        printf("--------\n");
        printf("The book was taken by:\n");
        print_person(book->persons, book->num_of_persons_tooked);
    }
}
