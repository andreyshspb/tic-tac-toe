#pragma once

enum SquareType {
    TYPE_EMPTY = 0,
    TYPE_O = 1,
    TYPE_X = 2
};

enum PlayerType {
    PLAYER_O = 1,
    PLAYER_X = 2
};

enum GameState {
    RUNNING = 0,
    DRAW = 1,
    O_WIN = 2,
    X_WIN = 3
};

class Board {
public:

    static constexpr int FIELD_SIZE = 10;
    static constexpr int SQUARES_FOR_WIN = 5;
    static constexpr int NO_DIRECTION = 0;
    static constexpr int UP_DIRECTION = -1;
    static constexpr int DOWN_DIRECTION = 1;
    static constexpr int LEFT_DIRECTION = -1;
    static constexpr int RIGHT_DIRECTION = 1;

    PlayerType current_player() const;
    bool can_move(int x, int y, PlayerType player) const;
    void move(int x, int y, PlayerType player);
    GameState get_state() const;
    bool check_the_line(int row, int column, PlayerType player, int row_direction, int column_direction) const;

    SquareType get_square(int row, int column) const;
    static SquareType to_square_type(PlayerType player);
    static bool compare_enums(SquareType square, PlayerType player);

private:
    SquareType _field[FIELD_SIZE][FIELD_SIZE] = {TYPE_EMPTY};
};
