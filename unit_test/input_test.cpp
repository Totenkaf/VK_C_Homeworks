// Copyright 2022 by Artem Ustsov

#include <cstring>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
#include "../lib/lib.h"
#include "../utils/utilities.h"
}

TEST(INPUT_TEST_1, INPUT_STRING) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << "this is a message string\n";
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  char *test_string = input_string(test_file_c);
  EXPECT_EQ(strcmp(test_string, "this is a message string\n"), 0);

  free(test_string);
  fclose(test_file_c);
  remove("test.txt");
}

TEST(INPUT_TEST_2, INPUT_WRONG_STRING) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << "test_string_7879-2554*/^&$#\n";
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  char *test_string = input_string(test_file_c);
  EXPECT_EQ(strcmp(test_string, "test_string_7879-2554*/^&$#\n"), 0);

  free(test_string);
  fclose(test_file_c);
  remove("test.txt");
}

TEST(INPUT_TEST_3, INPUT_STRINGS) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << "test_string1" << std::endl;
  test_file << "test_string2" << std::endl;
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  char *test_string = input_string(test_file_c);
  EXPECT_EQ(strcmp(test_string, "test_string1\n"), 0);
  free(test_string);

  test_string = input_string(test_file_c);
  EXPECT_EQ(strcmp(test_string, "test_string2\n"), 0);
  free(test_string);

  fclose(test_file_c);
  remove("test.txt");
}

TEST(INPUT_TEST_4, INPUT_EMPTY_STRING) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << "\n";
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  char *test_string = input_string(test_file_c);
  EXPECT_EQ(strcmp(test_string, "\n"), 0);

  free(test_string);
  fclose(test_file_c);
  remove("test.txt");
}

TEST(INPUT_TEST_5, INPUT_NUMBER) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << 150;
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  int test_number = input_number(test_file_c);
  EXPECT_EQ(test_number, 150);

  fclose(test_file_c);
  remove("test.txt");
}

TEST(INPUT_TEST_6, INPUT_WRONG_NUMBER) {
  std::ofstream test_file;
  test_file.open("test.txt");
  test_file << "abc";
  test_file.close();

  FILE *test_file_c = fopen("test.txt", "r");
  int test_number = input_number(test_file_c);
  EXPECT_EQ(test_number, 0);

  fclose(test_file_c);
  remove("test.txt");
}

TEST(ECG_TEST_1, NULL_POINTER) {
  bool success = create_ECG(nullptr, stdin);
  EXPECT_FALSE(success);
}

TEST(ECG_TEST_2, CORRECT_INPUT) {
  std::ofstream test_file;

  size_t sequence_size = 12;
  int input_sequence[sequence_size] = {10, -20, 10, 6, 9,   7,
                                       -9, 8,   0,  1, -50, 3};
  test_file.open("test.txt");
  for (size_t i = 0; i < sequence_size; ++i) {
    test_file << input_sequence[i] << std::endl;
  }
  test_file.close();

  int test_signals_data[] = {-20, 10, 6, 9, 7, -9, 8, 0, 1, -50};
  ECG test_ecg = {.signals_data = test_signals_data, .size = 10, .R_window = 3};

  FILE *test_input = fopen("test.txt", "r");
  ECG *ecg = NULL;

  bool success = create_ECG(&ecg, test_input);
  EXPECT_TRUE(success);
  fclose(test_input);
  remove("test.txt");

  EXPECT_EQ(ecg->size, test_ecg.size);
  EXPECT_EQ(ecg->R_window, test_ecg.R_window);

  for (size_t i = 0; i < ecg->size; ++i) {
    EXPECT_EQ(ecg->signals_data[i], test_ecg.signals_data[i]);
  }
  delete_ecg(ecg);
}

TEST(UTILS_TEST_1, CREATE_SEQUENCE) {
  const char *filename = "test.txt";
  size_t size = 10;
  size_t R_window = 2;
  bool success = create_random_sequence_file(filename, size, R_window);
  EXPECT_TRUE(success);
  remove("test.txt");
}

TEST(UTILS_TEST_2, BAD_STREAM_SEQUENCE) {
  const char *filename = nullptr;
  size_t size = 10;
  size_t R_window = 2;
  bool success = create_random_sequence_file(filename, size, R_window);
  EXPECT_FALSE(success);
}

TEST(UTILS_TEST_3, BAD_SIZE_SEQUENCE) {
  const char *filename = "test.txt";
  size_t size = 0;
  size_t R_window = 2;
  bool success = create_random_sequence_file(filename, size, R_window);
  EXPECT_FALSE(success);
  remove("test.txt");
}

TEST(UTILS_TEST_4, BAD_R_WINDOW) {
  const char *filename = "test.txt";
  size_t size = 10;
  size_t R_window = 0;
  bool success = create_random_sequence_file(filename, size, R_window);
  EXPECT_FALSE(success);
  remove("test.txt");
}

TEST(UTILS_TEST_5, GET_FILE_STREAM_STATIC) {
  FILE *stream = nullptr;
  size_t user_cores = 0;
  int argc = 5;
  char *argv[] = {(char *)"./ECG", (char *)"-i1", (char *)"test.txt",
                  (char *)"10", (char *)"2"};
  stream = get_stream(&user_cores, argc, argv);
  EXPECT_TRUE(stream);
  EXPECT_EQ(user_cores, 0);
  fclose(stream);
}

// TEST(UTILS_TEST_6, GET_FILE_STREAM_PARALLEL) {
//   FILE* stream = nullptr;
//   size_t user_cores = 0;
//   int argc = 6;
//   char* argv[] = {(char*)"./ECG",
//                   (char*)"-j4",
//                   (char*)"-i1",
//                   (char*)"test.txt",
//                   (char*)"10",
//                   (char*)"2"};
//   stream = get_stream(&user_cores, argc, argv);
//   EXPECT_TRUE(stream);
//   EXPECT_EQ(user_cores, 4);
//   fclose(stream);
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
