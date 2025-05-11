# Project 04 – Battleship

## 🕹️ Description

This is a two-player Battleship game built using C++ and SDL2. Each player takes turns trying to sink the other’s ships on a 6x6 grid. The game tracks hits, misses, and win conditions. It runs in a single window, handles mouse input, and can be restarted from inside the game. Ships are placed randomly at the start. Each player sees only their own board and shot history — no cross-contamination between turns.

## 🎮 Controls

- Click anywhere on the **right grid** ("Your Shots") to fire a shot
- Press **R** to reset the game
- Press **Esc** to quit

## 🧪 Screenshot

![Screenshot](screenshot.png)

## ✨ Extra Features

- Player-specific color themes for clarity
- Ships marked in white for visibility
- Accurate input targeting with synchronized rendering
- Turn banner that reads “Battleship — Player One/Two”
- All grid layout and sizing controlled via a centralized config file
