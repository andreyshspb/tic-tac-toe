#pragma once

#include "Board.hpp"
#include "BoardView.hpp"


class StdioBoardView : public BoardView {
public:

    static constexpr int CORRECT_ARGC = 3;
    static constexpr int CORRECT_ARGC_SILENT = 2;
    static constexpr int SYMBOL_END_OF_THE_GAME = -1;
    static constexpr char FORMAT_STEP[] = "%d%c%d %c";
    static constexpr char SEPARATE = ' ';
    static constexpr char SILENT_MODE[] = "silent";

    StdioBoardView(Board &board, bool is_silent) : BoardView(board), _is_silent(is_silent) {}

    void print_field(bool is_running) const override;
    bool read_data(int &row, int &column, PlayerType player) override;
    void show_draw() const override;
    void show_player_won(PlayerType player) const override;

    static void print_command(PlayerType player);
    static void bad_move_command();
    static char present_player(PlayerType player);
    static char present_square(SquareType square);

private:
    bool _is_silent;
};
