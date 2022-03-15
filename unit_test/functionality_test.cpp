#include <cstring>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
    #include "book_catalog.h"
    #include "utils.h"
}

TEST(BAD_INPUT, null_ptr_creation) {
    bool success = create_catalog(nullptr, stdin);
    EXPECT_FALSE(success);
}

TEST(BAD_INPUT, null_ptr_take_the_book) {
    bool success = take_the_book(nullptr, stdin);
    EXPECT_FALSE(success);
}

TEST(CORRECT_INPUT, create_catalog_function) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success = create_catalog(&new_catalog, stream);
    EXPECT_TRUE(success);
    delete_catalog(new_catalog);
    fclose(stream);
}

TEST(CORRECT_INPUT, take_the_book_function) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "1\n2\nUstsov\n12/12/2022\n2\nTimoshenko\n05/11/2021\n2\n3\n1\nOrekhov\n02/09/2021\n1";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_TRUE(success_2);

    delete_catalog(new_catalog);
}

TEST(CORRECT_INPUT, zero_person_taken) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "0";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_FALSE(success_2);

    delete_catalog(new_catalog);
}


TEST(INCORRECT_INPUT, create_catalog_function) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "55*/-9\n1arriors\n10\n20\n";
    FILE* stream = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success = create_catalog(&new_catalog, stream);
    EXPECT_TRUE(success);
    fclose(stream);
    delete_catalog(new_catalog);
}

TEST(INCORRECT_INPUT, take_the_non_existent_book) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "4\n1\nUstsov\n12/12/2020\n2";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_FALSE(success_2);

    delete_catalog(new_catalog);
}

TEST(INCORRECT_INPUT, take_overlimit_copies_of_book) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "1\n1\nUstsov\n12/12/2020\n150";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_FALSE(success_2);

    delete_catalog(new_catalog);
}

TEST(INCORRECT_INPUT, take_negative_num_of_copies) {
    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "1\n1\nUstsov\n12/12/2020\n-10";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_FALSE(success_2);

    delete_catalog(new_catalog);
}

TEST(COMPARISON, create_catalog_function) {
    Book test_book_1 = {
                            false,
                            (char*)"5559-9-9", /*C-casting to avoid the C_11 ISO standard*/
                            (char*)"Warriors",
                            2019,
                            20,
                            0,
                            0,
                            nullptr,
                        };

    Book test_book_2 = {
                            false,
                            (char*)"5656-98-08",
                            (char*)"Warriors_2",
                            2020,
                            100,
                            0,
                            0,
                            nullptr,
                        };

    Book test_book_3 = {
                            false,
                            (char*)"6569-9986-6260-0",
                            (char*)"Warriors_3",
                            2022,
                            10,
                            0,
                            0,
                            nullptr,
                        };

    Book test_books[3] = {test_book_1, test_book_2, test_book_3};


    BookCatalog test_catalog =  {
                                    test_catalog.capacity = 4,
                                    test_catalog.size = 3,
                                    test_catalog.books = test_books
                                };


    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";

    FILE* stream = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success = create_catalog(&new_catalog, stream);
    fclose(stream);
    EXPECT_TRUE(success);

    EXPECT_EQ(new_catalog->size, test_catalog.size);
    for (size_t i = 0; i < new_catalog->size; ++i)
    {
        EXPECT_EQ(strcmp(new_catalog->books[i].ISBN_code, test_catalog.books[i].ISBN_code), 0);
        EXPECT_EQ(strcmp(new_catalog->books[i].name, test_catalog.books[i].name), 0);
        EXPECT_EQ(new_catalog->books[i].publication_year, test_catalog.books[i].publication_year);
        EXPECT_EQ(new_catalog->books[i].num_of_stored, test_catalog.books[i].num_of_stored);
        EXPECT_EQ(new_catalog->books[i].is_tooked, test_catalog.books[i].is_tooked);
        EXPECT_EQ(new_catalog->books[i].persons, nullptr);
        EXPECT_EQ(new_catalog->books[i].num_of_persons_tooked, 0);
        EXPECT_EQ(new_catalog->books[i].num_of_taken, 0);
    }
    delete_catalog(new_catalog);
}

TEST(COMPARISON, take_the_book_function) {
    PersonTookedBook persons_1[2] = {
                                        {(char*)"Ustsov", (char*)"12/12/2022", 2},
                                        {(char*)"Timoshenko", (char*)"05/11/2021", 2},
                                    };
    PersonTookedBook persons_3[1] = {(char*)"Orekhov", (char*)"02/09/2021", 1};


    Book test_book_1 = {
                            true,
                            (char*)"5559-9-9",
                            (char*)"Warriors",
                            2019,
                            20,
                            2,
                            4,
                            persons_1,
                        };

    Book test_book_2 = {
                            false,
                            (char*)"5656-98-08",
                            (char*)"Warriors_2",
                            2020,
                            100,
                            0,
                            0,
                            nullptr,
                        };

    Book test_book_3 = {
                            true,
                            (char*)"6569-9986-6260-0",
                            (char*)"Warriors_3",
                            2022,
                            10,
                            1,
                            1,
                            persons_3,
                        };

    Book test_books[3] = {test_book_1, test_book_2, test_book_3};


    BookCatalog test_catalog =  {
                                    test_catalog.capacity = 4,
                                    test_catalog.size = 3,
                                    test_catalog.books = test_books
                                };

    BookCatalog *new_catalog = NULL;
    static char input_catalog[] = "5559-9-9\nWarriors\n2019\n20\n5656-98-08\nWarriors_2\n2020\n100\n6569-9986-6260-0\nWarriors_3\n2022\n10\n";
    FILE* stream_1 = fmemopen(input_catalog, strlen(input_catalog), "r");
    bool success_1 = create_catalog(&new_catalog, stream_1);
    fclose(stream_1);
    EXPECT_TRUE(success_1);

    static char input_person[] = "1\n2\nUstsov\n12/12/2022\n2\nTimoshenko\n05/11/2021\n2\n3\n1\nOrekhov\n02/09/2021\n1";
    FILE* stream_2 = fmemopen(input_person, strlen(input_person), "r");
    bool success_2 = take_the_book(&new_catalog, stream_2);
    fclose(stream_2);
    EXPECT_TRUE(success_2);

    EXPECT_EQ(new_catalog->size, test_catalog.size);
    for (size_t i = 0; i < new_catalog->size; ++i)
    {
        EXPECT_EQ(new_catalog->books[i].num_of_stored, test_catalog.books[i].num_of_stored);
        EXPECT_EQ(new_catalog->books[i].is_tooked, test_catalog.books[i].is_tooked);
        EXPECT_EQ(new_catalog->books[i].num_of_persons_tooked, test_catalog.books[i].num_of_persons_tooked);

        for (size_t j = 0; j < new_catalog->books[i].num_of_persons_tooked; ++j)
        {
            EXPECT_EQ(strcmp(new_catalog->books[i].persons[j].surname, test_catalog.books[i].persons[j].surname), 0);
            EXPECT_EQ(strcmp(new_catalog->books[i].persons[j].date_taken, test_catalog.books[i].persons[j].date_taken), 0);
            EXPECT_EQ(new_catalog->books[i].persons[j].num_of_taken, test_catalog.books[i].persons[j].num_of_taken);
        }
    }
    delete_catalog(new_catalog);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
