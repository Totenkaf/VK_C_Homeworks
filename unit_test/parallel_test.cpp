// Copyright 2022 by Artem Ustsov

#include <cstring>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
#include "lib.h"
#include "utilities.h"
}

TEST(PARALLEL_LIB_TEST_1, NULL_SEQUENCE) {
  ECG ecg = {.signals_data = nullptr, .size = 0, .R_window = 1};
  size_t user_cores = 4;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 0);
}

TEST(PARALLEL_LIB_TEST_1, BAD_CORES) {
  ECG ecg = {.signals_data = nullptr, .size = 0, .R_window = 1};
  size_t user_cores = 0;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 0);
}

TEST(PARALLEL_LIB_TEST_3, UNIQUE_PEAK_AND_WINDOW) {
  int sequence[] = {1, 2, 3, 2, 1};
  ECG ecg = {.signals_data = sequence, .size = 5, .R_window = 1};
  size_t user_cores = 4;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 1);
}

TEST(PARALLEL_LIB_TEST_4, BEGIN_END_PEAKS) {
  int sequence[] = {3, 2, 1, 0, -1, 5, 6, 7, 8, 9};
  ECG ecg = {.signals_data = sequence, .size = 10, .R_window = 5};
  size_t user_cores = 4;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 2);
}

TEST(PARALLEL_LIB_TEST_5, SKIP_PEAK) {
  int sequence[] = {1, 2, 1, 10, -1, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4};
  ECG ecg = {.signals_data = sequence, .size = 15, .R_window = 5};
  size_t user_cores = 4;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 2);
}

TEST(PARALLEL_LIB_TEST_6, EVEN_WINDOW) {
  int sequence[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
  ECG ecg = {.signals_data = sequence, .size = 10, .R_window = 2};
  size_t user_cores = 4;
  size_t result = count_R_peaks(&ecg, &user_cores);
  EXPECT_EQ(result, 3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
