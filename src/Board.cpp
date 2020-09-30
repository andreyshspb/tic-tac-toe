#include <cassert>
#include "Board.hpp"


SquareType Board::get_square(int row, int column) const {
    assert(0 <= row && row < FIELD_SIZE);
    assert(0 <= column && column < FIELD_SIZE);
    return _field[row][column];
}


SquareType Board::to_square_type(PlayerType player) {
    if (player == PLAYER_O) return TYPE_O;
    return TYPE_X;
}


bool Board::compare_enums(SquareType square, PlayerType player) {
    if (player == PLAYER_O && square == TYPE_O) return true;
    return player == PLAYER_X && square == TYPE_X;
}


bool Board::check_the_line(int row, int column, PlayerType player, int row_direction, int column_direction) const {
    for (int i = 0; i < SQUARES_FOR_WIN; i++) {
        int cur_row = row + i * row_direction;
        int cur_column = column + i * column_direction;
        if (!(0 <= cur_row && cur_row < FIELD_SIZE)) return false;
        if (!(0 <= cur_column && cur_column < FIELD_SIZE)) return false;
        SquareType square = _field[cur_row][cur_column];
        if (!compare_enums(square, player)) return false;
    }
    return true;
}


PlayerType Board::current_player() const {
    int count_o = 0;
    int count_x = 0;
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (compare_enums(_field[row][column], PLAYER_O)) count_o++;
            if (compare_enums(_field[row][column], PLAYER_X)) count_x++;
        }
    }
    assert(count_o - count_x == 0 || count_o - count_x == 1);
    if (count_o - count_x == 0) return PLAYER_O;
    return PLAYER_X;
}


bool Board::can_move(int row, int column, PlayerType player) const {
    assert(current_player() == player);
    assert((0 <= row && row < FIELD_SIZE));
    assert((0 <= column && column < FIELD_SIZE));
    return !(_field[row][column] != TYPE_EMPTY);
}


void Board::move(int row, int column, PlayerType player) {
    assert(can_move(row, column, player));
    _field[row][column] = to_square_type(player);
}


GameState Board::get_state() const {
    bool only_fill = true;
    bool o_wins = false;
    bool x_wins = false;
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (_field[row][column] == TYPE_EMPTY) only_fill = false;
            int row_directions[] = {DOWN_DIRECTION, NO_DIRECTION, UP_DIRECTION};
            int column_directions[] = {LEFT_DIRECTION, NO_DIRECTION, RIGHT_DIRECTION};
            for (int row_direction : row_directions) {
                for (int column_direction : column_directions) {
                    if (row_direction == NO_DIRECTION && column_direction == NO_DIRECTION) continue;
                    if (check_the_line(row, column, PLAYER_O, row_direction, column_direction)) o_wins = true;
                    if (check_the_line(row, column, PLAYER_X, row_direction, column_direction)) x_wins = true;
                }
            }
        }
    }
    if (o_wins) return O_WIN;
    if (x_wins) return X_WIN;
    if (only_fill) return DRAW;
    return RUNNING;
}
