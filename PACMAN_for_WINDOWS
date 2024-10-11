#include <stdio.h>
#include <conio.h> // Include conio.h for getch() in Windows

void map(){
	#define Height 26
    #define Width 60
    #define Wall '#'
    #define Empty '.'
	char map[Height][Width];
	for (int i=0; i < Height; i++) {
    	for (int j=0;j < Width; j++) {
        	if(i == 0 || j == Width -1 || j == 0 || i == Height -1) {
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else{
                map[i][j] = Empty;
                printf("%c", map[i][j]);
            }
        }printf("\n");
  	}
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

    // Wait for user input using getch from conio.h (for Windows)
    pf = _getch(); // _getch() gets a single character without waiting for Enter

    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }
    
    // If 'Y' or 'y' is pressed, continue the game
    printf("Game Starting...\n"); // Indicate the game has started

    map();
    return 0;
}
