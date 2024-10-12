#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#define WIDTH 20
#define HEIGHT 10

// Move cursor to a specific position in the terminal
void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

// Hide the cursor
void hide_cursor() {
    printf("\033[?25l");
}

// Show the cursor
void show_cursor() {
    printf("\033[?25h");
}

// Set terminal to non-blocking input
void enable_non_blocking_input() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;  // Disable canonical mode
    t.c_lflag &= ~ECHO;    // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// Restore terminal to blocking input
void disable_non_blocking_input() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;  // Enable canonical mode
    t.c_lflag |= ECHO;    // Enable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// Check if a key has been pressed
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Get a single character input (non-blocking)
int getch() {
    return getchar();
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

    const double frameDelay = 0.35;  // Target frame time (100 ms = 10 FPS)

    // Hide cursor and enable non-blocking input for smoother gameplay
    hide_cursor();
    enable_non_blocking_input();

    while (running) {
        // Handle input (non-blocking)
        if (kbhit()) {  // Check if a key is pressed
            char ch = getch();  // Get the pressed key
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

        // If movement has started, move the character
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

        // Sleep to control frame rate (100 ms per frame)
        usleep((useconds_t)(frameDelay * 1000000));
    }

    // Show cursor and disable non-blocking input before exiting
    show_cursor();
    disable_non_blocking_input();

    return 0;
}
