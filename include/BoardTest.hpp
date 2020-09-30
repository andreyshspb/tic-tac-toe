#pragma once


#include "Board.hpp"
#include "Test.hpp"


class BoardTest : public Test {
private:

    // testing current_player() function
    static void first_current_player();
    static void second_current_player();
    static void third_current_player();

    // testing can_move() function
    static void first_can_move();
    static void second_can_move();
    static void third_can_move();

    // testing move() function
    static void first_move();
    static void second_move();
    static void third_move();

    // testing get_state() function
    static void first_get_state();
    static void second_get_state();
    static void third_get_state();

    // testing get_square() function
    static void first_get_square();
    static void second_get_square();
    static void third_get_square();

    // testing check_the_line() function
    static void first_check_the_line();
    static void second_check_the_line();
    static void third_check_the_line();

public:
    void run_all_tests() override;
};
