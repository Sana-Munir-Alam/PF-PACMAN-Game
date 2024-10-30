// Section 0: These 7 functions below are handling the cursor, the terminal setting, and to get an input without the need of pressing enter or displaying it. (This is used to have a smoother game flow experience)

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
    t.c_lflag &= ~ICANON;  // Disable canonical mode, ICANON: Canonical mode is responsible for line-buffered input, which means input is not sent to the program until the user presses Enter.
    t.c_lflag &= ~ECHO;    // Disable echo, ECHO: This flag causes input to be echoed back to the terminal (i.e., when you type, it shows up on the screen).
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

// Get a single character input (non-blocking)
int getch() {
    return getchar();
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
