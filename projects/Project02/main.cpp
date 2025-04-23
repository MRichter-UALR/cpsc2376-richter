#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include "game.h"

// reads a line; returns move index or -1 for surrender
int getMove() {
    std::string line;
    while (true) {
        std::cout << "Enter row and column (0-" << BattleshipGame::SIZE - 1
            << ") or 'quit' to surrender: ";
        std::getline(std::cin, line);
        if (line == "quit") {
            return -1;
        }
        std::istringstream iss(line);
        int r, c;
        if (iss >> r >> c) {
            if (r >= 0 && r < BattleshipGame::SIZE
                && c >= 0 && c < BattleshipGame::SIZE) {
                return r * BattleshipGame::SIZE + c;
            }
        }
        std::cout << "Invalid. Enter two numbers between 0 and "
            << BattleshipGame::SIZE - 1 << " or 'quit'.\n";
    }
}

// prompt to play again
bool playAgainPrompt() {
    std::string line;
    std::cout << "Play again? (y/n): ";
    std::getline(std::cin, line);
    return (!line.empty() && (line[0] == 'y' || line[0] == 'Y'));
}

int main() {
    do {
        BattleshipGame game;
        bool surrendered = false;
        int  surrenderWinner = -1;

        while (game.status() == BattleshipGame::ONGOING && !surrendered) {
            std::cout << game << "\n";
            int mv = getMove();
            if (mv == -1) {
                surrendered = true;
                surrenderWinner = 1 - game.getCurrentPlayer();
                break;
            }
            auto res = game.play(mv);
            if (res == BattleshipGame::INVALID) {
                std::cout << "-- Already tried or out of range --\n";
                continue;
            }
            if (res == BattleshipGame::HIT_SHOT)  std::cout << "-- HIT! --\n";
            if (res == BattleshipGame::MISS_SHOT) std::cout << "-- MISS! --\n";
            if (res == BattleshipGame::SINK_SHOT) std::cout << "-- You sank the last ship! --\n";

            std::cout << "Press Enter to end turn...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

        // final boards & result
        std::cout << game << "\n";
        if (surrendered) {
            std::cout << "Player " << (surrenderWinner + 1)
                << " wins by surrender!\n";
        }
        else {
            std::cout << (game.status() == BattleshipGame::PLAYER1_WINS
                ? "Player 1 wins!\n"
                : "Player 2 wins!\n");
        }

    } while (playAgainPrompt());

    return 0;
}
