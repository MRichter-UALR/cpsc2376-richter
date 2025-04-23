#pragma once

#include <array>
#include <vector>
#include <iostream>

class BattleshipGame {
public:
    enum Cell { EMPTY, SHIP, HIT, MISS };
    enum Status { ONGOING, PLAYER1_WINS, PLAYER2_WINS };
    enum MoveResult { INVALID, MISS_SHOT, HIT_SHOT, SINK_SHOT };

    static const int SIZE = 6;            // 6×6 grid
    BattleshipGame();                     // set up boards & ships

    MoveResult play(int move);            // fire at 0…35
    Status     status() const;            // who’s won (if anyone)
    int        getCurrentPlayer() const;  // whose turn it is

    friend std::ostream& operator<<(
        std::ostream& os, const BattleshipGame& game);

private:
    using Board = std::array<std::array<Cell, SIZE>, SIZE>;
    Board shipBoards[2];
    Board trackBoards[2];

    int    currentPlayer;
    Status gameStatus;

    // three ships: lengths 4, 3, and 2
    const std::vector<int> shipSizes{ 4, 3, 2 };

    bool placeShip(Board& board, int r, int c, int len, bool horiz);
    void placeAllShips(Board& board);
    bool allShipsSunk(const Board& board) const;
};
