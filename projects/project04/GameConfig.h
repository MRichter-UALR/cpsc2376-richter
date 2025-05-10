#pragma once

// Grid and layout constants
constexpr int CELL_SIZE = 50;
constexpr int GRID_SIZE = 6;
constexpr int BOARD_GAP = 20;
constexpr int BOARD_OFFSET_Y = 100;

// Grid pixel dimensions
constexpr int GRID_WIDTH = GRID_SIZE * CELL_SIZE;
constexpr int TOTAL_WIDTH = GRID_WIDTH * 2 + BOARD_GAP;
constexpr int SCREEN_WIDTH = 900;
constexpr int SCREEN_HEIGHT = GRID_SIZE * CELL_SIZE + BOARD_OFFSET_Y + 220;

// Shared offsets
constexpr int BOARD_OFFSET_X = (SCREEN_WIDTH - TOTAL_WIDTH) / 2;
constexpr int LEFT_GRID_X = BOARD_OFFSET_X;
constexpr int RIGHT_GRID_X = BOARD_OFFSET_X + GRID_WIDTH + BOARD_GAP;
