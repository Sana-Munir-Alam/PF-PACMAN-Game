#include <stdio.h>
#include <conio.h>  // For kbhit() and getch() on Windows
#include <windows.h> // For Sleep() on Windows
#include <stdbool.h>
#define WIDTH 20
#define HEIGHT 10

// Move cursor to a specific position in the terminal (Windows version)
void move_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide the cursor (Windows version)
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Show the cursor (Windows version)
void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE; // Show the cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Render the box and character
void render(int x, int y) {
    move_cursor(0, 0);  // Move cursor to the top left corner

    // Draw the box and character
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#");  // Boundary of the box
            } else if (i == y && j == x) {
                printf("@");  // The character
            } else {
                printf(" ");  // Empty space
            }
        }
        printf("\n");
    }
    fflush(stdout);  // Ensure everything is printed immediately
}

// Main game logic
int main() {
    int x = WIDTH / 2;  // Initial x position of the character
    int y = HEIGHT / 2; // Initial y position of the character
    int dx = 0;  // No movement initially
    int dy = 0;  // No movement initially

    bool running = true;
    bool movement_started = false; // Track if movement has started

    const double frameDelay = 0.25;  // Target frame time (350 ms per frame)

    // Hide cursor for smoother gameplay
    hide_cursor();

    while (running) {
        // Handle input (non-blocking)
        if (_kbhit()) {  // Check if a key is pressed
            char ch = _getch();  // Get the pressed key
            switch (ch) {
                case 'w': // Move up
                    dx = 0;
                    dy = -1;
                    movement_started = true;
                    break;
                case 's': // Move down
                    dx = 0;
                    dy = 1;
                    movement_started = true;
                    break;
                case 'a': // Move left
                    dx = -1;
                    dy = 0;
                    movement_started = true;
                    break;
                case 'd': // Move right
                    dx = 1;
                    dy = 0;
                    movement_started = true;
                    break;
                case 'q': // Quit the game
                    running = false;
                    break;
            }
        }

        // If movement has started, move the character continuously
        if (movement_started) {
            x += dx;
            y += dy;
        }

        // Keep the character within bounds
        if (x < 1) x = 1;
        if (x > WIDTH - 2) x = WIDTH - 2;
        if (y < 1) y = 1;
        if (y > HEIGHT - 2) y = HEIGHT - 2;

        // Render the game
        render(x, y);

        // Sleep to control frame rate (350 ms per frame)
        Sleep((DWORD)(frameDelay * 1000)); // Sleep takes milliseconds
    }

    // Show cursor before exiting
    show_cursor();

    return 0;
}
