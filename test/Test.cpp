#include <Test.hpp>

#include <iostream>

int Test::failed_num = 0;
int Test::total_num = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t line_num) {
    total_num += 1;
    if (expr) return;
    failed_num += 1;
    std::cout << filename << ':' << line_num << ": " << func << "(): ";
    std::cout << "Test failed" << std::endl;
}

bool Test::show_final_result() {
    std::cout << total_num - failed_num << "/" << total_num;
    std::cout << " tests were passed" << std::endl;
    return failed_num == 0;
}

