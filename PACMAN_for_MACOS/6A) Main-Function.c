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
            // Check if power-up time is over
            if (powerUpActive) {
                double elapsed = difftime(time(NULL), powerUpStart);
                if (elapsed >= 5) {
                    powerUpActive = false; // Deactivate power-up after 5 seconds
                }
            }
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
