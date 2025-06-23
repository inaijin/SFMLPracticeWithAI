# SFML Practice with AI

## Overview

This project was created as a practice exercise using the SFML (Simple and Fast Multimedia Library) for game development and incorporating basic AI concepts. It includes two separate projects:

1.  **Pacman:** A classic Pacman game with AI-controlled ghosts and Pacman (partially).
2.  **TicTacToe:** A simple Tic Tac Toe game with an AI opponent.

## Pacman

#### Description

This is an implementation of the classic Pacman game using SFML. The project focuses on:

*   SFML basics: window management, drawing shapes, handling input.
*   Game logic: Pacman and ghost movement, collision detection, scorekeeping (not fully implemented).
*   AI: Ghosts with basic Q-learning AI for decision-making.

#### File Structure

```
Pacman/
├── Blinky.cpp         # Blinky (Red Ghost) implementation
├── Blinky.h           # Blinky class definition
├── Clyde.cpp          # Clyde (Orange Ghost) implementation
├── Clyde.h            # Clyde class definition
├── Constants.h        # Game constants (screen size, object dimensions, etc.)
├── Game.cpp           # Main game logic
├── Game.h             # Game class definition
├── GameObject.cpp     # Base class for game objects
├── GameObject.h       # GameObject class definition
├── Ghost.cpp          # Ghost base class implementation
├── Ghost.h            # Ghost class definition
├── GhostAI.cpp        # Ghost AI (Q-learning) implementation
├── GhostAI.h          # GhostAI class definition
├── Grid.cpp           # Grid class implementation
├── Grid.h             # Grid class definition
├── Inky.cpp           # Inky (Cyan Ghost) implementation
├── Inky.h             # Inky class definition
├── Makefile           # Build configuration
├── Map.cpp            # Map loading and handling
├── Map.h              # Map class definition
├── Pacman.cpp         # Pacman implementation
├── Pacman.h           # Pacman class definition
├── Pinky.cpp          # Pinky (Magenta Ghost) implementation
├── Pinky.h            # Pinky class definition
├── Tile.cpp           # Tile implementation
├── Tile.h             # Tile class definition
├── main.cpp           # Entry point
└── weights/           # Directory containing Q-learning tables
    ├── blinky_q_table.txt
    ├── clyde_q_table.txt
    ├── inky_q_table.txt
    ├── pacman_q_table.txt
    └── pinky_q_table.txt
```

#### AI Implementation (Pacman Ghosts)

The ghosts in this Pacman implementation use a simple Q-learning algorithm to determine their movements. The `weights/` directory contains the Q-tables, which store the learned values for each state-action pair.

#### How to Run

1.  Make sure you have SFML installed and configured correctly.
2.  Navigate to the `Pacman/` directory.
3.  Run `make` to build the project.
4.  Execute the compiled binary: `bin/Pacman`.
5.  To make training faster press `F`.

## Tic Tac Toe

#### Description

A basic Tic Tac Toe game implemented using SFML with a simple AI opponent.

#### File Structure

```
TicTacToe/
├── ai.cpp    # AI logic
├── ai.h      # AI class definition
├── game.cpp  # Game logic
├── game.h    # Game class definition
├── main.cpp  # Entry point
├── Makefile  # Build configuration
└── fonts/    # Directory containing fonts
    └── arial.ttf
```

#### AI Implementation (Tic Tac Toe)

The AI opponent uses the minimax algorithm with alpha-beta pruning to determine the best move. The difficulty of the AI can be adjusted.

#### How to Run

1.  Make sure you have SFML installed.
2.  Navigate to the `TicTacToe/` directory.
3.  Run `make` to build the project.
4.  Execute the compiled binary: `bin/TicTacToe`.