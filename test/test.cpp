#include "BoardTest.hpp"

int main() {

    BoardTest board_test;
    board_test.run_all_tests();

    if (board_test.show_final_result()) return 0;
    return 1;
}

