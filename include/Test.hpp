#pragma once

#define DO_CHECK(EXPR)  check(EXPR, __func__, __FILE__, __LINE__);

#include <cstdlib>


class Test {
protected:

    static int failed_num;
    static int total_num;

    static void check(bool expr, const char *func, const char  *filename, size_t line_num);

public:
    static bool show_final_result();

    virtual void run_all_tests() = 0;
};