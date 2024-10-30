// Section A: This is our main Function, it has the home page, the game page, and the exit page, it iincludes movements, coins check, collision check etc.

// Main game function
int main() {
    int x = 29;         // Initial x position of Pacman
    int y = 17;         // Initial y position of Pacman
    int dx = 0;         // No movement initially
    int dy = 0;         // No movement initially
    int Ghost1X = 14;   // Initial demon x position
    int Ghost1Y = 5;    // Fixed demon y position
    int Ghost1DX = 1;   // Demon moving right initially
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

    // Game initialization
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
                    dx = 0; // Reset movement direction
                    dy = 0; // Reset movement direction
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
                } else if (((newX + 1) == Ghost1X && newY == Ghost1Y) || (Ghost1X == (newX - 1) && Ghost1Y == newY) || (Ghost1X == newX && Ghost1Y == newY)) {  // Collision with GhostGang
                    Lives--;    // Decrease Lives by 1
                    Stunned = true; // Set stunned state to true
                    printf("Ouch! You hit a demon! Lives left: %d\n", Lives);
                    
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
                        Score++;    //Increase Score by 1
                        if (Score > HighScore) {
                            HighScore = Score; // Update High Score
                        }
                        // Check if All Coins Are Collected
                        if (AllCoinsCollected(Score)) {
                            Result = 1;
                            break;
                        }
                    }
                }
            }

            // Demon movement //Confirm Deaths of PACMAN if hit
            Ghost1X += Ghost1DX;
            if (Ghost1X < 1 || Ghost1X >= Width - 1) { // Change direction at boundaries
                Ghost1DX = -Ghost1DX;
                Ghost1X += Ghost1DX; // Move demon in the new direction
            }

            
            double ElapsedTime = GetElapsedTime(StartTime);
            Render(x, y, Ghost1X, Ghost1Y, Lives, Score, HighScore, ElapsedTime, Map);

            // End Game due to All Lives Lost OR All Coins Collected Option Menu
            if ((Lives <= 0) || (Result == 1)) {
                system("clear");
                printf("  ____    _    __  __ _____     _____     _______ ____\n");
                printf(" / ___|  / \\  |  \\/  | ____|   / _ \\ \\   / | ____|  _ \\\n");
                printf("| |  _  / _ \\ | |\\/| |  _|    | | | \\ \\ / /|  _| | |_) |  \n");
                printf("| |_| |/ ___ \\| |  | | |___   | |_| |\\ V / | |___|  _ <\n");
                printf(" \\____/_/   \\_|_|  |_|_____|   \\___/  \\_/  |_____|_| \\_\\\n");
                printf("\n\n");
                printf("Your Score: %d\n", Score);
                printf("High Score: %d\n", HighScore);
                printf("\n\n\n");
                printf("Press Q to Quit\n");
                printf("Press N for New Game (Reset High Score)\n");
                printf("Press P for Play Again (Retain High Score)\n");
                enable_non_blocking_input();
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
