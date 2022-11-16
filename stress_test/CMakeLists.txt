# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.8)
project(stress_test)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ldl -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
file(GLOB SOURCES *.c)
file(GLOB STRESS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# 2 | Executables
# ------------------------------------------------------------------------------
add_executable(stress_test ${SOURCES})
target_include_directories(stress_test PUBLIC ${LIB_INCLUDE_DIRS} ${UTILS_INCLUDE_DIRS})

option(BUILD_PARALLEL "USING SHARED LIBRARY" OFF) # By default PARALLEL is OFF.
if(BUILD_PARALLEL)
    target_link_libraries(stress_test ${LIB_PARALLEL_LIBRARIES} ${UTILS_LIBRARIES})
else()
    target_link_libraries(stress_test ${LIB_STATIC_LIBRARIES} ${UTILS_LIBRARIES})
endif()

# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()
