/*
This Code is Correct: 
It has a continious moving PACMAN and 4 Ghost. (2 ghost moves Horizontally and 2 ghost moves Vertically)
It has coins which can be collected and replaced with empty space.
It has a timer that calculates how much time has passed since game started
It has a High Score and Player Score counter
It has W,A,S,D Keys as control keys (Made sure that both Upper Case and Small Case Letter are accepted)
It has Power Coins (@) that allows PACMAN to eat ghost temporaly for 5 seconds.
It has 3 Lives of PACMAN
It has a functioning maze
Invalid Enteries are ignored by the program
Game Ends in two Cases when all lives are lost or when all Coins Collected
When Gamover it shows options of NEW GAME and PLAY AGAIN, both these options work as they should (!Retain HighScore, Retain HighScore) Respectively
*/

/*
Additional Thing:
This code includes filing.
It asks user to create account and store it in a file.
it asks user to login to play
The game play when user has logged in.
The user than quits the game to save their score if it's higher than their previous score.
The user can view evry player high score by choosing display option
*/

/*
What's Left to do:
Sound effects.
*/

#include <stdio.h>
#include <conio.h>      // For kbhit() and getch()
#include <windows.h>    // For Sleep()
#include <stdbool.h>
#include <time.h>       // To call time related functions
#include <string.h>

// Pacman Define
#define Width 60
#define Height 26
#define Wall '|'
#define Pacman 'C'
#define GhostGang 'X'
#define GhostGang2 'Y'
#define GhostGang3 'Z'
#define GhostGang4 'W'
#define Coins '.'
#define Empty ' '
#define PowerCoin '@'

// Filing Define
#define MAX_NAME_LEN 30
#define MAX_PASS_LEN 20
#define MAX_Players 100

//Global Variable
int Food = 0;
int Score = 0;
int HighScore = 0;
bool powerUpActive = false;
time_t powerUpStart;

//These 4 functions below are handling the cursor, the terminal setting, and to get an input without the need of pressing enter or displaying it. (Smooth Display)
// Move cursor to a specific position in the terminal
void move_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide the cursor
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Show the cursor
void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE; // Show the cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
// Function to avoid Run Time Error in Filing Area
void clearInputBuffer() {
    while (getchar() != '\n'); // Clears the input buffer until a newline is found
}

