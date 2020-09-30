#pragma once


#include "Board.hpp"
#include "BoardView.hpp"


class NcursesBoardView : public BoardView {
public:

    NcursesBoardView(Board &board);
    ~NcursesBoardView() override final;

    static constexpr int CORRECT_ARGC_CURSES = 2;
    static constexpr char CURSES_MODE[] = "curses";
    static constexpr int COLOR_EMPTY_SQUARE = 1;
    static constexpr int COLOR_BUSY_SQUARE = 2;
    static constexpr int COLOR_WIN_SQUARE = 3;
    static constexpr int NO_DIRECTION = 0;
    static constexpr int UP_DIRECTION = -1;
    static constexpr int DOWN_DIRECTION = 1;
    static constexpr int LEFT_DIRECTION = -1;
    static constexpr int RIGHT_DIRECTION = 1;
    static constexpr int START_DEPTH = 1;

    void print_field(bool is_running) const override;
    bool read_data(int &row, int &column, PlayerType player) override;
    void show_draw() const override;
    void show_player_won(PlayerType player) const override;

    static char present_square(SquareType square);
    static char present_player(PlayerType player);
    static void paint_square(int row, int column, PlayerType player, const Board &board);
    static bool paint_line(const Board &board, SquareType square, int depth, int row, int column, int r, int c);

private:
    int _row = 0;
    int _column = 0;
};
