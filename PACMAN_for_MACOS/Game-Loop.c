int GameLoop(){
    startTime = time(NULL);
    char pf;
    while (1) {
            DrawMap();
            DisplayTime();
            if (result == 1) { 
                // Clear screen 
                system("cls"); 
                printf("You Win! \n Your Score: %d\n", Score); 
                return 1; 
            } 
            pf = getch();
            // Move based on user input
            switch (pf) { 
                case 'W':
                    move(-1, 0); // Move up
                    break;
                case 'S':
                    move(1, 0); // Move down
                    break;
                case 'A':
                    move(0, -1); // Move left
                    break;
                case 'D':
                    move(0, 1); // Move right
                    break;
                case 'Q':
                    printf("Game Over! Your Score: %d\n", Score);
                    return 0;
                default:
                    break;
            }
        // Delay for a moment to slow down the loop
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
        }
}
