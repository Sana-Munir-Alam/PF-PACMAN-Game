//Section 1: of 5 functions that handle the whole game
// Time Function
double GetElapsedTime(time_t StartTime) {
    return difftime(time(NULL), StartTime);
}
