# 12 Beads Game – C++ Console Implementation

A console-based version of the **12 Beads Game**, implemented using 2D arrays in C++.  
The project includes full board setup, move legality checks, bead capturing, and victory conditions.

## 🎮 Game Description
The 12 Beads game is played on a square-shaped board with 16 mini-boxes and a large diamond crossing through them.  
Each mini-box has 4 positions at its corners, forming **25 possible slots** where pawns can be placed.

- Each player has **12 beads** (Player 1 = Red, Player 2 = Green).  
- Players take turns moving one bead at a time (first move decided by coin toss).  
- Beads can move vertically, horizontally, or diagonally along board lines.  
- A bead can **capture** an opponent's bead by jumping over it into an empty position.  
- The goal is to eliminate all of the opponent’s beads.

## ✅ Features Implemented
- **Board Printing** (16 mini-box layout with 25 slots).  
- **Game Flow** – turn-based play (Player 1 → Player 2).  
- **Move Legality** – prevent illegal moves (no stacking, no illegal diagonals).  
- **Capturing** – vertical, horizontal, and diagonal jumps to capture opponent beads.  
- **Restrictions** – prevent self-jumps and invalid diagonals.  
- **Win Condition** – detect when all opponent beads are eliminated.

## 🛠️ Tech Stack
- Language: **C++**
- Data Structures: 2D arrays
- Console utilities: cursor movement, highlighting, input

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/hamxaShaukat/12-beads.git
