// Extra Functions (Not included in Main Game)
/* This getch function was replaced with short pieces of it called enable-non-blocking input (you can find this in Section 0: Terminal-Technicalities Function).
They all do the same thing that is making changes in terminal setting of ICANON and ECHO. (The comments might help you understand what is happening exactly).
*/

// Function to get a single character input without waiting for Enter
char getch() {
    char buf = 0;  // Declare a variable to store the character read from input.
    struct termios old = {0};  // Declare a struct to hold the current terminal settings.
    
    // Retrieve the current terminal settings and store them in 'old'
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");     //This function call retrieves the current settings of the terminal (associated with STDIN_FILENO, which represents standard input and stores them in the oldt structure. This allows us to save the current terminal configuration for later restoration.

    // Modify the terminal settings stored in 'old' to disable canonical mode and echo.
    old.c_lflag &= ~ICANON;  // ICANON: Canonical mode is responsible for line-buffered input, which means input is not sent to the program until the user presses Enter. By disabling this (~ICANON), the program can capture each character as it's typed, without waiting for Enter.
    old.c_lflag &= ~ECHO;  // ECHO: This flag causes input to be echoed back to the terminal (i.e., when you type, it shows up on the screen). By disabling this (~ECHO), characters typed by the user won’t be displayed on the terminal.

    // Set minimum number of characters for non-canonical read to 1 and set timeout to 0.
    old.c_cc[VMIN] = 1;  // 'VMIN = 1' ensures the program will wait for at least one character to be input before proceeding.
    old.c_cc[VTIME] = 0;  // 'VTIME = 0' sets no timeout for input. It ensures the program waits indefinitely for input, which is ideal for capturing real-time keystrokes.

    // Apply the new terminal settings (with canonical mode and echo disabled) immediately.
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");  // Apply changes to terminal settings using 'TCSANOW', which makes the changes take effect immediately.
    // Read one character from standard input (file descriptor 0) and store it in 'buf'.
    // 'read(0, &buf, 1)' reads 1 byte (character) from STDIN. This is a low-level system call that directly interacts with input streams.
    if (read(0, &buf, 1) < 0) perror("read()");  // If reading fails, print an error message.
    // Restore the original terminal settings (enable canonical mode and echo).
    old.c_lflag |= ICANON;  // Re-enable canonical mode, meaning input will be line-buffered again (user has to press Enter to send input).
    old.c_lflag |= ECHO;  // Re-enable echo, meaning typed characters will now be displayed on the terminal.
    // Apply the restored terminal settings after all pending output has been written.
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");  // Use 'TCSADRAIN' to wait until all output is written before restoring the settings, ensuring smooth terminal behavior.
    return buf;
}


// This function was removed and replaced with Section 2 and Section 1: However those 2 sections depict the final image of what this function does.
// This is how our maze actually looks like

//Function that creates the main map (this is making the alteration in the global map function)
void CreateMap(){
    system("cls"); //Clears Screen
    for (int i=0; i < Height; i++) {       //use of nested loop inorder for the walls to be made horizontally and vertically
        for (int j=0;j < Width; j++) {
            if(i == 0 || j == Width -1 || j == 0 || i == Height -1) {   //This creates the main boundary of the wall
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==1 || i==2 || i==3 || i==4) && (j == 29 || j == 30)){ //row 1 to row 4 walls
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==2 || i==3 || i==4)&& ((j>=2 && j <= 13)||(j>=16 && j<=27)||(j>=32 && j<=43)||(j>=46 && j<=57))){
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==6)&& ((j>=2 && j<=13) || (j>=16 && j<=18) || (j>=20 && j<=39)|| (j>=41 && j<=43)|| (j>=46 && j<=57))){ //row 6
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==7)&& ((j>=16 && j<=18) || (j>=29 && j<=30) || (j>=41 && j<=43))){ //row 7
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==8)&& ((j>=1 && j<=13) || (j>=16 && j<=26) || (j>=29 && j<=30)|| (j>=33 && j<=43)|| (j>=46 && j<=58))){ //row 8
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==9)&& ((j>=1 && j<=13) || (j>=16 && j<=18) || (j>=41 && j<=43)|| (j>=46 && j<=58))){ //row 9
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==10)&& ((j>=1 && j<=13) || (j>=16 && j<=18) || (j>=20 && j<=28)|| (j>=31 && j<=39)|| (j>=41 && j<=43)|| (j>=46 && j<=58))){ //row 10
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 11) &&((j>=20 && j<=22)||(j>=37 && j<=39))){
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 12) &&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=20 && j<=28)||(j>=31 && j<=33)||(j>=34 && j<=39)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 12
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 13) &&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=41 && j<=43)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 13
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 14)&&((j>=1 && j<=13)||(j>=16 && j<=18)||(j>=20 && j<=22)||(j>=23  && j<=39)||(j>=41 && j<=43)||(j>=46 && j<=58))){ //row 14
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i == 15)&&((j==29 || j ==30))){ //row 15
                map[i][j] = Wall;
                printf("%c", map[i][j]);   
            }else if ((i==16)&& ((j>=2 && j<= 13) || (j>=16 && j<=26) || (j>=29 && j<= 30) || (j>=33 && j<= 43) || (j>=46 && j<=57))) { //row 16
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==17)&& ((j>=8 && j<= 13) || (j>=46 && j<=51))) { //row 17
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==18)&& ((j>=1 && j<= 6) || (j>=8 && j<=13)|| (j>=16 && j<=18)|| (j>=20 && j<=39) || (j>=41 && j<=43) || (j>=46 && j<=51) || (j>=53 && j<=58))) { //row 18
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==19)&& ((j>=16 && j<= 18) || (j>=29 && j<=30)|| (j>=41 && j<=43))) { //row 19
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==20)&& ((j>=2 && j<= 26) || (j>=29 && j<=30)|| (j>=33 && j<=57))) { //row 20
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if ((i==21)&& ((j>=2 && j<= 10) || (j>=28 && j<=31)|| (j>=49 && j<=57))) { //row 21
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }
            else if((i==22)&&((j>=2&&j<=7)||(j>=11&&j<=26)||(j>=33&&j<=54))){ //row 22
                map[i][j] = Wall;
                printf("%c", map[i][j]);  
            }else if((i == 23)&&((j>=2&&j<=9)||(j>=11&&j<=15)||(j>=17&&j<=26)||(j>=33&&j<=57))){ //row 23
                map[i][j] = Wall;
                printf("%c", map[i][j]);                
            }else if((i == 24)&&(j>=28&&j<=31)){ //row 24
                map[i][j] = Wall;
                printf("%c", map[i][j]); 
            }else if (i == Px && j == Py) {
                map[i][j] = Pacman;
                printf("%c", map[i][j]);
            }else if ((map[i][j] != Pacman) && (map[i][j] != Wall)) {
                map[i][j] = Coins;
                printf("%c", map[i][j]);
                Coin = Coin + 1;
            }
        }printf("\n"); //To move to next line
    }
    printf("Score: %d\n", Score); 
}

//Draw Map it redraws map after each movement of the character
void DrawMap() {
    system("clear");  // Clear screen before each redraw
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            printf("%c", map[i][j]);  // Print current map state
        }
        printf("\n");
    }
    printf("Score: %d\n", Score);  // Display current score
}
