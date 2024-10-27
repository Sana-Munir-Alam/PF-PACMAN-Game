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
