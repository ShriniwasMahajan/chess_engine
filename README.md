# C++ Chess Engine with SFML and GPU Acceleration

This project implements a chess engine built with C++ and the SFML library. Players can compete against a computer opponent powered by a minimax algorithm with alpha-beta pruning for efficient move selection.

The AI opponent evaluates the board using a minimax algorithm with alpha-beta pruning. Each piece has a different point value based on its importance and position on the board. For example, queens are worth more than pawns, and pieces in central squares are generally more valuable than those on the edge. This evaluation helps the AI choose the move that leads to the most favorable outcome

![Initial chessboard setup](https://github.com/ShriniwasMahajan/chess_engine/assets/85168586/4c38cef0-15b6-4e84-afb9-b15af8d54421)

## Key Features:

### Visually appealing: 
- Chessboard and pieces rendered with SFML

### Intuitive controls: 
- Drag and drop pieces for smooth gameplay
### User-friendly features:
- Undo move with backspace key
- Restart game with 'r' key
### Strategic AI: 
- Uses minimax with alpha-beta pruning for strategic play
### Smooth animations: 
- Enhanced user experience with fluid animations
### Human vs. AI: 
- Play as white against the computer as black

![Midway snapshot of a game](https://github.com/ShriniwasMahajan/chess_engine/assets/85168586/8dd1b8fb-0091-40a0-a8bd-1ea44e442b85)

## Target Audience:

- Chess enthusiasts who enjoy a challenge
- Programmers interested in game development and AI

## Getting Started:

### Prerequisites:
- C++ compiler (e.g., GCC, Clang)
- SFML library (https://www.sfml-dev.org/download.php)
- A graphics card that supports CUDA or OpenCL (optional, for GPU acceleration)

### Usage:
The game uses a drag-and-drop interface for selecting and moving pieces. Simply click and hold a piece, then drag it to the desired destination square and release. The AI opponent will automatically make its moves after your turn. Utilize the backspace key to undo your last move and the 'r' key to restart the game.
