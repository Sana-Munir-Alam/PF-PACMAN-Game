// Section 4: This function is called every iteration to update the maze state as per character movement, it also displays many important things (like Lives status, Score, High Score, Time Elapsed etc)

// Render the box and character (every iteration)
void Render(int x, int y, int Ghost1X, int Ghost1Y, int Lives, int Score, int HighScore, double ElapsedTime, char Map[Height][Width]) {
    move_cursor(0, 0);  // Move cursor to the top left corner
    // Draw the Maze and Characters
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (IsWall(j, i)) {
                printf("%c", Wall);
            } else if (i == y && j == x) {
                printf("%c", Pacman);  // The Pacman
            } else if (i == Ghost1Y && j == Ghost1X) {
                printf("%c", GhostGang);  // Ghost1
            } else if (Map[i][j] == '.') {
                printf("%c", Coins);  // Coin
            } else {
                printf("%c", Empty);  // Empty space
            }
        }
        printf("\n");
    }
    printf("Lives: %d\n", Lives); // Display Remaining Lives
    printf("Score: %d\n", Score); // Display the Score
    printf("High Score: %d\n", HighScore); // Display the High Score
    printf("Time: %.0f seconds\n", ElapsedTime); // Display Elapsed Time
    printf("Pacman(%d,%d)", x,y);
    printf(" Demon (%d,%d)", Ghost1X, Ghost1Y);
    fflush(stdout);  // Ensure everything is printed immediately
}
