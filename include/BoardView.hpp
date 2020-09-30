#pragma once

#include "Board.hpp"


class BoardView {
public:

    BoardView(Board &board) : _board(board) {}
    virtual ~BoardView() = default;

    virtual void print_field(bool is_running) const = 0;
    virtual bool read_data(int &row, int &column, PlayerType player) = 0;
    virtual void show_draw() const = 0;
    virtual void show_player_won(PlayerType player) const = 0;

protected:
    Board &_board;

};

