#pragma once


#include "BoardView.hpp"


class GameController {
public:

    GameController(BoardView &board_view, Board &board) : _board_view(board_view), _board(board) {}

    void run_game();

private:
    BoardView &_board_view;
    Board &_board;
};
