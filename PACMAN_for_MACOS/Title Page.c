//This code is only the title page and Map (every addition in our code will be added here)
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define Height 26   //This defines the height of the maze (rows)
#define Width 60    //This defines the width of the maze (columns)
#define Wall '#'    //This defines the wall material
#define Empty ' '   //This defines the empty space (where pacman and the ghostgang will roam about)
#define Coins '.'
#define Pacman 'C'
#define GhostGang 'X'

//global variable
int Score = 0;
int Coin = 0;
int result = 0;
int Px = 17, Py = 29;
char map[Height][Width]; //2D Array for defining the height and width of the maze
time_t startTime; // Variable to store the start time


// Function to get a single character input without waiting for Enter
char getch() {
    char buf = 0;  // Declare a variable to store the character read from input.
    struct termios old = {0};  // Declare a struct to hold the current terminal settings.
    
    // Retrieve the current terminal settings and store them in 'old'
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");     //This function call retrieves the current settings of the terminal (associated with STDIN_FILENO, which represents standard input and stores them in the oldt structure. This allows us to save the current terminal configuration for later restoration.

    // Modify the terminal settings stored in 'old' to disable canonical mode and echo.
    old.c_lflag &= ~ICANON;  // ICANON: Canonical mode is responsible for line-buffered input, which means input is not sent to the program until the user presses Enter. By disabling this (~ICANON), the program can capture each character as it's typed, without waiting for Enter.
    old.c_lflag &= ~ECHO;  // ECHO: This flag causes input to be echoed back to the terminal (i.e., when you type, it shows up on the screen). By disabling this (~ECHO), characters typed by the user won’t be displayed on the terminal.

    // Set minimum number of characters for non-canonical read to 1 and set timeout to 0.
    old.c_cc[VMIN] = 1;  // 'VMIN = 1' ensures the program will wait for at least one character to be input before proceeding.
    old.c_cc[VTIME] = 0;  // 'VTIME = 0' sets no timeout for input. It ensures the program waits indefinitely for input, which is ideal for capturing real-time keystrokes.

    // Apply the new terminal settings (with canonical mode and echo disabled) immediately.
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");  // Apply changes to terminal settings using 'TCSANOW', which makes the changes take effect immediately.
    // Read one character from standard input (file descriptor 0) and store it in 'buf'.
    // 'read(0, &buf, 1)' reads 1 byte (character) from STDIN. This is a low-level system call that directly interacts with input streams.
    if (read(0, &buf, 1) < 0) perror("read()");  // If reading fails, print an error message.
    // Restore the original terminal settings (enable canonical mode and echo).
    old.c_lflag |= ICANON;  // Re-enable canonical mode, meaning input will be line-buffered again (user has to press Enter to send input).
    old.c_lflag |= ECHO;  // Re-enable echo, meaning typed characters will now be displayed on the terminal.
    // Apply the restored terminal settings after all pending output has been written.
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");  // Use 'TCSADRAIN' to wait until all output is written before restoring the settings, ensuring smooth terminal behavior.
    return buf;
}

int main() {
    char pf;
    printf(" ____   _    ____ __  __    _    _   _\n");
    printf("|  _ \\ / \\  / ___|  \\/  |  / \\  | \\ | |\n");
    printf("| |_) / _ \\| |   | |\\/| | / _ \\ |  \\| |\n");
    printf("|  __/ ___ | |___| |  | |/ ___ \\| |\\  |\n");
    printf("|_| /_/   \\_\\____|_|  |_/_/   \\_|_| \\_|\n");
    printf("\n\n\n");
    printf("INSTRUCTIONS:\n");
    printf("To Move Up Press W\n");
    printf("To Move Down Press S\n");
    printf("To Move Right Press D\n");
    printf("To Move Left Press A\n");
    printf("To Quit Game Press Q\n");
    printf("\n\n");
    printf("To Start Game Press Y\n"); // Display prompt to start the game

    // Wait for user input using getch from conio.h (for Windows)
    pf = getch(); // _getch() gets a single character without waiting for Enter

    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }
    // If 'Y' or 'y' is pressed, continue the game
    printf("Game Starting...\n"); // Indicate the game has started
    CreateMap();
    system("cls"); 
    GameLoop();
    return 0;
}
