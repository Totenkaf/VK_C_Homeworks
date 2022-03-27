// Copyright 2022 by Artem Ustsov
#include <dlfcn.h>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
    #include "lib.h"
    #include "../utils/utilities.h"
}

bool (*parallel_reflection)(int * const, size_t, size_t);

class DynamicLibraryEnvironment : public ::testing::Environment { // фикстура для подключения динамической библиотеки
public:
    virtual ~DynamicLibraryEnvironment() {}

    void SetUp() override {
        void *library = dlopen("./libparallel_work_with_matrix.so", RTLD_LAZY);
        if (!library)
            EXPECT_TRUE(library);
        void *func = dlsym(library, "parallel_side_matrix_reflection");
        parallel_reflection = reinterpret_cast<bool(*)(int * const, size_t, size_t)>(func);
        if (!parallel_reflection)
            EXPECT_TRUE(parallel_reflection);
    }
};
