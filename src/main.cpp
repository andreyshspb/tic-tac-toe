#include "Board.hpp"
#include "BoardView.hpp"
#include "StdioBoardView.hpp"
#include "NcursesBoardView.hpp"
#include "GameController.hpp"


#include <cstring>


int main(int argc, char *argv[]) {

    Board board;
    BoardView *board_view = nullptr;

    if (argc == NcursesBoardView::CORRECT_ARGC_CURSES && std::strcmp(argv[argc - 1], NcursesBoardView::CURSES_MODE) == 0) {
        board_view = new NcursesBoardView(board);
    } else if (argc == StdioBoardView::CORRECT_ARGC_SILENT && std::strcmp(argv[argc - 1], StdioBoardView::SILENT_MODE) == 0) {
        board_view = new StdioBoardView(board, true);
    } else {
        board_view = new StdioBoardView(board, false);
    }


    GameController game_controller(*board_view, board);
    game_controller.run_game();

    delete board_view;

    return 0;
}

