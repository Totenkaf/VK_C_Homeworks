# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.8)
project(utils)


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
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# 2 | Libs
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} ${SOURCES})

set(UTILS_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(UTILS_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()
