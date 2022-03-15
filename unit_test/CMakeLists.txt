# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.14)
project(unit_test)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ldl -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
find_package(GTest REQUIRED)
set(input_test_src ${PROJECT_SOURCE_DIR}/input_test.cpp)
set(functionality_test_src ${PROJECT_SOURCE_DIR}/functionality_test.cpp)
file(GLOB SOURCES *.cpp)

# ------------------------------------------------------------------------------
# 2 | Executables
# ------------------------------------------------------------------------------
add_executable(input_test ${input_test_src})
target_include_directories(input_test PUBLIC ${BOOK_CATALOG_LIB_INCLUDE_DIRS})
target_link_libraries(input_test ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(input_test ${BOOK_CATALOG_LIB_LIBRARIES})

add_executable(functionality_test ${functionality_test_src})
target_include_directories(functionality_test PUBLIC ${BOOK_CATALOG_LIB_INCLUDE_DIRS})
target_link_libraries(functionality_test ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(functionality_test ${BOOK_CATALOG_LIB_LIBRARIES})