# **PAC-MAN**

## **Description**
This project is an enhanced console-based implementation of the classic **PAC-MAN** game, complete with exciting features such as player account management, colored output, and leaderboard functionality. It offers an immersive gaming experience.

---

## **Features**

### **Gameplay Mechanics**
- **PAC-MAN and Ghosts Movement**:
  - **PAC-MAN** moves continuously within the maze.
  - Four ghosts:
    - Two move **horizontally**.
    - Two move **vertically**.
- **Coins** (`.`) and **Power Coins** (`@`):
  - Collect coins to score points; they disappear upon collection.
  - Power coins allow **PAC-MAN** to eat ghosts temporarily for **5 seconds**.
- Functional maze with walls (`|`) to navigate.

### **Progress Tracking**
- **Timers**:
  - Displays elapsed time since the game started.
- **Score Tracking**:
  - Tracks the current player score.
  - Displays the highest score achieved across all sessions.

### **Player Controls**
- Use **W, A, S, D** (both uppercase and lowercase) to move **PAC-MAN**:
  - `W` - Up
  - `A` - Left
  - `S` - Down
  - `D` - Right
- Invalid moves are ignored, ensuring smooth gameplay.

### **Lives and Game Over Conditions**
- **PAC-MAN** starts with **three lives**.
- Game ends when:
  - All lives are lost.
  - All coins are collected.
- End-of-game options:
  - **New Game**: Resets all scores and progress.
  - **Play Again**: Retains the high score while resetting other states.

---

## **Enhanced Features**

### **Visual and Audio Feedback**
- Colored output enhances the visual appeal.
- Audio feedback accompanies specific events.

### **Account Management**
- Players create an account before starting the game, with credentials securely stored in a file.
- Login is required to play, ensuring scores are associated with the correct player.

### **Score and Leaderboard Management**
- Saves the player’s score if it surpasses their previous high score.
- Allows viewing of the leaderboard to see all players' high scores.

---

## **How to Play**

### **Starting the Game**
1. Run the program.
2. Create an account or log in with your credentials.
3. Follow on-screen instructions to begin.

### **In-Game Controls**
- Move **PAC-MAN** using:
  - `W` - Up
  - `A` - Left
  - `S` - Down
  - `D` - Right

### **Winning and Losing**
- **Win**: Collect all coins.
- **Lose**: Lose all lives.

---

## **Tech Stack**

This project is built using the following technologies:

### **Programming Language**
- **C**: The primary language used for game logic, handling input/output, and managing gameplay flow.

### **Libraries and Tools**
- **Standard Libraries**:
  - `<stdio.h>`: Used for standard input and output operations.
  - `<stdlib.h>`: Provides utility functions for memory management and conversions.
  - `<conio.h>`: Enables real-time keyboard input handling.
  - `<windows.h>`: Used for terminal control and manipulating the console window.
  - `<stdbool.h>`: Allows usage of Boolean data types and operations.
  - `<time.h>`: Provides time functions for tracking elapsed game time.
  - `<string.h>`: Provides string functions for string related function.

### **File Management**
- **File Handling**: Used to store player accounts, scores, and the leaderboard to ensure persistence across sessions.
---

Enjoy the game!! Good Luck!
