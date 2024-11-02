/*
This Code is Correct: 
It has a continious moving PACMAN and 4 Ghost. (2 ghost moves Horizontally and 2 ghost moves Vertically)
It has coins which can be collected and replaced with empty space.
It has a timer that calculates how much time has passed since game started
It has a High Score and Player Score counter
It has W,A,S,D Keys as control keys (Made sure that both Upper Case and Small Case Letter are accepted)
Invalid Enteries are ignored by the program
It has 3 Lives of PACMAN
It has a functioning maze
Game Ends in two Cases when all lives are lost or when all Coins Collected
When Gamover it shows options of NEW GAME and PLAY AGAIN, both these options work as they should (!Retain HighScore, Retain HighScore) Respectively
*/

/*What's Left to do:
Sound effects, need to temporaly allow pacman to eat ghost
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define Width 60
#define Height 26
#define Wall '#'
#define Pacman 'C'
#define GhostGang 'X'
#define GhostGang2 'Y'
#define GhostGang3 'Z'
#define GhostGang4 'W'
#define Coins '.'
#define Empty ' '

//Global Variable
int Score = 0;
int HighScore = 0;
int Coin = 0;
//These 7 functions below are handling the cursor, the terminal setting, and to get an input without the need of pressing enter or displaying it. (Smooth Display)
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


// These 5 are the functions realted to the Game functioning
// Time Function
double GetElapsedTime(time_t StartTime) {
    return difftime(time(NULL), StartTime);
}

// Check if next position is wall (This is used to print the maze wall structure)
bool IsWall(int x, int y) {
    if(y == 0 || x == Width -1 || x == 0 || y == Height -1) {   //Thys creates the main boundary of the wall
        return true;
    }else if((y==1 || y==2 || y==3 || y==4) && (x == 29 || x == 30)){ // Row 1 to Row 4 walls                
        return true;
    }else if((y==2 || y==3 || y==4)&& ((x>=2 && x <= 13)||(x>=16 && x<=27)||(x>=32 && x<=43)||(x>=46 && x<=57))){                 
        return true;
    }else if((y==6)&& ((x>=2 && x<=13) || (x>=16 && x<=18) || (x>=20 && x<=39)|| (x>=41 && x<=43)|| (x>=46 && x<=57))){ // Row 6                 
        return true;
    }else if((y==7)&& ((x>=16 && x<=18) || (x>=29 && x<=30) || (x>=41 && x<=43))){ // Row 7                 
        return true;
    }else if((y==8)&& ((x>=1 && x<=13) || (x>=16 && x<=26) || (x>=29 && x<=30)|| (x>=33 && x<=43)|| (x>=46 && x<=58))){ // Row 8                 
        return true;
    }else if((y==9)&& ((x>=1 && x<=13) || (x>=16 && x<=18) || (x>=41 && x<=43)|| (x>=46 && x<=58))){ // Row 9
        return true;
    }else if((y==10)&& ((x>=1 && x<=13) || (x>=16 && x<=18) || (x>=20 && x<=28)|| (x>=31 && x<=39)|| (x>=41 && x<=43)|| (x>=46 && x<=58))){ // Row 10 
        return true;
    }else if((y == 11) &&((x>=20 && x<=22)||(x>=37 && x<=39))){ // Row 11      
        return true;
    }else if((y == 12) &&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=20 && x<=28)||(x>=31 && x<=33)||(x>=34 && x<=39)||(x>=41 && x<=43)||(x>=46 && x<=58))){ // Row 12                
        return true;
    }else if((y == 13) &&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=41 && x<=43)||(x>=41 && x<=43)||(x>=46 && x<=58))){ // Row 13             
        return true;
    }else if((y == 14)&&((x>=1 && x<=13)||(x>=16 && x<=18)||(x>=20 && x<=22)||(x>=23  && x<=39)||(x>=41 && x<=43)||(x>=46 && x<=58))){ // Row 14               
        return true;
    }else if((y == 15)&&((x==29 || x ==30))){ // Row 15                 
        return true;   
    }else if ((y==16)&& ((x>=2 && x<= 13) || (x>=16 && x<=26) || (x>=29 && x<= 30) || (x>=33 && x<= 43) || (x>=46 && x<=57))) { // Row 16                 
        return true;  
    }else if ((y==17)&& ((x>=8 && x<= 13) || (x>=46 && x<=51))) { // Row 17                 
        return true;  
    }else if ((y==18)&& ((x>=1 && x<= 6) || (x>=8 && x<=13)|| (x>=16 && x<=18)|| (x>=20 && x<=39) || (x>=41 && x<=43) || (x>=46 && x<=51) || (x>=53 && x<=58))) { // Row 18                 
        return true;  
    }else if ((y==19)&& ((x>=16 && x<= 18) || (x>=29 && x<=30)|| (x>=41 && x<=43))) { // Row 19                
        return true;  
    }else if ((y==20)&& ((x>=2 && x<= 26) || (x>=29 && x<=30)|| (x>=33 && x<=57))) { // Row 20                 
        return true;  
    }else if ((y==21)&& ((x>=2 && x<= 10) || (x>=28 && x<=31)|| (x>=49 && x<=57))) { // Row 21                 
        return true;  
    }else if((y==22)&&((x>=2&&x<=7)||(x>=11&&x<=26)||(x>=33&&x<=54))){ // Row 22                
        return true;  
    }else if((y == 23)&&((x>=2&&x<=9)||(x>=11&&x<=15)||(x>=17&&x<=26)||(x>=33&&x<=57))){ // Row 23                
        return true;                
    }else if((y == 24)&&(x>=28&&x<=31)){ // Row 24               
        return true; 
    }
    return false;
}

// Initializes or resets the game variables and map
void InitializeGame(char Map[Height][Width], int *x, int *y, int *Lives, bool resetScore, bool resetHighScore) {
    // Reset PACMAN position, lives, and score
    *x = 29;
    *y = 17;
    *Lives = 3;
    Score = resetHighScore? 0 : 0;
    HighScore = resetHighScore ? 0 : HighScore;

    // Reset the map with coins and clear previous characters positions
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (i == 17 && j == 29) {
                Map[i][j] = Pacman;
            } else if (i == 5 && j == 14) {
                Map[i][j] = GhostGang;
            } else if ( i == 11 && j == 23){
                Map[i][j] = GhostGang2;
            } else if (i == 19 && j ==45){
                Map[i][j] = GhostGang3;
            } else if(i == 1 && j == 14){
                Map[i][j] = GhostGang4;
            } else {
                Map[i][j] = Coins;
            }
        }
    }
}

// Render the box and character (every iteration)
void Render(int x, int y, int Ghost1X, int Ghost1Y, int Ghost2X, int Ghost2Y, int Ghost3X, int Ghost3Y, int Ghost4X, int Ghost4Y, int Lives, int Score, int HighScore, double ElapsedTime, char Map[Height][Width]) {
    move_cursor(0, 0);  // Move cursor to the top left corner
    
    // Draw the Maze and Characters
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (IsWall(j, i)) {
                printf("%c", Wall);
            } else if (i == y && j == x) {
                printf("%c", Pacman);  // The Pacman
            } else if (i == Ghost1Y && j == Ghost1X) {
                printf("%c", GhostGang);    // Ghost1
            } else if (i == Ghost2Y && j == Ghost2X){
                printf("%c", GhostGang2);   // Ghost2
            } else if (i == Ghost3Y && j == Ghost3X){
                printf("%c", GhostGang3);   // Ghost3
            } else if (i == Ghost4Y && j == Ghost4X){
                printf("%c", GhostGang4);   // Ghost4
            }else if (Map[i][j] == '.') {
                printf("%c", Coins);  // Coin
            } else {
                printf("%c", Empty);  // Empty space
            }
        }
        printf("\n");
    }
    printf("Lives: %d\n", Lives); // Display Remaining Lives
    printf("Score: %d\n", Score); // Display the Player Score
    printf("High Score: %d\n", HighScore); // Display the High Score
    printf("Time: %.0f seconds\n", ElapsedTime); // Display Elapsed Time
    printf("Pacman(%d,%d)\n", x,y);
    printf("Demon 1 (%d,%d)\n", Ghost1X, Ghost1Y);
    printf("Demon 2 (%d,%d)\n", Ghost2X, Ghost2Y);
    printf("Demon 3 (%d,%d)\n", Ghost3X, Ghost3Y);
    printf("Demon 4 (%d,%d)\n", Ghost4X, Ghost4Y);
    fflush(stdout);  // Ensure everything is printed immediately
}

// Function to check if all coins have been collected
bool AllCoinsCollected(int Coin) {
    if (Coin != 615){
        return false;   // Coins Left
    }
    return true;  // No coins left
}

// Main game function
int main() {
    int x = 29;         // Initial x position of Pacman
    int y = 17;         // Initial y position of Pacman
    int dx = 0;         // No x movement initially
    int dy = 0;         // No y movement initially
    int Ghost1X = 14;   // Initial Ghost1 x position
    int Ghost1Y = 5;    // Fixed Ghost1 y position
    int Ghost1DX = 1;   // Ghost1 moving right initially
    int Ghost2X = 23;   // Initial Ghost2 x position
    int Ghost2Y = 11;   // Fixed Ghost2 y position
    int Ghost2DX = 1;   // Ghost2 moving right initially
    int Ghost3X = 45;   // Fixed Ghost3 x position
    int Ghost3Y = 19;   // Initial Ghost3 y position
    int Ghost3DY = -1;  // Ghost3 Moving up initially
    int Ghost4X = 14;   // Fixed Ghost4 x position 
    int Ghost4Y = 1;    // Initial Ghost4 y position
    int Ghost4DY = 1;   // Ghost4 moving down initially
    int Lives = 3;      // Pacman Total Lives
    int Result = 0;     // Holds the AllCoinsCollected Status
    bool Stunned = false;
    bool Running = true;
    char Map[Height][Width];

    time_t StartTime;
    const double frameDelay = 0.1; // Frame delay for movement

    // Initial Game Instructions and Start Page
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
    printf("To Quit Game Press Q (Caution: Whole Program will End, Nothing will be Saved, Think Before Clicking)\n");
    printf("\n\n");
    printf("To Start Game Press Y\n");
    
    enable_non_blocking_input();
    // Wait for user input using getch
    char pf = getch();
    if (pf != 'Y' && pf != 'y') {
        return 1; // Exit if not 'Y'/'y'
    }
    system("clear");  // Clearing the screen so that only map is shown

    // Game Initialization
    InitializeGame(Map, &x, &y, &Lives, true, true); // Start with a clean state
    hide_cursor();

    while (Running) {
        StartTime = time(NULL);  // Reset the timer

        while (Running) {
            if (kbhit()) { // Check if a key is pressed
                char ch = getch(); // Get the pressed key
                if (Stunned) {      // This Condition Runs when Pacman has hit Ghost Gang
                    Stunned = false;
                    x = 29; // Original x coordinate
                    y = 17; // Original y coordinate
                    dx = 0; // Reset x movement direction
                    dy = 0; // Reset y movement direction
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
            
            // This Condition Runs when Pacman has not hit Ghost Gang
            if (!Stunned) {
                int newX = x + dx;
                int newY = y + dy;

                if (IsWall(newX, newY)) {
                    continue;
                } else if (((newX + 1) == Ghost1X && newY == Ghost1Y) || (Ghost1X == (newX - 1) && Ghost1Y == newY) || (Ghost1X == newX && Ghost1Y == newY)) {  // Collision with GhostGang 1
                    Lives--;    // Decrease Lives by 1
                    Stunned = true; // Set stunned state to true
                    printf("Ouch! You hit a ghost! Lives left: %d\n", Lives);
                    
                    // Reset Pacman's position
                    x = 29; // Original x position
                    y = 17; // Original y position
                    
                    // Check if the player is out of lives
                    if (Lives <= 0) {
                        break; // Break if no lives are left
                    }
                } else if(((newX + 1) == Ghost2X && newY == Ghost2Y) || (Ghost2X == (newX - 1) && Ghost2Y == newY) || (Ghost2X == newX && Ghost2Y == newY)) {   // Collision with GhostGang 2
                    Lives--;    // Decrease Lives by 1
                    Stunned = true; // Set stunned state to true
                    printf("Ouch! You hit a ghost! Lives left: %d\n", Lives);
                    
                    // Reset Pacman's position
                    x = 29; // Original x position
                    y = 17; // Original y position
                    
                    // Check if the player is out of lives
                    if (Lives <= 0) {
                        break; // Break if no lives are left
                    }
                } else if((newX == Ghost3X && newY == Ghost3Y) || (Ghost3X == newX && Ghost3Y == newY - 1)|| (Ghost3X == newX && Ghost3Y == newY + 1)) {   // Collision with GhostGang 3
                    Lives--;    // Decrease Lives by 1
                    Stunned = true; // Set stunned state to true
                    printf("Ouch! You hit a ghost! Lives left: %d\n", Lives);
                    
                    // Reset Pacman's position
                    x = 29; // Original x position
                    y = 17; // Original y position
                    
                    // Check if the player is out of lives
                    if (Lives <= 0) {
                        break; // Break if no lives are left
                    }
                } else if(newX == Ghost4X && newY == Ghost4Y || (Ghost4X == newX && Ghost4Y == newY - 1)|| (Ghost4X == newX && Ghost4Y == newY - 1)){   // Collision with GhostGang 4
                    Lives--;    // Decrease Lives by 1
                    Stunned = true; // Set stunned state to true
                    printf("Ouch! You hit a ghost! Lives left: %d\n", Lives);
                    
                    // Reset Pacman's position
                    x = 29; // Original x position
                    y = 17; // Original y position
                    
                    // Check if the player is out of lives
                    if (Lives <= 0) {
                        break; // Break if no lives are left
                    }
                } else {
                    // Only update Pacman's position if not stunned
                    x = newX;
                    y = newY;

                    // Check for Coin Collection
                    if (Map[y][x] == Coins) {
                        Map[y][x] = Empty; // Remove Coin from Map
                        Score++;    // Increase Score by 1
                        Coin++;     // Increase Coin by 1
                        if (Score > HighScore) {
                            HighScore = Score; // Update High Score
                        }
                        // Check if All Coins Are Collected
                        if (AllCoinsCollected(Coin)) {
                            Result = 1;
                            break;
                        }
                    }
                }
            }

            // Ghost 1 movement // Confirmed Deaths of PACMAN if hit
            Ghost1X += Ghost1DX;
            if (Ghost1X < 1 || Ghost1X >= Width - 1) { // Change direction at boundaries
                Ghost1DX = -Ghost1DX;
                Ghost1X += Ghost1DX; // Move Ghost1 in the new direction
            }
            // Ghost 2 movement // Confirmed Deaths of PACMAN if hit
            Ghost2X += Ghost2DX;
            if (Ghost2X < 23 || Ghost2X > 36) { // Change direction at boundaries
                Ghost2DX = -Ghost2DX;
                Ghost2X += Ghost2DX; // Move Ghost2 in the new direction
            }
            // Ghost 3 movement // Confirmed Deaths of PACMAN if hit
            Ghost3Y += Ghost3DY;
            if (Ghost3Y < 1 || Ghost3Y > 19) { // Change direction at boundaries
                Ghost3DY = -Ghost3DY;
                Ghost3Y += Ghost3DY; // Move Ghost3 in the new direction
            }
            // Ghost 4 movement // Confirmed Deaths of PACMAN if hit
            Ghost4Y += Ghost4DY;
            if (Ghost4Y < 1 || Ghost4Y > 19) { // Change direction at boundaries
                Ghost4DY = -Ghost4DY;
                Ghost4Y += Ghost4DY; // Move Ghost4 in the new direction
            }
            
            double ElapsedTime = GetElapsedTime(StartTime);
            Render(x, y, Ghost1X, Ghost1Y, Ghost2X, Ghost2Y, Ghost3X, Ghost3Y, Ghost4X, Ghost4Y, Lives, Score, HighScore, ElapsedTime, Map);

            // End Game EITHER due to All Lives Lost OR All Coins Collected / Option Menu
            if ((Lives <= 0) || (Result == 1)) {
                system("clear");
                printf("  ____    _    __  __ _____     _____     _______ ____\n");
                printf(" / ___|  / \\  |  \\/  | ____|   / _ \\ \\   / | ____|  _ \\\n");
                printf("| |  _  / _ \\ | |\\/| |  _|    | | | \\ \\ / /|  _| | |_) |  \n");
                printf("| |_| |/ ___ \\| |  | | |___   | |_| |\\ V / | |___|  _ <\n");
                printf(" \\____/_/   \\_|_|  |_|_____|   \\___/  \\_/  |_____|_| \\_\\\n");
                printf("\n\n\n");
                printf("Your Score: %d\n", Score);
                printf("High Score: %d\n", HighScore);
                printf("\n\n\n");
                printf("Press Q to Quit\n");
                printf("Press N for New Game (Reset High Score)\n");
                printf("Press P for Play Again (Retain High Score)\n");
                //enable_non_blocking_input();
                pf = getch();
                if (pf == 'Q' || pf == 'q') {
                    Running = false;
                } else if (pf == 'N' || pf == 'n') {    // New Game (High Score is set to 0)
                    Result = 0;
                    InitializeGame(Map, &x, &y, &Lives, true, true);
                } else if (pf == 'P' || pf == 'p') {    // Play Again (High Score is Retained)
                    Result = 0;
                    InitializeGame(Map, &x, &y, &Lives, true, false);
                }
            }
            
            usleep((useconds_t)(frameDelay * 1000000));
        }
    }
    show_cursor();
    disable_non_blocking_input();
    return 0;
}
