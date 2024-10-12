#include <stdio.h>
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep(), SetConsoleCursorPosition(), etc.

#define WIDTH 20
#define HEIGHT 10

// Move cursor to a specific position in the console
void move_cursor(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide the cursor for smoother rendering
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Show the cursor after the game ends
void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = TRUE;
    cursorInfo.dwSize = 1;
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
}

// Main game logic
int main() {
    int x = WIDTH / 2;  // Initial x position of the character
    int y = HEIGHT / 2; // Initial y position of the character

    boolean running = TRUE;

    LARGE_INTEGER frequency;        // Ticks per second
    LARGE_INTEGER frameStart, frameEnd; // Start and end ticks of each frame
    double frameDuration;           // Duration of each frame in seconds
    const double frameDelay = 0.1;  // Target frame time (100 ms = 10 FPS)

    // Get the frequency of the performance counter
    QueryPerformanceFrequency(&frequency);

    // Hide cursor for smoother gameplay
    hide_cursor();

    while (running) {
        // Get the starting time for the frame
        QueryPerformanceCounter(&frameStart);

        // Handle input (non-blocking)
        if (_kbhit()) {  // Check if a key is pressed
            char ch = _getch();  // Get the pressed key
            switch (ch) {
                case 'w': // Move up
                    if (y > 1) y--;
                    break;
                case 's': // Move down
                    if (y < HEIGHT - 2) y++;
                    break;
                case 'a': // Move left
                    if (x > 1) x--;
                    break;
                case 'd': // Move right
                    if (x < WIDTH - 2) x++;
                    break;
                case 'q': // Quit the game
                    running = FALSE;
                    break;
            }
        }

        // Render the game
        render(x, y);

        // Get the ending time for the frame
        QueryPerformanceCounter(&frameEnd);

        // Calculate the frame duration in seconds
        frameDuration = (double)(frameEnd.QuadPart - frameStart.QuadPart) / frequency.QuadPart;

        // Sleep for the remaining time to control frame rate (if needed)
        if (frameDuration < frameDelay) {
            Sleep((DWORD)((frameDelay - frameDuration) * 1000));
        }
    }

    // Show cursor again before exiting
    show_cursor();

    return 0;
}
