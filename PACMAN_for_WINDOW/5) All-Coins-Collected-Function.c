// Section 5: This function checks whether all the coins have been collected so that it can return true to indicate the Game Over Scene

// Function to check if all coins have been collected
bool AllCoinsCollected(int Food) {
    if (Food != 613){
        return false;   // Coins Left
    }
    return true;  // No coins left
}