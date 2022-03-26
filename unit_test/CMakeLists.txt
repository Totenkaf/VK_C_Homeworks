# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.14)
project(unit_test)


set(CMAKE_CXX_STANDARD 11)
# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
include(CTest)
find_package(GTest REQUIRED)
set(input_test_src ${PROJECT_SOURCE_DIR}/input_test.cpp)
set(static_test_src ${PROJECT_SOURCE_DIR}/static_test.cpp)

# ------------------------------------------------------------------------------
# 2 | Executables
# ------------------------------------------------------------------------------
add_executable(input_test ${input_test_src})
target_include_directories(input_test PUBLIC ${LIB_INCLUDE_DIRS} ${UTILS_INCLUDE_DIRS})
target_link_libraries(input_test ${LIB_STATIC_LIBRARIES} ${UTILS_LIBRARIES})
target_link_libraries(input_test ${GTEST_LIBRARIES} -pthread)

add_executable(static_test ${static_test_src})
target_include_directories(static_test PUBLIC ${LIB_INCLUDE_DIRS} ${UTILS_INCLUDE_DIRS})
target_link_libraries(static_test ${LIB_STATIC_LIBRARIES} ${UTILS_LIBRARIES})
target_link_libraries(static_test ${GTEST_LIBRARIES} -pthread)

# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()