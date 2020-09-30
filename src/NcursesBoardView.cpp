#include "NcursesBoardView.hpp"
#include "Board.hpp"
#include <GameController.hpp>

#include <ncurses.h>
#include <string>


NcursesBoardView::NcursesBoardView(Board &board) : BoardView(board) {
    initscr();
    start_color();
    keypad(stdscr, true);
    init_pair(COLOR_EMPTY_SQUARE, COLOR_GREEN, COLOR_WHITE);
    init_pair(COLOR_BUSY_SQUARE, COLOR_RED, COLOR_WHITE);
    init_pair(COLOR_WIN_SQUARE, COLOR_YELLOW, COLOR_BLACK);
}


NcursesBoardView::~NcursesBoardView() {
    endwin();
}


char NcursesBoardView::present_player(PlayerType player) {
    if (player == PLAYER_O) return 'O';
    return 'X';
}


char NcursesBoardView::present_square(SquareType square) {
    if (square == TYPE_EMPTY) return '.';
    if (square == TYPE_O) return 'O';
    return 'X';
}


void NcursesBoardView::paint_square(int row, int column, PlayerType player, const Board &board) {
    std::string square = "";
    if (board.can_move(row, column, player)) {
        square = present_square(board.get_square(row, column));
        attron(COLOR_PAIR(COLOR_EMPTY_SQUARE));
        printw(square.c_str());
        attroff(COLOR_PAIR(COLOR_EMPTY_SQUARE));
    } else {
        square = present_square(board.get_square(row, column));
        attron(COLOR_PAIR(COLOR_BUSY_SQUARE));
        printw(square.c_str());
        attroff(COLOR_PAIR(COLOR_BUSY_SQUARE));
    }
}


bool NcursesBoardView::paint_line(const Board &board, SquareType square, int depth, int row, int column, int r, int c) {
    if (!(0 <= row && row < Board::FIELD_SIZE)) return false;
    if (!(0 <= column && column < Board::FIELD_SIZE)) return false;
    if (depth == Board::SQUARES_FOR_WIN) {
        return board.get_square(row, column) == square;
    }
    if (board.get_square(row, column) != square) return false;
    if (paint_line(board, square, depth + 1, row + r, column + c, r, c)) {
        std::string buffer = "";
        buffer = present_square(square);
        attron(COLOR_PAIR(COLOR_WIN_SQUARE));
        move(row + r, column + c);
        printw(buffer.c_str());
        move(row, column);
        printw(buffer.c_str());
        attroff(COLOR_PAIR(COLOR_WIN_SQUARE));
        return true;
    }
    return false;
}


void NcursesBoardView::print_field(bool is_running) const {
    clear();
    std::string field;
    for (int row = 0; row < Board::FIELD_SIZE; row++) {
        for (int column = 0; column < Board::FIELD_SIZE; column++) {
            if (row == _row && column == _column && is_running) {
                printw(field.c_str());
                field = "";
                paint_square(row, column, _board.current_player(), _board);
                continue;
            }
            field += present_square(_board.get_square(row, column));
        }
        field += '\n';
    }
    printw(field.c_str());
    if (!is_running) {
        for (int row = 0; row < Board::FIELD_SIZE; row++) {
            for (int column = 0; column < Board::FIELD_SIZE; column++) {
                SquareType square = _board.get_square(row, column);
                if (square == TYPE_EMPTY) continue;
                if (paint_line(_board, square, START_DEPTH, row, column, UP_DIRECTION, NO_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, UP_DIRECTION, LEFT_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, UP_DIRECTION, RIGHT_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, NO_DIRECTION, LEFT_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, NO_DIRECTION, RIGHT_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, DOWN_DIRECTION, NO_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, DOWN_DIRECTION, LEFT_DIRECTION)) return;
                if (paint_line(_board, square, START_DEPTH, row, column, DOWN_DIRECTION, RIGHT_DIRECTION)) return;
            }
        }
    }
}


bool NcursesBoardView::read_data(int &row, int &column, PlayerType player)  {
    while (true) {
        print_field(true);
        move(_row, _column);
        int command = getch();
        switch (command) {
            case KEY_DOWN:
                if (_row < Board::FIELD_SIZE - 1) _row += 1;
                break;
            case KEY_UP:
                if (_row > 0) _row -= 1;
                break;
            case KEY_RIGHT:
                if (_column < Board::FIELD_SIZE - 1) _column += 1;
                break;
            case KEY_LEFT:
                if (_column > 0) _column -= 1;
                break;
            case ' ':
                if (!_board.can_move(_row, _column, player)) continue;
                row = _row;
                column = _column;
                return false;
            case 'x':
                return true;
        }
    }
}


void NcursesBoardView::show_draw() const {
    move(Board::FIELD_SIZE, 0);
    printw("Draw.\n");
    getch();
}


void NcursesBoardView::show_player_won(PlayerType player) const {
    move(Board::FIELD_SIZE, 0);
    std::string buffer = "";
    buffer = buffer + present_player(player) + " wins!\n";
    printw(buffer.c_str());
    getch();
}
