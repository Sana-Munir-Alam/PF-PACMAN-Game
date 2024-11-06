//Section 1: This Function handles the time calculation (from when the game begins till the game ends)

// Time Function
double GetElapsedTime(time_t StartTime) {
    return difftime(time(NULL), StartTime);
}
