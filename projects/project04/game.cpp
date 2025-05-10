#include "game.h"
#include "GameConfig.h"
#include <random>

static int randInt(int a, int b) {
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}

BattleshipGame::BattleshipGame()
    : currentPlayer(0), gameStatus(ONGOING) {
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
        gameStatus = (currentPlayer == 0 ? PLAYER1_WINS : PLAYER2_WINS);
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
        for (int c = 0; c < BattleshipGame::SIZE; ++c) {
            char ch = (g.shipBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::SHIP ? 'S'
                : g.shipBoards[g.getCurrentPlayer()][r][c] == BattleshipGame::HIT ? 'X'
                : '.');
            os << ch << ' ';
        }
        os << "  |  ";
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

void BattleshipGame::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_Rect banner = { 0, 0, SCREEN_WIDTH, 60 };
    SDL_RenderFillRect(renderer, &banner);

    // Per-player themes
    SDL_Color shipsFill = (currentPlayer == 0) ? SDL_Color{ 80, 120, 200, 255 } : SDL_Color{ 60, 160, 160, 255 };
    SDL_Color shotsFill = (currentPlayer == 0) ? SDL_Color{ 40, 60, 100, 255 } : SDL_Color{ 20, 80, 80, 255 };
    SDL_Color shotsTint = (currentPlayer == 0) ? SDL_Color{ 0, 120, 255, 255 } : SDL_Color{ 0, 180, 180, 255 };

    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            // SHIPS
            rect.x = LEFT_GRID_X + c * CELL_SIZE;
            rect.y = BOARD_OFFSET_Y + r * CELL_SIZE;
            rect.w = rect.h = CELL_SIZE;

            Cell cell = shipBoards[currentPlayer][r][c];
            if (cell == HIT) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else if (cell == SHIP) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white for ships
            else SDL_SetRenderDrawColor(renderer, shipsFill.r, shipsFill.g, shipsFill.b, 255);

            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);

            // SHOTS
            rect.x = RIGHT_GRID_X + c * CELL_SIZE;

            Cell tcell = trackBoards[currentPlayer][r][c];
            if (tcell == HIT) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else if (tcell == MISS) SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            else SDL_SetRenderDrawColor(renderer, shotsFill.r, shotsFill.g, shotsFill.b, 255);

            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
