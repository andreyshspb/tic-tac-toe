#include "BoardTest.hpp"


// testing current_player() function

void BoardTest::first_current_player() {
    Board board;
    DO_CHECK(board.current_player() == PLAYER_O)
}

void BoardTest::second_current_player() {
    Board board;
    board.move(0, 0, PLAYER_O);
    DO_CHECK(board.current_player() == PLAYER_X)
}

void BoardTest::third_current_player() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    DO_CHECK(board.current_player() == PLAYER_O)
}


// testing can_move() function

void BoardTest::first_can_move() {
    Board board;
    DO_CHECK(board.can_move(5, 5, PLAYER_O))
}

void BoardTest::second_can_move() {
    Board board;
    board.move(0, 0, PLAYER_O);
    DO_CHECK(!board.can_move(0, 0, PLAYER_X))
}

void BoardTest::third_can_move() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    DO_CHECK(board.can_move(0, 1, PLAYER_O))
}


// testing move() function

void BoardTest::first_move() {
    Board board;
    bool correct_field = true;
    for (int row = 0; row < Board::FIELD_SIZE; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            if (board.get_square(row, column) != TYPE_EMPTY) correct_field = false;
        }
    }
    DO_CHECK(correct_field)
}

void BoardTest::second_move() {
    Board board;
    board.move(0, 0, PLAYER_O);
    bool correct_field = board.get_square(0, 0) == TYPE_O;
    for (int row = 1; row < Board::FIELD_SIZE; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            if (board.get_square(row, column) != TYPE_EMPTY) correct_field = false;
        }
    }
    for (int column = 1; column < Board::FIELD_SIZE; column++) {
        if (board.get_square(0, column) != TYPE_EMPTY) correct_field = false;
    }
    DO_CHECK(correct_field)
}

void BoardTest::third_move() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(0, 1, PLAYER_X);
    bool correct_field = board.get_square(0, 0) == TYPE_O;
    correct_field = correct_field && (board.get_square(0, 1) == TYPE_X);
    for (int row = 1; row < Board::FIELD_SIZE; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            if (board.get_square(row, column) != TYPE_EMPTY) correct_field = false;
        }
    }
    for (int column = 2; column < Board::FIELD_SIZE; column++) {
        if (board.get_square(0, column) != TYPE_EMPTY) correct_field = false;
    }
    DO_CHECK(correct_field)
}


// testing get_state() function

static PlayerType update_player(PlayerType player) {
    if (player == PLAYER_O) return PLAYER_X;
    return PLAYER_O;
}

void BoardTest::first_get_state() {
    Board board;
    DO_CHECK(board.get_state() == RUNNING)
}

void BoardTest::second_get_state() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 0, PLAYER_X);
    board.move(0, 1, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    board.move(0, 2, PLAYER_O);
    board.move(1, 2, PLAYER_X);
    board.move(0, 3, PLAYER_O);
    board.move(1, 3, PLAYER_X);
    board.move(0, 4, PLAYER_O);
    DO_CHECK(board.get_state() == O_WIN)
}

void BoardTest::third_get_state() {
    Board board;
    PlayerType current_player = PLAYER_O;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            board.move(row, column, current_player);
            current_player = update_player(current_player);
        }
    }
    for (int row = 3; row < 6; row++) {
        for (int column = Board::FIELD_SIZE - 1; column >= 0; column--) {
            board.move(row, column, current_player);
            current_player = update_player(current_player);
        }
    }
    for (int row = 6; row < 9; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            board.move(row, column, current_player);
            current_player = update_player(current_player);
        }
    }
    for (int column = 0; column < Board::FIELD_SIZE; column++) {
        board.move(9, column, current_player);
        current_player = update_player(current_player);
    }

    DO_CHECK(board.get_state() == DRAW)
}


// testing get_square() function

void BoardTest::first_get_square() {
    Board board;
    DO_CHECK(board.get_square(0, 0) == TYPE_EMPTY)
}

void BoardTest::second_get_square() {
    Board board;
    board.move(0, 0, PLAYER_O);
    DO_CHECK(board.get_square(0, 0) == TYPE_O)
}

void BoardTest::third_get_square() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    DO_CHECK(board.get_square(1, 1) == TYPE_X)
}


// testing check_the_line() function

void BoardTest::first_check_the_line() {
    Board board;
    DO_CHECK(!board.check_the_line(0, 0, PLAYER_O, Board::DOWN_DIRECTION, Board::RIGHT_DIRECTION))
}

void BoardTest::second_check_the_line() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 0, PLAYER_X);
    board.move(0, 1, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    board.move(0, 2, PLAYER_O);
    board.move(1, 2, PLAYER_X);
    board.move(0, 3, PLAYER_O);
    board.move(1, 3, PLAYER_X);
    board.move(0, 4, PLAYER_O);
    DO_CHECK(board.check_the_line(0, 0, PLAYER_O, Board::NO_DIRECTION, Board::RIGHT_DIRECTION))
}

void BoardTest::third_check_the_line() {
    Board board;
    board.move(0, 0, PLAYER_O);
    board.move(1, 0, PLAYER_X);
    board.move(0, 1, PLAYER_O);
    board.move(1, 1, PLAYER_X);
    board.move(0, 2, PLAYER_O);
    board.move(1, 2, PLAYER_X);
    board.move(0, 3, PLAYER_O);
    board.move(1, 3, PLAYER_X);
    board.move(9, 9, PLAYER_O);
    board.move(1, 4, PLAYER_X);
    DO_CHECK(board.check_the_line(1, 4, PLAYER_X, Board::NO_DIRECTION, Board::LEFT_DIRECTION))
}


void BoardTest::run_all_tests() {
    first_current_player();
    second_current_player();
    third_current_player();
    first_can_move();
    second_can_move();
    third_can_move();
    first_move();
    second_move();
    third_move();
    first_get_state();
    second_get_state();
    third_get_state();
    first_get_square();
    second_get_square();
    third_get_square();
    first_check_the_line();
    second_check_the_line();
    third_check_the_line();
}

