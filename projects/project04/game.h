#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

class BattleshipGame {
public:
    enum Cell { EMPTY, SHIP, HIT, MISS };
    enum Status { ONGOING, PLAYER1_WINS, PLAYER2_WINS };
    enum MoveResult { INVALID, MISS_SHOT, HIT_SHOT, SINK_SHOT };

    static const int SIZE = 6;

    BattleshipGame();
    MoveResult play(int move);
    Status     status() const;
    int        getCurrentPlayer() const;

    void draw(SDL_Renderer* renderer) const;

    friend std::ostream& operator<<(std::ostream& os, const BattleshipGame& game);

private:
    using Board = std::array<std::array<Cell, SIZE>, SIZE>;
    Board shipBoards[2];
    Board trackBoards[2];

    int currentPlayer;
    int lastPlayer; // NEW: Track who made the previous move
    Status gameStatus;

    const std::vector<int> shipSizes{ 4, 3, 2 };

    bool placeShip(Board& board, int r, int c, int len, bool horiz);
    void placeAllShips(Board& board);
    bool allShipsSunk(const Board& board) const;
};
