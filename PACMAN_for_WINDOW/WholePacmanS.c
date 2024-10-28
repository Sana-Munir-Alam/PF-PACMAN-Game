//This code has continious movement/time/character movement/Coin collectio/coin watcher

#include <stdio.h>
#include <conio.h>  // For kbhit() and getch() on Windows
#include <windows.h> // For Sleep() on Windows
#include <stdbool.h>
#include <time.h>

#define Width 60
#define Height 26
#define Wall '#'
#define Pacman 'C'
#define Coins '.'
#define Empty ' '

//Global Variable
int Score = 0;


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

// Time Function
double GetElapsedTime(time_t StartTime) {
    return difftime(time(NULL), StartTime);
}

//Check if next position is wall
bool IsWall(int x, int y) {
    if(y == 0 || x == Width -1 || x == 0 || y == Height -1) {   //Thys creates the mayn boundary of the wall
        return true;
    }else if((y==1 || y==2 || y==3 || y==4) && (x == 29 || x == 30)){ //row 1 to row 4 walls                
        return true;
    }else if((y==2 || y==3 || y==4)&& ((x>=2 && x <= 13)||(x>=16 && x<=27)||(x>=32 && x<=43)||(x>=46 && x<=57))){                 
        return true;
    }else if((y==6)&& ((x>=2 && x<=13) || (x>=16 && x<=18) || (x>=20 && x<=39)|| (x>=41 && x<=43)|| (x>=46 && x<=57))){ //row 6                 
        return true;
    }else if((y==7)&& ((x>=16 && x<=18) || (x>=29 && x<=30) || (x>=41 && x<=43))){ //row 7                 
        return true;
    }else if((y==8)&& ((x>=1 && x<=13) || (x>=16 && x<=26) || (x>=29 && x<=30)|| (x>=33 && x<=43)|| (x>=46 && x<=58))){ //row 8                 
        return true;
    }else if((y==9)&& ((x>=1 && x<=13) || (x>=16 && x<=18) || (x>=41 && x<=43)|| (x>=46 && x<=58))){ //row 9
        return true;
    }else if((y==10)&& ((x>=1 && x<=13) || (x>=16 && x<=18) || (x>=20 && x<=28)|| (x>=31 && x<=39)|| (x>=41 && x<=43)|| (x>=46 && x<=58))){ //row 10 
        return true;
    }else if((y == 11) &&((x>=20 && x<=22)||(x>=37 && x<=39))){                
        return true;
    }else if((y == 12) &&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=20 && x<=28)||(x>=31 && x<=33)||(x>=34 && x<=39)||(x>=41 && x<=43)||(x>=46 && x<=58))){ //row 12                
        return true;
    }else if((y == 13) &&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=41 && x<=43)||(x>=41 && x<=43)||(x>=46 && x<=58))){ //row 13             
        return true;
    }else if((y == 14)&&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=20 && x<=22)||(x>=23  && x<=39)||(x>=41 && x<=43)||(x>=46 && x<=58))){ //row 14               
        return true;
    }else if((y == 15)&&((x==29 || x ==30))){ //row 15                 
        return true;   
    }else if ((y==16)&& ((x>=2 && x<= 13) || (x>=16 && x<=26) || (x>=29 && x<= 30) || (x>=33 && x<= 43) || (x>=46 && x<=57))) { //row 16                 
        return true;  
    }else if ((y==17)&& ((x>=8 && x<= 13) || (x>=46 && x<=51))) { //row 17                 
        return true;  
    }else if ((y==18)&& ((x>=1 && x<= 6) || (x>=8 && x<=13)|| (x>=16 && x<=18)|| (x>=20 && x<=39) || (x>=41 && x<=43) || (x>=46 && x<=51) || (x>=53 && x<=58))) { //row 18                 
        return true;  
    }else if ((y==19)&& ((x>=16 && x<= 18) || (x>=29 && x<=30)|| (x>=41 && x<=43))) { //row 19                
        return true;  
    }else if ((y==20)&& ((x>=2 && x<= 26) || (x>=29 && x<=30)|| (x>=33 && x<=57))) { //row 20                 
        return true;  
    }else if ((y==21)&& ((x>=2 && x<= 10) || (x>=28 && x<=31)|| (x>=49 && x<=57))) { //row 21                 
        return true;  
    }else if((y==22)&&((x>=2&&x<=7)||(x>=11&&x<=26)||(x>=33&&x<=54))){ //row 22                
        return true;  
    }else if((y == 23)&&((x>=2&&x<=9)||(x>=11&&x<=15)||(x>=17&&x<=26)||(x>=33&&x<=57))){ //row 23                
        return true;                
    }else if((y == 24)&&(x>=28&&x<=31)){ //row 24               
        return true; 
    }
    return false;
}

