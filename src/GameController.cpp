#include "GameController.hpp"
#include "Board.hpp"


void GameController::run_game() {

    while (true) {

        _board_view.print_field(true);

        PlayerType current_player = _board.current_player();
        int row, column;
        if (_board_view.read_data(row, column, current_player)) return;

        _board.move(row, column, current_player);
        GameState game_state = _board.get_state();
        switch (game_state) {
            case RUNNING:
                break;
            case DRAW:
                _board_view.print_field(false);
                _board_view.show_draw();
                return;
            case O_WIN:
                _board_view.print_field(false);
                _board_view.show_player_won(PLAYER_O);
                return;
            case X_WIN:
                _board_view.print_field(false);
                _board_view.show_player_won(PLAYER_X);
                return;

        }

    }

}

