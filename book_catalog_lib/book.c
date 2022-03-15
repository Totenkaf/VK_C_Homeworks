// Copyright 2022 by Artem Ustsov
#include "book.h"

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
