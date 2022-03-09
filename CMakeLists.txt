# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================
cmake_minimum_required(VERSION 3.8)
set(project_name book_catalog)
project(${project_name})

project(tests_gtest CXX)

find_package(Git REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ldl -pthread -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -ldl -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
# Main project
set(includes ${PROJECT_SOURCE_DIR}/include)
include(ExternalProject)
include_directories(${includes})
# Gtest includes
include_directories(${GTEST_INCLUDE_DIRS})

# Main stress test
set(includes_time_test ${PROJECT_SOURCE_DIR}/stress_test/include)

# ------------------------------------------------------------------------------
# 2 | Sources_MAIN
# ------------------------------------------------------------------------------
# Main project source
set(sources ${PROJECT_SOURCE_DIR}/src)

# Main function source
set(src_main ${sources}/main.c)
# Subsudiary sources
set(src_files_lib ${sources}/matrix.c)
set(src_files_utils ${sources}/utils.c)
# Main static source
set(src_files_static ${sources}/matrix_cons.c)
# Main dynaic source
set(src_files_dynamic ${sources}/matrix_parallel.c)
# Main creator source
set(src_files_random_matrix_creation ${sources}/matrix_creator.c)


# ------------------------------------------------------------------------------
# 3 | Sources_STRESS TEST
# ------------------------------------------------------------------------------
# Main stress_test source
set(sources_time_tests ${PROJECT_SOURCE_DIR}/stress_test/src)

# Main function stress_test source
set(src_main_stress_test ${sources_time_tests}/main.c)
set(src_files_test_common ${sources_time_tests}/stress_test.c)


# ------------------------------------------------------------------------------
# 4 | Libraries
# ------------------------------------------------------------------------------
# Main static
add_library(${project_name}_static STATIC ${src_files_lib} ${src_files_static} ${src_files_utils})
# Main dynamic
add_library(${project_name}_dynamic SHARED ${src_files_lib} ${src_files_dynamic} ${src_files_utils})


# ------------------------------------------------------------------------------
# 5 | Executables_MAIN
# ------------------------------------------------------------------------------
# Creation availability
add_executable(run_creation ${src_files_utils} ${src_files_random_matrix_creation})
target_include_directories(run_creation PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Consecutive case availability
add_executable(run_consecutive ${src_main})
target_link_libraries(run_consecutive ${project_name}_static)
target_include_directories(run_consecutive PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Parallel case availability
add_executable(run_parallel ${src_main})
target_link_libraries(run_parallel ${project_name}_dynamic)
target_include_directories(run_parallel PUBLIC ${PROJECT_SOURCE_DIR}/include)


# ------------------------------------------------------------------------------
# 6 | Executables_STRESS TEST
# ------------------------------------------------------------------------------

if(ENABLE_STRESS_TEST)
# Consecutive stress test case availability
  add_executable(run_consecutive_st ${src_main_stress_test} ${src_files_test_common})
  target_link_libraries(run_consecutive_st ${project_name}_static)
  target_include_directories(run_consecutive_st PUBLIC ${PROJECT_SOURCE_DIR}/stress_test/include)

  # Parallel stress test case availability
  add_executable(run_parallel_st ${src_main_stress_test} ${src_files_test_common})
  target_link_libraries(run_parallel_st ${project_name}_dynamic)
  target_include_directories(run_parallel_st PUBLIC ${PROJECT_SOURCE_DIR}/stress_test/include)
endif()

# ==============================================================================
# III | Check settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Clang-Tidy
# ------------------------------------------------------------------------------
if(ENABLE_CLANG_TIDY)

    find_program(CLANG_TIDY_BIN clang-tidy-10)
    find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-10.py)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-10")
    endif()

    if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate run-clang-tidy-10.py")
    endif()

    list(APPEND RUN_CLANG_TIDY_BIN_ARGS
        -clang-tidy-binary ${CLANG_TIDY_BIN}
        -header-filter=.*
        -checks=cert*,misc*,perf*,cppc*,read*,mode*
    )
    add_custom_target(
        tidy
        COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
        COMMENT "running clang tidy"
    )
endif()

# ------------------------------------------------------------------------------
# 2 | Clang-Format
# ------------------------------------------------------------------------------
if(ENABLE_CLANG_FORMAT)
  file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
         ${PROJECT_SOURCE_DIR}/src/*.c
         ${PROJECT_SOURCE_DIR}/incude/*.h
         ${PROJECT_SOURCE_DIR}/stress_test/include/*.h
         ${PROJECT_SOURCE_DIR}/stress_test/src/*.c
         ${PROJECT_SOURCE_DIR}/unit_tests/*.cpp)

  add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format
    -i
    -style=LLVM
    ${ALL_CXX_SOURCE_FILES}
  )

endif()

# ------------------------------------------------------------------------------
# 3 | Facebook Infer
# ------------------------------------------------------------------------------
if(ENABLE_INFER)
  add_custom_target(
    infer
    COMMAND /usr/local/bin/infer run
    --reactive
    --print-logs
    --compilation-database compile_commands.json
  )
endif()

# ------------------------------------------------------------------------------
# 4 | CppLint
# ------------------------------------------------------------------------------
if(ENABLE_CPPLINT)
  file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
         ${PROJECT_SOURCE_DIR}/src/*.c
         ${PROJECT_SOURCE_DIR}/stress_test/src/*.c
         ${PROJECT_SOURCE_DIR}/unit_tests/*.cpp)

  add_custom_target(
      cpplint
      COMMAND /usr/local/bin/cpplint 
      --extensions=c,cpp,h,hpp
      --linelength=80
      --filter=-runtime/casting,-readability/casting,-build/include_subdir,-build/include_order,-whitespace/indent
      ${ALL_CXX_SOURCE_FILES}
  )
endif()

# ------------------------------------------------------------------------------
# 5 | CodeCoverage
# ------------------------------------------------------------------------------
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

# ------------------------------------------------------------------------------
# 6 | CppCheck
# ------------------------------------------------------------------------------
option(ENABLE_CPPCHECK "Build all tests." OFF) # Makes boolean 'test' available.
if(ENABLE_CPPCHECK)

    list(APPEND CPPCHECK_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    )

    ExternalProject_Add(
        cppcheck
        GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
        GIT_TAG             1.79
        GIT_SHALLOW         1
        CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
        PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )

    list(APPEND CPPCHECK_ARGS
        --enable=all
        --suppress=missingIncludeSystem
        --std=c11
        --verbose
        --error-exitcode=1
        --language=c
        --check-config
        -DMAIN = main
        -I ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/unit_test/*.cpp
        ${CMAKE_SOURCE_DIR}/stress_test/src/*.c
        ${CMAKE_SOURCE_DIR}/stress_test/include/*.h
    )

    add_custom_target(
        check
        COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
        COMMENT "running cppcheck"
    )
endif()


# ------------------------------------------------------------------------------
# 7 | Google Sanitizers
# ------------------------------------------------------------------------------
if(ENABLE_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_USAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()


# ==============================================================================
# IV | Tests
# ==============================================================================
option(BUILD_TESTS "Build all tests." OFF) # Makes boolean 'test' available.

if (BUILD_TESTS)

  include(CTest)
  include_directories(${GTEST_INCLUDE_DIRS})
  
  add_executable(run_functionality_consecutive_test unit_tests/functionality_test.cpp)
  target_link_libraries(run_functionality_consecutive_test ${GTEST_LIBRARIES} -lpthread)
  target_link_libraries(run_functionality_consecutive_test ${project_name}_static)
  target_include_directories(run_functionality_consecutive_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

  add_executable(run_functionality_parallel_test unit_tests/functionality_test.cpp)
  target_link_libraries(run_functionality_parallel_test ${GTEST_LIBRARIES} -lpthread)
  target_link_libraries(run_functionality_parallel_test ${project_name}_dynamic)
  target_include_directories(run_functionality_parallel_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

  add_executable(run_input_test unit_tests/input_test.cpp)
  target_link_libraries(run_input_test ${GTEST_LIBRARIES} -lpthread)
  target_link_libraries(run_input_test ${project_name}_static)
  target_include_directories(run_input_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

  add_executable(run_comparison_test unit_tests/comparison_test.cpp)
  target_link_libraries(run_comparison_test ${GTEST_LIBRARIES} -lpthread)
  target_link_libraries(run_comparison_test ${project_name}_static)
  target_include_directories(run_comparison_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

  add_test(functionality_consecutive_test ${EXECUTABLE_OUTPUT_PATH}/run_functionality_consecutive_test)
  add_test(functionality_parallel_test ${EXECUTABLE_OUTPUT_PATH}/run_functionality_parallel_test)
  add_test(input_test ${EXECUTABLE_OUTPUT_PATH}/run_input_test)
  add_test(comparison_test ${EXECUTABLE_OUTPUT_PATH}/run_comparison_test)

endif()
