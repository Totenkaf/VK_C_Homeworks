// Copyright 2022 by Artem Ustsov
#include "book_catalog.h"


int main(int argc, char** argv) {
    
    if(argc < 3) {
        printf("Too few input arguments");
        return EXIT_FAILURE;
    }
    
    const char* input_mode = argv[1];
    FILE* file_1;
    if (strcmp(input_mode, "std_input") == 0)
    {
        file_1 = stdin;
    } else if (strcmp(input_mode, "file_input") == 0) {
        const char* filename_1 = argv[2];
        file_1 = fopen(filename_1, "r");
    } else {
        return _EXIT_FAILURE; 
    }
    
    if (!file_1) {
        return _EXIT_FAILURE;
    }

    BookCatalog *new_catalog = NULL;
    bool success = create_catalog(&new_catalog, file_1);
    if (success) {
        print_catalog(new_catalog, new_catalog->size);
    }
    fclose(file_1);

    FILE* file_2;
    const char* filename_2 = argv[3]; 
    file_2 = fopen(filename_2, "r");
    if (!file_2) {
        return _EXIT_FAILURE;
    }

    success = take_the_book(&new_catalog, file_2);
    if (success) {
        print_catalog(new_catalog, new_catalog->size);
    }

    get_info_of_taken_books(new_catalog);
    delete_catalog(new_catalog);
    fclose(file_2);
    return _EXIT_SUCCESS;
}
