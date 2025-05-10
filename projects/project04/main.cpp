#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>
#include "game.h"
#include "GameConfig.h"

int getCellIndex(int mouseX, int mouseY, int boardStartX, int boardStartY) {
    int col = (mouseX - boardStartX) / CELL_SIZE;
    int row = (mouseY - boardStartY) / CELL_SIZE;
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE)
        return row * GRID_SIZE + col;
    return -1;
}

void drawText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = { x, y, surface->w, surface->h };
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    SDL_DestroyTexture(texture);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    TTF_Font* fontLarge = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 42);
    TTF_Font* fontSmall = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24);
    if (!fontLarge || !fontSmall) {
        std::cerr << "Font load error: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Project04 – Battleship",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed\n";
        TTF_CloseFont(fontLarge);
        TTF_CloseFont(fontSmall);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    std::unique_ptr<BattleshipGame> game = std::make_unique<BattleshipGame>();

    bool running = true;
    bool clickCooldown = false;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                else if (e.key.keysym.sym == SDLK_r) {
                    game = std::make_unique<BattleshipGame>();
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && !clickCooldown) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int move = getCellIndex(x, y, RIGHT_GRID_X, BOARD_OFFSET_Y);
                if (move != -1 && game->status() == BattleshipGame::ONGOING) {
                    game->play(move);
                }
                clickCooldown = true;
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                clickCooldown = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        game->draw(renderer);

        // Turn banner
        std::string banner = "Battleship -- Player " + std::to_string(game->getCurrentPlayer() + 1);
        drawText(renderer, fontLarge, banner, 20, 10);

        // Labels
        int labelY = BOARD_OFFSET_Y + GRID_SIZE * CELL_SIZE + 10;
        drawText(renderer, fontSmall, "Your Ships", LEFT_GRID_X, labelY);
        drawText(renderer, fontSmall, "Your Shots", RIGHT_GRID_X, labelY);

        // Endgame messages
        if (game->status() == BattleshipGame::PLAYER1_WINS) {
            drawText(renderer, fontLarge, "Player 1 Wins!", 200, SCREEN_HEIGHT - 110);
        }
        else if (game->status() == BattleshipGame::PLAYER2_WINS) {
            drawText(renderer, fontLarge, "Player 2 Wins!", 200, SCREEN_HEIGHT - 110);
        }

        // Instructions
        drawText(renderer, fontSmall, "Click on the right grid to fire.", 100, SCREEN_HEIGHT - 60);
        drawText(renderer, fontSmall, "Press R to restart. Press Esc to quit.", 100, SCREEN_HEIGHT - 30);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(fontLarge);
    TTF_CloseFont(fontSmall);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
