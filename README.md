# C++ Chess Engine

## Description
This is a C++ Chess Engine with an emphasis on user interaction and experience. The engine is designed to play and analyze chess games, featuring smooth animations, an intuitive GUI, and user-friendly controls.

## Features
- Full chess move generation and validation
- Drag and drop functionality for making moves
- Smooth animations for piece movement
- User-friendly graphical interface
- Backspace to undo the last move
- Press 'R' to restart the game
- Endgame recognition and handling
- Implementation of key algorithms for chess AI, including:
  - Minimax algorithm
  - Alpha-beta pruning
  - Evaluation function to assess board positions

![Initial Board Setup](https://github.com/user-attachments/assets/fcebc9b9-07af-45d6-b841-c91718c42b8a)

## Usage
### Playing a Game
Once you have compiled the engine, start the game by running the executable. The graphical interface will launch, allowing you to drag and drop pieces to make your moves.
### Controls
- Drag and Drop: Use your mouse to drag and drop pieces.
- Backspace: Press backspace to undo your last move.
- Restart: Press 'R' to restart the game.

## Example
Here's an example of how to start the engine and interact with the GUI:
```$ ./chess_engine```

Once the game starts, use your mouse to drag and drop pieces to make your moves. If you make a mistake, press backspace to undo the last move, or press 'R' to restart the game.

## Code Structure
The code is organized into the following main components:
1. **main.cpp**: Handles the main game loop, including user inputs, rendering, and overall program flow.
2. **ai.cpp**: Implements the chess AI with algorithms like Minimax and Alpha-Beta Pruning. Also includes functions for evaluating the board state and detecting endgame scenarios.
3. **pieces.cpp**: Defines the behavior and movement of individual chess pieces, including the generation of possible moves for each piece.
4. **board.cpp**: Manages the chessboard's state, including piece positions and move validation. Also includes utility functions for converting positions and handling game restart.
5. **game.cpp**: Handles the game logic, including move execution, drawing the board, undoing moves, and checking for endgame conditions.

![Midway through a game](https://github.com/user-attachments/assets/39e560cc-fb57-491c-807e-7a0bc1639804)

## Global Variables and Functions
### board.cpp:
- board[8][8]: Represents the chessboard with pieces indexed by their position.
- pieceVals[32]: Stores values associated with the pieces.
- Various arrays for piece positions (e.g., bRookPos, bKnightPos).
- Functions for loading positions, converting between chess notation and coordinates, and restarting the game.
### game.cpp:
- gameOver: Boolean flag indicating whether the game is over.
- Functions for drawing the board, making moves, undoing moves, and handling the computer's move.
### ai.cpp:
- endGame: Boolean flag for endgame detection.
- Functions for evaluating the board, checking game over conditions, and implementing the minimax algorithm.
### pieces.cpp:
- f[32]: Sprite array for the chess pieces.
- defeated: Vector for storing defeated pieces.
- Functions for generating moves for each piece type.
