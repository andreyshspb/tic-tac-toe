#include "StdioBoardView.hpp"
#include "Board.hpp"

#include <iostream>


char StdioBoardView::present_player(PlayerType player) {
    if (player == PLAYER_O) return 'O';
    return 'X';
}


char StdioBoardView::present_square(SquareType square) {
    if (square == TYPE_EMPTY) return '.';
    if (square == TYPE_O) return 'O';
    return 'X';
}


void StdioBoardView::print_field(bool is_running) const {
    if (_is_silent && is_running) return;
    std::cout << std::endl;
    for (int row = 0; row < Board::FIELD_SIZE; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            std::cout << present_square(_board.get_square(row, column));
        }
        std::cout << std::endl;
    }
}


void StdioBoardView::show_draw() const {
    std::cout << "Draw." << std::endl;
}


void StdioBoardView::show_player_won(PlayerType player) const {
    std::cout << present_player(player) << " wins!" << std::endl;
}


void StdioBoardView::print_command(PlayerType player) {
    std::cout << present_player(player) << " move: ";
}


void StdioBoardView::bad_move_command() {
    std::cout << "Bad move!" << std::endl;
}


bool StdioBoardView::read_data(int &row, int &column, PlayerType player) {
    while (true) {
        print_command(player);
        std::string line;
        std::getline(std::cin, line);
        char buffer1, buffer2;
        if (std::sscanf(line.c_str(), FORMAT_STEP, &row, &buffer1, &column, &buffer2) != CORRECT_ARGC || buffer1 != SEPARATE) {
            bad_move_command();
            continue;
        }
        if (row == SYMBOL_END_OF_THE_GAME && column == SYMBOL_END_OF_THE_GAME) return true;
        if (! (0 <= row && row < Board::FIELD_SIZE) || !(0 <= column && column < Board::FIELD_SIZE)) {
            bad_move_command();
            continue;
        }
        if (!_board.can_move(row, column, player)) {
            bad_move_command();
            continue;
        }
        break;
    }
    return false;
}

