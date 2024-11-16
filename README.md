# **PAC-MAN Game Simulation**

## **Description**
This project is a console-based implementation of the classic **PAC-MAN** game with added features and functionality. The game is designed to provide an engaging gaming experience.

---

## **Features**

### **PAC-MAN and Ghosts Movement**
- **PAC-MAN** moves continuously within the maze.
- Four ghosts:
  - Two ghosts move **horizontally**.
  - Two ghosts move **vertically**.

### **Interactive Gameplay**
- Collect coins (`.`) to score points. Coins are replaced with empty spaces upon collection.
- Power coins (`@`) allow **PAC-MAN** to eat ghosts for 5 seconds.

### **Game Progress Tracking**
- Displays elapsed time since the game started.
- Tracks:
  - **Current player score**.
  - **Highest score across sessions**.

### **Player Controls**
- Use **W, A, S, D** (both uppercase and lowercase) to move **PAC-MAN**:
  - `W` - Up
  - `A` - Left
  - `S` - Down
  - `D` - Right
- Press **Q** to quit the game.

### **PAC-MAN Lives and Game Over Conditions**
- **PAC-MAN** starts with **three lives**.
- Game ends when:
  - All lives are lost.
  - All coins are collected.

### **Maze and Ghost Interaction**
- Fully functional maze with walls (`#`) to navigate.
- Collisions with ghosts result in losing a life (unless under the power coin effect).

### **Game End Options**
- **New Game**: Resets all scores and game state.
- **Play Again**: Retains the high score while resetting the rest.

---

## **What's Missing**
- **Sound Effects**: Adding sound effects for PAC-MAN's movements, ghost collisions, and power coin effects would enhance gameplay.

---

## **How to Play**

### **Start the Game**
1. Run the program.
2. Follow the on-screen instructions to begin.

### **Controls**
- Move **PAC-MAN** using:
  - `W` - Up
  - `A` - Left
  - `S` - Down
  - `D` - Right
- Quit anytime by pressing `Q`.

### **Objectives**
- **Collect all coins** in the maze.
- Avoid collisions with ghosts unless under the power coin effect.

### **Winning and Losing**
- **Win**: Collect all coins.
- **Lose**: Lose all lives.

---

## **Technologies Used**
- **Programming Language**: C
- **Libraries**:
  - `<stdio.h>` for input and output.
  - `<conio.h>` for real-time keyboard input handling.
  - `<windows.h>` for cursor and terminal control.
  - `<stdbool.h>` for Boolean operations.
  - `<time.h>` for time tracking.