/*                                                     
 ____   _    ____ __  __    _    _   _   ____   _    ____ _____ 
|  _ \ / \  / ___|  \/  |  / \  | \ | | |  _ \ / \  |  _ |_   _|
| |_) / _ \| |   | |\/| | / _ \ |  \| | | |_) / _ \ | |_) || |  
|  __/ ___ | |___| |  | |/ ___ \| |\  | |  __/ ___ \|  _ < | |  
|_| /_/   \_\____|_|  |_/_/   \_|_| \_| |_| /_/   \_|_| \_\|_|  
*/

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
            } else if ((i == 11 && j == 1) || (i == 11 && j == 58)){
                Map[i][j] = PowerCoin;
            }else {
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
                printf(powerUpActive ? "x" : "X");    // Ghost1
            } else if (i == Ghost2Y && j == Ghost2X){
                printf(powerUpActive ? "y" : "Y");   // Ghost2
            } else if (i == Ghost3Y && j == Ghost3X){
                printf(powerUpActive ? "z" : "Z");   // Ghost3
            } else if (i == Ghost4Y && j == Ghost4X){
                printf(powerUpActive ? "w" : "W");   // Ghost4
            }else if (Map[i][j] == PowerCoin) {
                printf("%c", PowerCoin);  // Power Coin
            } else if (Map[i][j] == '.') {
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
bool AllCoinsCollected(int Food) {
    if (Food != 613){
        return false;   // Coins Left
    }
    return true;  // No coins left
}

// Main game function
int Pacman_Game() {
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
    printf("To Quit Game Press Q\n");
    printf("\n\n");
    printf("CAUTION-------!!!-------CAUTION-------!!!-------CAUTION\n\n");
    printf("Caution: Pressing Q During Game WILL NOT SAVE YOUR SCORE instead wil send you back to Main Page!\n");
    printf("ALL PROGRESS DURING THAT SESSION WILL BE LOST.\n");
    printf("THINK BEFORE PRESSING \"Q\"");
    printf("\n\n");
    printf("To Start Game Press Y\n");
    

    // Wait for user input using getch
    char pf = _getch();
    if (pf != 'Y' && pf != 'y') {
        return 1; // Exit if not 'Y'/'y'
    }
    system("cls");  // Clearing the screen so that only map is shown

    // Game Initialization
    InitializeGame(Map, &x, &y, &Lives, true, true); // Start with a clean state
    hide_cursor();

    while (Running) {
        StartTime = time(NULL);  // Reset the timer

        while (Running) {
            // Check if power-up time is over
            if (powerUpActive) {
                double elapsed = difftime(time(NULL), powerUpStart);
                if (elapsed >= 5) {
                    powerUpActive = false; // Deactivate power-up after 5 seconds
                }
            }
            if (_kbhit()) { // Check if a key is pressed
                char ch = _getch(); // Get the pressed key
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
                        system("cls");
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
                } else if (Map[y][x] == PowerCoin) {
                        powerUpActive = true;
                        powerUpStart = time(NULL);
                        Map[y][x] = ' ';
                } else if (((newX + 1) == Ghost1X && newY == Ghost1Y) || (Ghost1X == (newX - 1) && Ghost1Y == newY) || (Ghost1X == newX && Ghost1Y == newY)) {  // Collision with GhostGang 1
                    if (powerUpActive) {
                        Score += 10;
                    }else{
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
                    }
                } else if(((newX + 1) == Ghost2X && newY == Ghost2Y) || (Ghost2X == (newX - 1) && Ghost2Y == newY) || (Ghost2X == newX && Ghost2Y == newY)) {   // Collision with GhostGang 2
                    if (powerUpActive) {
                        Score += 10;
                    }else{
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
                    }
                } else if((newX == Ghost3X && newY == Ghost3Y) || (Ghost3X == newX && Ghost3Y == newY - 1)|| (Ghost3X == newX && Ghost3Y == newY + 1)) {   // Collision with GhostGang 3
                    if (powerUpActive) {
                        Score += 10;
                    }else{
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
                    }
                } else if(newX == Ghost4X && newY == Ghost4Y || (Ghost4X == newX && Ghost4Y == newY - 1)|| (Ghost4X == newX && Ghost4Y == newY - 1)){   // Collision with GhostGang 4
                    if (powerUpActive) {
                        Score += 10;
                    }else{
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
                    }
                } else {
                    // Only update Pacman's position if not stunned
                    x = newX;
                    y = newY;

                    // Check for Coin Collection
                    if (Map[y][x] == Coins) {
                        Map[y][x] = Empty; // Remove Coin from Map
                        Score++;    // Increase Score by 1
                        Food++;
                        if (Score > HighScore) {
                            HighScore = Score; // Update High Score
                        }
                        // Check if All Coins Are Collected
                        if (AllCoinsCollected(Food)) {
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
                system("cls");
                printf("  ____    _    __  __ _____     _____     _______ ____\n");
                printf(" / ___|  / \\  |  \\/  | ____|   / _ \\ \\   / | ____|  _ \\\n");
                printf("| |  _  / _ \\ | |\\/| |  _|    | | | \\ \\ / /|  _| | |_) |  \n");
                printf("| |_| |/ ___ \\| |  | | |___   | |_| |\\ V / | |___|  _ <\n");
                printf(" \\____/_/   \\_|_|  |_|_____|   \\___/  \\_/  |_____|_| \\_\\\n");
                printf("\n\n\n");
                printf("Your Score: %d\n", Score);
                printf("High Score: %d\n", HighScore);
                printf("\n\n\n");
                printf("Press Q to Quit and Save your Score in File.\n");
                printf("Press N for New Game (Reset High Score of this session, Caution: Score is not saved on File)\n");
                printf("Press P for Play Again (Retain High Score of this session Caution: Score is not saved on File)\n");

                pf = _getch();
                if (pf == 'Q' || pf == 'q') {
                    Running = false;
                    return Score;
                } else if (pf == 'N' || pf == 'n') {    // New Game (High Score is set to 0)
                    Result = 0;
                    InitializeGame(Map, &x, &y, &Lives, true, true);
                } else if (pf == 'P' || pf == 'p') {    // Play Again (High Score is Retained)
                    Result = 0;
                    InitializeGame(Map, &x, &y, &Lives, true, false);
                }
            }
            Sleep((DWORD)(frameDelay * 1000)); // Frame rate control
        }
    }
    show_cursor();
    return 0;
}


/*
 _____ ___ _     ___ _   _  ____   ____   _    ____ _____ 
|  ___|_ _| |   |_ _| \ | |/ ___| |  _ \ / \  |  _ |_   _|
| |_   | || |    | ||  \| | |  _  | |_) / _ \ | |_) || |  
|  _|  | || |___ | || |\  | |_| | |  __/ ___ \|  _ < | |  
|_|   |___|_____|___|_| \_|\____| |_| /_/   \_|_| \_\|_|  
*/


struct Player{
    char Username[MAX_NAME_LEN];
    char Password[MAX_PASS_LEN];
    int Highscore;
};

// Create a New Account For the Player
void CreateAccount(struct Player *Players, int *PlayerCount) {
    getchar();
    
    printf("Enter Username: ");
    fgets(Players[*PlayerCount].Username, MAX_NAME_LEN, stdin);
    Players[*PlayerCount].Username[strcspn(Players[*PlayerCount].Username, "\n")] = '\0'; // Remove newline
    printf("Enter Password: ");
    fgets(Players[*PlayerCount].Password, MAX_PASS_LEN, stdin);
    Players[*PlayerCount].Password[strcspn(Players[*PlayerCount].Password, "\n")] = '\0'; // Remove newline
    
    Players[*PlayerCount].Highscore = 0; // New Players start with 0 score
    (*PlayerCount)++;   // Increase the player Counter by 1
    printf("Account created successfully!\n");
}

// Check Login credentials for an existing player
int Login(struct Player *Players, int PlayerCount, char *Username, char *Password) {
    for (int i = 0; i < PlayerCount; i++) {
        if (strcmp(Players[i].Username, Username) == 0 && strcmp(Players[i].Password, Password) == 0) {
            return i; // Player Found (Index)
        }
    }
    return -1; // Player not found
}

// Load Players and their high scores from the file
int LoadHighscores(struct Player *Players) {
    FILE *file = fopen("Highscores2.txt", "r");  // Open for reading
    int PlayerCount = 0;
    if (file == NULL) {
        return 0; // No saved data, so no Players
    }
    // Loop through the file and read each player's data
    // fscanf reads the username, password, and highscore in a specific format
    while (fscanf(file, "Username: %s\n", Players[PlayerCount].Username) == 1) {
        fscanf(file, "Password: %s\n", Players[PlayerCount].Password);  // Read the password for the current player, expecting the format "Password: <password>"
        fscanf(file, "Highscore: %d\n", &Players[PlayerCount].Highscore);   // Read the highscore for the current player, expecting the format "Highscore: <score>"
        PlayerCount++;  //PlayerCount is incremented by 1 to reflect that one more player has been loaded into the Players array.
    }
    fclose(file);
    return PlayerCount;
}

// Update the player's Highscore if necessary
void UpdatePlayerHighscore(struct Player *Players, int PlayerCount, int playerIndex, int score) {
    // Make sure the player index is valid
    if ((playerIndex >= 0 && playerIndex < PlayerCount)) {
        if(score > Players[playerIndex].Highscore){
            Players[playerIndex].Highscore = score;
            printf("\n\nHighscore updated successfully!\n");
            printf("Your New Highscore: %d\n", score);
        }else{
            printf("\nYour Score: %d\n", score);
        }
        return;
    } else {
        printf("Invalid player index.\n");
    }
}

// Save all player data, including high scores, to a file
void SaveHighscores(struct Player *Players, int PlayerCount) {
    FILE *file = fopen("Highscores2.txt", "w");  // Use "w" mode to overwrite and save the data
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < PlayerCount; i++) {
        fprintf(file, "Username: %s\n", Players[i].Username);
        fprintf(file, "Password: %s\n", Players[i].Password);
        fprintf(file, "Highscore: %d\n\n", Players[i].Highscore);
    }
    fclose(file);
}

// Display the High Scores For All Players
void DisplayHighscores(struct Player *Players, int PlayerCount) {
    printf("\nHigh Scores:\n");
    for (int i = 0; i < PlayerCount; i++) {
        printf("Username: %s, Highscore: %d\n", Players[i].Username, Players[i].Highscore);
    }
}

int main() {
    struct Player Players[MAX_Players];
    int PlayerCount = LoadHighscores(Players);
    int choice, score;
    char Username[MAX_NAME_LEN], Password[MAX_PASS_LEN];

    while (1) {
        // Initial Game Instructions and Start Page
        printf(" ____   _    ____ __  __    _    _   _\n");
        printf("|  _ \\ / \\  / ___|  \\/  |  / \\  | \\ | |\n");
        printf("| |_) / _ \\| |   | |\\/| | / _ \\ |  \\| |\n");
        printf("|  __/ ___ | |___| |  | |/ ___ \\| |\\  |\n");
        printf("|_| /_/   \\_\\____|_|  |_/_/   \\_|_| \\_|\n");
        printf("\n\n\n");
        printf("INSTRUCTIONS:\n");
        printf("1. Create New Account\n");
        printf("2. Login and Play\n");
        printf("3. Show High Scores of All Players in File\n");
        printf("4. Exit and Save Score in File\n");

        // Validate the choice input
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            system("cls");
            clearInputBuffer(); // Clear the invalid input from the buffer
            continue;
        }

        // Process the valid choice
        switch (choice) {
            case 1:
                CreateAccount(Players, &PlayerCount);
                break;
            case 2:
                getchar();
                printf("Enter your Username: ");
                fgets(Username, 30, stdin);
                Username[strcspn(Username, "\n")]='\0';
                printf("Enter your Password: ");
                fgets(Password, 30, stdin);
                Password[strcspn(Password, "\n")]='\0';
                
                int playerIndex = Login(Players, PlayerCount, Username, Password);
                if (playerIndex != -1) {
                    system("cls");
                    // Player logged in successfully, now start the game and get score
                    score = Pacman_Game(); 
                    // Update the player's high score
                    UpdatePlayerHighscore(Players, PlayerCount, playerIndex, score);
                    SaveHighscores(Players, PlayerCount);
                    printf("Score: %d\n", score); // Display score
                } else {
                    printf("Invalid Username or Password!\n");
                }
                break;
            case 3:
                DisplayHighscores(Players, PlayerCount);
                break;
            case 4:
                SaveHighscores(Players, PlayerCount);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    }
    return 0;
}
