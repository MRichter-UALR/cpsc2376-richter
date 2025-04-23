#include "game.h"
#include <random>

// random integer in [a, b]
static int randInt(int a, int b) {
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}

BattleshipGame::BattleshipGame()
    : currentPlayer(0), gameStatus(ONGOING)
{
    for (int p = 0; p < 2; ++p) {
        for (auto& row : shipBoards[p])  row.fill(EMPTY);
        for (auto& row : trackBoards[p]) row.fill(EMPTY);
        placeAllShips(shipBoards[p]);
    }
}

bool BattleshipGame::placeShip(Board& board, int r, int c, int len, bool horiz) {
    if (horiz) {
        if (c + len > SIZE) return false;
        for (int i = 0; i < len; ++i)
            if (board[r][c + i] != EMPTY) return false;
        for (int i = 0; i < len; ++i)
            board[r][c + i] = SHIP;
    }
    else {
        if (r + len > SIZE) return false;
        for (int i = 0; i < len; ++i)
            if (board[r + i][c] != EMPTY) return false;
        for (int i = 0; i < len; ++i)
            board[r + i][c] = SHIP;
    }
    return true;
}

void BattleshipGame::placeAllShips(Board& board) {
    for (int len : shipSizes) {
        bool placed = false;
        while (!placed) {
            bool horiz = randInt(0, 1);
            int r = randInt(0, horiz ? SIZE - 1 : SIZE - len);
            int c = randInt(0, horiz ? SIZE - len : SIZE - 1);
            placed = placeShip(board, r, c, len, horiz);
        }
    }
}

BattleshipGame::MoveResult BattleshipGame::play(int move) {
    int total = SIZE * SIZE;
    if (move < 0 || move >= total)
        return INVALID;

    int r = move / SIZE, c = move % SIZE;
    if (trackBoards[currentPlayer][r][c] != EMPTY)
        return INVALID;

    int opp = 1 - currentPlayer;
    bool hit = (shipBoards[opp][r][c] == SHIP);
    if (hit) {
        shipBoards[opp][r][c] = HIT;
        trackBoards[currentPlayer][r][c] = HIT;
    }
    else {
        trackBoards[currentPlayer][r][c] = MISS;
    }

    if (allShipsSunk(shipBoards[opp])) {
        gameStatus = (currentPlayer == 0
            ? PLAYER1_WINS
            : PLAYER2_WINS);
        return SINK_SHOT;
    }

    currentPlayer = opp;
    return hit ? HIT_SHOT : MISS_SHOT;
}

BattleshipGame::Status BattleshipGame::status() const {
    return gameStatus;
}

int BattleshipGame::getCurrentPlayer() const {
    return currentPlayer;
}

bool BattleshipGame::allShipsSunk(const Board& board) const {
    for (auto& row : board)
        for (auto cell : row)
            if (cell == SHIP)
                return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const BattleshipGame& g) {
    os << "Player " << (g.getCurrentPlayer() + 1)
        << " - Your ships    |  Your shots\n";
    for (int r = 0; r < BattleshipGame::SIZE; ++r) {
        // show ships
        for (int c = 0; c < BattleshipGame::SIZE; ++c) {
            char ch = (g.shipBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::SHIP ? 'S'
                : g.shipBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::HIT ? 'X'
                : '.');
            os << ch << ' ';
        }
        os << "  |  ";
        // show shots
        for (int c = 0; c < BattleshipGame::SIZE; ++c) {
            char ch = (g.trackBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::HIT ? 'X'
                : g.trackBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::MISS ? 'o'
                : '.');
            os << ch << ' ';
        }
        os << "\n";
    }
    return os;
}
