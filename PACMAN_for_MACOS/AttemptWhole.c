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

//Function that creates the main map (this is making the alteration in the global map function)
void CreateMap(){
    system("cls"); //Clears Screen
    for (int i=0; i < Height; i++) {       //use of nested loop inorder for the walls to be made horizontally and vertically
        for (int j=0;j < Width; j++) {
            if(i == 0 || j == Width -1 || j == 0 || i == Height -1) {   //This creates the main boundary of the wall
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==1 || i==2 || i==3 || i==4) && (j == 29 || j == 30)){ //row 1 to row 4 walls
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==2 || i==3 || i==4)&& ((j>=2 && j <= 13)||(j>=16 && j<=27)||(j>=32 && j<=43)||(j>=46 && j<=57))){
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==6)&& ((j>=2 && j<=13) || (j>=16 && j<=18) || (j>=20 && j<=39)|| (j>=41 && j<=43)|| (j>=46 && j<=57))){ //row 6
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==7)&& ((j>=16 && j<=18) || (j>=29 && j<=30) || (j>=41 && j<=43))){ //row 7
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==8)&& ((j>=1 && j<=13) || (j>=16 && j<=26) || (j>=29 && j<=30)|| (j>=33 && j<=43)|| (j>=46 && j<=58))){ //row 8
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==9)&& ((j>=1 && j<=13) || (j>=16 && j<=18) || (j>=41 && j<=43)|| (j>=46 && j<=58))){ //row 9
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==10)&& ((j>=1 && j<=13) || (j>=16 && j<=18) || (j>=20 && j<=28)|| (j>=31 && j<=39)|| (j>=41 && j<=43)|| (j>=46 && j<=58))){ //row 10
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 11) &&((j>=20 && j<=22)||(j>=37 && j<=39))){
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 12) &&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=20 && j<=28)||(j>=31 && j<=33)||(j>=34 && j<=39)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 12
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 13) &&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=41 && j<=43)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 13
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 14)&&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=20 && j<=22)||(j>=23  && j<=39)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 14
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 15)&&((j==29 || j ==30))){ //row 15
                map[i][j] = Wall;
                printf("%c", map[i][j]);   
            }else if ((i==16)&& ((j>=2 && j<= 13) || (j>=16 && j<=26) || (j>=29 && j<= 30) || (j>=33 && j<= 43) || (j>=46 && j<=57))) { //row 16
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==17)&& ((j>=8 && j<= 13) || (j>=46 && j<=51))) { //row 17
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==18)&& ((j>=1 && j<= 6) || (j>=8 && j<=13)|| (j>=16 && j<=18)|| (j>=20 && j<=39) || (j>=41 && j<=43) || (j>=46 && j<=51) || (j>=53 && j<=58))) { //row 18
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==19)&& ((j>=16 && j<= 18) || (j>=29 && j<=30)|| (j>=41 && j<=43))) { //row 19
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==20)&& ((j>=2 && j<= 26) || (j>=29 && j<=30)|| (j>=33 && j<=57))) { //row 20
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==21)&& ((j>=2 && j<= 10) || (j>=28 && j<=31)|| (j>=49 && j<=57))) { //row 21
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }
            else if((i==22)&&((j>=2&&j<=7)||(j>=11&&j<=26)||(j>=33&&j<=54))){ //row 22
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if((i == 23)&&((j>=2&&j<=9)||(j>=11&&j<=15)||(j>=17&&j<=26)||(j>=33&&j<=57))){ //row 23
                map[i][j] = Wall;
                printf("%c", map[i][j]);                
            }else if((i == 24)&&(j>=28&&j<=31)){ //row 24
                map[i][j] = Wall;
                printf("%c", map[i][j]); 
            }else if (i == Px && j == Py) {
                map[i][j] = Pacman;
                printf("%c", map[i][j]);
            }else if ((map[i][j] != Pacman) && (map[i][j] != Wall)) {
                map[i][j] = Coins;
                printf("%c", map[i][j]);
                Coin = Coin + 1;
            }
        }printf("\n"); //To move to next line
    }
    printf("Score: %d\n", Score); 
}

//Draw Map it redraws map after each movement of the character
void DrawMap() {
    system("clear");  // Clear screen before each redraw
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            printf("%c", map[i][j]);  // Print current map state
        }
        printf("\n");
    }
    printf("Score: %d\n", Score);  // Display current score
}

// Function to calculate and display the elapsed time
void DisplayTime() {
    time_t currentTime = time(NULL);  // Get the current time
    int elapsedTime = difftime(currentTime, startTime); // Calculate elapsed time in seconds
    printf("Time Elapsed: %d seconds\n", elapsedTime);
}

// Function to move the player based on input direction
void move(int move_x, int move_y) {
    int newX = Px + move_x;
    int newY = Py + move_y;

    if (newX >= 0 && newX < Height && newY >= 0 && newY < Width && map[newX][newY] != Wall) {
        if (map[newX][newY] == Coins) {
            Score = Score + 1;  // Increment score when collecting a coin
            Coin = Coin - 1;    //Decrement Coins Quantity
            if (Coin == 0){     //If all the coins are finished than the game is complete
                result = 1;
                return;
            }
        }
        map[Px][Py] = Empty;  // Clear Pacman’s previous position
        Px = newX;             // Update Pacman's position x coordinate
        Py = newY;             // Update Pacman's position y coordinates
        map[Px][Py] = Pacman;  // Place Pacman at the new position
    }
}

int GameLoop(){
    startTime = time(NULL);
    char pf;
    while (1) {
            DrawMap();
            DisplayTime();
            if (result == 1) { 
                // Clear screen 
                system("cls"); 
                printf("You Win! \n Your Score: %d\n", Score); 
                return 1; 
            } 
            pf = getch();
            // Move based on user input
            switch (pf) { 
                case 'W':
                    move(-1, 0); // Move up
                    break;
                case 'S':
                    move(1, 0); // Move down
                    break;
                case 'A':
                    move(0, -1); // Move left
                    break;
                case 'D':
                    move(0, 1); // Move right
                    break;
                case 'Q':
                    printf("Game Over! Your Score: %d\n", Score);
                    return 0;
                default:
                    break;
            }
        // Delay for a moment to slow down the loop
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
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
