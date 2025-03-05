#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Constants for the game
const int BOARD_SIZE = 6; // Grid size (6x6)
const char EMPTY = '-'; // Empty space on the board
const char PLAYER1 = 'P'; // Player 1 car
const char PLAYER2 = 'Q'; // Player 2 car
const char OBSTACLE = 'X'; // Obstacle

enum class GameState { ONGOING, PLAYER1_WINS, PLAYER2_WINS, DRAW };

// Function prototypes
void makeBoard(std::vector<std::vector<char>>& board);
void printBoard(const std::vector<std::vector<char>>& board);
bool isValidMove(const std::vector<std::vector<char>>& board, int x, int y);
GameState gameStatus(const std::vector<std::vector<char>>& board);
void movePlayer(std::vector<std::vector<char>>& board, char player, int newX, int newY);
void placeObstacles(std::vector<std::vector<char>>& board);

int main() {
    srand(time(0)); // Seed for random number generation

    // Initialize the board
    std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY));
    makeBoard(board);
    placeObstacles(board);

    // Game Loop
    GameState state = GameState::ONGOING;
    int player1X = 0, player1Y = 0; // Player 1 starts at (0, 0)
    int player2X = BOARD_SIZE - 1, player2Y = 0; // Player 2 starts at (BOARD_SIZE-1, 0)
    int turn = 0; // 0 for Player 1, 1 for Player 2

    while (state == GameState::ONGOING) {
        printBoard(board);

        int direction;
        int x = (turn == 0) ? player1X : player2X;
        int y = (turn == 0) ? player1Y : player2Y;

        if (turn == 0) {
            std::cout << "Player 1's turn (P):\n";
        } else {
            std::cout << "Player 2's turn (Q):\n";
        }

        std::cout << "Enter direction (1: up, 2: down, 3: left, 4: right): ";
        std::cin >> direction;

        int newX = x, newY = y;
        
        // Determine new coordinates based on the direction
        switch (direction) {
            case 1: newX = x - 1; break; // Up
            case 2: newX = x + 1; break; // Down
            case 3: newY = y - 1; break; // Left
            case 4: newY = y + 1; break; // Right
            default: 
                std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
                continue;
        }

        if (isValidMove(board, newX, newY)) {
            movePlayer(board, (turn == 0) ? PLAYER1 : PLAYER2, newX, newY);
            if (turn == 0) {
                player1X = newX;
                player1Y = newY;
            } else {
                player2X = newX;
                player2Y = newY;
            }
            state = gameStatus(board);
        } else {
            std::cout << "Invalid move. Try again.\n";
        }

        turn = (turn + 1) % 2; // Switch turn
    }

    // End of game
    printBoard(board);
    if (state == GameState::PLAYER1_WINS) {
        std::cout << "Player 1 wins!\n";
    } else if (state == GameState::PLAYER2_WINS) {
        std::cout << "Player 2 wins!\n";
    } else {
        std::cout << "Game is a draw.\n";
    }

    return 0;
}

// Function definitions

void makeBoard(std::vector<std::vector<char>>& board) {
    // Clear the board and set up player starting positions
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    board[0][0] = PLAYER1; // Player 1 starts at (0, 0)
    board[BOARD_SIZE - 1][0] = PLAYER2; // Player 2 starts at (BOARD_SIZE-1, 0)
}

void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "\nBoard:\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool isValidMove(const std::vector<std::vector<char>>& board, int x, int y) {
    // Check if the move is within bounds and the space is not an obstacle
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        std::cout << "Move out of bounds. Try again.\n";
        return false;
    }
    if (board[x][y] == OBSTACLE) {
        std::cout << "Move blocked by obstacle. Try again.\n";
        return false;
    }
    return true;
}

GameState gameStatus(const std::vector<std::vector<char>>& board) {
    // Check if any player has reached the far-right column (win condition)
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][BOARD_SIZE - 1] == PLAYER1) {
            return GameState::PLAYER1_WINS;
        }
        if (board[i][BOARD_SIZE - 1] == PLAYER2) {
            return GameState::PLAYER2_WINS;
        }
    }
    return GameState::ONGOING;
}

void movePlayer(std::vector<std::vector<char>>& board, char player, int newX, int newY) {
    // Find the current position of the player and move it
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                board[i][j] = EMPTY;
                board[newX][newY] = player;
                return;
            }
        }
    }
}

void placeObstacles(std::vector<std::vector<char>>& board) {
    // Place a few obstacles randomly on the board
    for (int i = 0; i < 5; i++) { // Place 5 obstacles
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] == EMPTY) {
            board[x][y] = OBSTACLE;
        } else {
            i--; // Retry if the space is not empty
        }
    }
}
