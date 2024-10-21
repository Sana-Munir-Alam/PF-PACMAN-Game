//This code is only the title page and Map (every addition in our code will be added here)
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Function to get a single character input without waiting for Enter
char getch() {
    char ch;
    struct termios oldt, newt; //These are structures that hold the terminal settings. We need two variables: oldt to store the original settings so that we can restore them later, and newt to modify the settings temporarily.

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt); //This function call retrieves the current settings of the terminal (associated with STDIN_FILENO, which represents standard input and stores them in the oldt structure. This allows us to save the current terminal configuration for later restoration.
    newt = oldt; //This copies the current terminal settings (oldt) to the newt structure so that we can modify them without affecting the original settings.
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo. ICANON: Canonical mode is responsible for line-buffered input, which means input is not sent to the program until the user presses Enter. By disabling this (~ICANON), the program can capture each character as it's typed, without waiting for Enter. ECHO: This flag causes input to be echoed back to the terminal (i.e., when you type, it shows up on the screen). By disabling this (~ECHO), characters typed by the user won’t be displayed on the terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // This function applies the modified terminal settings (newt) immediately (TCSANOW). Input will be captured character by character

    ch = getchar(); // Read a single character

    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //After capturing the character, this line restores the terminal to its original settings (oldt).
    
    return ch; // Return the character read
}

//Creating Map of PACMAN
void map(){
	#define Height 26   //This defines the height of the maze (rows)
    #define Width 60    //This defines the width of the maze (columns)
    #define Wall '#'    //This defines the wall material
    #define Empty ' '   //This defines the empty space (where pacman and the ghostgang will roam about)
	char map[Height][Width];    //2D Array for defining the height and width of the maze
	for (int i=0; i < Height; i++) {       //use of nested loop inorder for the walls to be made horizontally and vertically
    	for (int j=0;j < Width; j++) {
        	if(i == 0 || j == Width -1 || j == 0 || i == Height -1) {   //This creates the main boundary of the wall
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==1 && j < 29)){
                map[i][j] = Empty;
                printf("%c", map[i][j]);
            }else if((i==1 || i==2 || i==3 || i==4) && (j == 29 || j == 30)){ //row 1 to row 4 walls
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else if((i==2 || i==3 || i==4)&& ((j>=2 && j <= 13)||(j>=16 && j<=27)||(j>=32 && j<=43)||(j>=46 && j<=57))){ //row 2 to row 4 walls
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
            }else{
                map[i][j] = Empty;
                printf("%c", map[i][j]);
            }
        }printf("\n"); //To move to next line
  	}
}
int main() {
    char pf;
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
    printf("\n\n");
    printf("To Start Game Press Y\n"); // Display prompt to start the game

    // Wait for user input
    pf = getch(); // Call the custom getch function
    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }
    
    // If 'Y' or 'y' is pressed, continue the game
    printf("Game Starting...\n"); // Indicate the game has started
    system("clear"); //Clears the current screen completely so that map can be drawn in a new page.
    map(); //Calling the map function to create the game map.
    return 0;
}
