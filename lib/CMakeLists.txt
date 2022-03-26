# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.8)
project(lib)


set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ldl -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
file(GLOB SOURCES_STATIC ECG.c lib_static.c)
# file(GLOB SOURCES_PARALLEL ECG.c lib_parallel.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# 2 | Libs
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_static ${SOURCES_STATIC})
# target_include_directories(${PROJECT_NAME}_static PUBLIC ${UTILS_INCLUDE_DIRS})

# add_library(${PROJECT_NAME}_parallel ${SOURCES_PARALLEL})

set(LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
set(LIB_STATIC_LIBRARIES ${PROJECT_NAME}_static PARENT_SCOPE)
# set(LIB_PARALLEL_LIBRARIES ${PROJECT_NAME}_parallel PARENT_SCOPE)



# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()