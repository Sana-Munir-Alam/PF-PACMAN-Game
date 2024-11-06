//Section 3: This function is what that recreates the whole map including walls and all the inside characters when the game begins or when player start a new game, this function basically resets everything to its original state.

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