// Render the box and character
void Render(int x, int y, int Lives, int Score, double ElapsedTime, char map[Height][Width]) {
    move_cursor(0, 0);  // Move cursor to the top left corner
    // Draw the Maze and Characters
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (IsWall(j, i)) {
                printf("%c", Wall);
            } else if (i == y && j == x) {
                printf("%c", Pacman);  // The character
            } else if (map[i][j] == '.') {
                printf("%c", Coins);  // Coin
            } else {
                printf("%c", Empty);  // Empty space
            }
        }
        printf("\n");
    }
    printf("Lives: %d\n", Lives); // Display Remaining Lives
    printf("Score: %d\n", Score); // Display the Score
    printf("Time: %.0f seconds\n", ElapsedTime); // Display Elapsed Time
    fflush(stdout);  // Ensure everything is printed immediately
}

// Main game logic
int main() {
    int x = 29;  // Initial x position of Pacman
    int y = 17; // Initial y position of Pacman
    int dx = 0;  // No movement initially
    int dy = 0;  // No movement initially
    int Lives = 3;

    bool Stunned = false;
    bool Running = true;

    time_t StartTime = time(NULL);
    const double frameDelay = 0.15;  // Target frame time (350 ms per frame)
    
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
    char pf = _getch(); // _getch() gets a single character without waiting for Enter
    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }

    // Initializing Map with Coins and Pacman
    char map[Height][Width];
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
                if (i == 17 && j == 29){
                    map[i][j] = Pacman;
                }else{
                    map[i][j] = Coins;
                }   
        }
    }

    // Hide cursor for smoother gameplay
    hide_cursor();

    while (Running) {
        // Handle input (non-blocking)
        if (_kbhit()) {  // Check if a key is pressed
            char ch = _getch();  // Get the pressed key
            if (Stunned) {  //True if Pacman collided with GhostGang this will reset Pacman to original position
                Stunned = false;
                x = 29; //Original x coordinate
                y = 17; //Original y coordinate
            } else {
                switch (ch) {
                    case 'w': case 'W': // Move up
                        dx = 0;
                        dy = -1;
                        break;
                    case 's': case 'S': // Move down
                        dx = 0;
                        dy = 1;
                        break;
                    case 'a': case 'A': // Move left
                        dx = -1;
                        dy = 0;
                        break;
                    case 'd': case 'D': // Move right
                        dx = 1;
                        dy = 0;
                        break;
                    case 'q': case 'Q': // Quit the game
                        Running = false;
                        break;
                }
            }
        }

        // This checks if Pacman has not come in contact with Ghost Gang
        if (!Stunned) {
            int newX = x + dx;
            int newY = y + dy;

            if (IsWall(newX, newY)) {
                continue;
            } else if (newX == 17 && newY == 10) {
                Lives = Lives - 1;
                Stunned = true;
                printf("Ouch! You hit a demon! Lives left: %d\n", Lives);
                x = Width / 2;
                y = Height / 2;
            } else {
                x = newX;
                y = newY;

                // Check for coin collection
                if (map[y][x] == Coins) {
                    map[y][x] = Empty;  // Replace coin with empty space
                    Score = Score + 1;  // Increment score
                }
            }
        }

        double ElapsedTime = GetElapsedTime(StartTime);
        
        // Render the game
        Render(x, y, Lives, Score, ElapsedTime, map);

        //Check if Pacman has any remaining life if no 'Game Over'
        if (Lives <= 0) {
            printf("Game Over! You have no lives left.\n");
            Running = false;
        }

        // Sleep to control frame rate (350 ms per frame)
        Sleep((DWORD)(frameDelay * 1000)); // Sleep takes milliseconds
    }

    // Show cursor before exiting
    show_cursor();
    return 0;
}
