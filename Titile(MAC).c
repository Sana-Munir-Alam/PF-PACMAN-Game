#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Function to get a single character input without waiting for Enter
char getch() {
    char ch;
    struct termios oldt, newt; //These are structures that hold the terminal settings. We need two variables: oldt to store the original settings so that we can restore them later, and newt to modify the settings temporarily.

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt); //This function call retrieves the current settings of the terminal (associated with STDIN_FILENO, which represents standard input) and stores them in the oldt structure. This allows us to save the current terminal configuration for later restoration.
    newt = oldt; //This copies the current terminal settings (oldt) to the newt structure so that we can modify them without affecting the original settings.
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo. ICANON: Canonical mode is responsible for line-buffered input, which means input is not sent to the program until the user presses Enter. By disabling this (~ICANON), the program can capture each character as it's typed, without waiting for Enter. ECHO: This flag causes input to be echoed back to the terminal (i.e., when you type, it shows up on the screen). By disabling this (~ECHO), characters typed by the user won’t be displayed on the terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // This function applies the modified terminal settings (newt) immediately (TCSANOW). Input will be captured character by character

    ch = getchar(); // Read a single character

    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //After capturing the character, this line restores the terminal to its original settings (oldt).
    
    return ch; // Return the character read
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
    printf("\n\n");
    printf("To Start Game Press Y\n"); // Display prompt to start the game

    // Wait for user input
    pf = getch(); // Call the custom getch function
    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }
    
    // If 'Y' or 'y' is pressed, continue the game
    printf("Game Starting...\n"); // Indicate the game has started
    return 0;
}
