#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define Height 26   //This defines the height of the maze (rows)
#define Width 60    //This defines the width of the maze (columns)
#define Wall '#'    //This defines the wall material
#define Empty ' '   //This defines the empty space (where pacman and the ghostgang will roam about)
#define Coins '.'
#define Pacman 'C'
#define GhostGang 'X'

//global variable
int Score = 0;
int Coin = 0;
int result = 0;
int Px = 17, Py = 29;
char map[Height][Width]; //2D Array for defining the height and width of the maze

//Function that creates the main map
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

//Draw Map it redraws map after each movement
void DrawMap() {
    system("cls");  // Clear screen before each redraw
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            printf("%c", map[i][j]);  // Print current map state
        }
        printf("\n");
    }
    printf("Score: %d\n", Score);  // Display current score
}

// Function to move the player based on input direction
void move(int move_x, int move_y) {
    int newX = Px + move_x;
    int newY = Py + move_y;

    if (newX >= 0 && newX < Height && newY >= 0 && newY < Width && map[newX][newY] != Wall) {
        if (map[newX][newY] == Coins) {
            Score = Score + 1;  // Increment score when collecting a coin
            Coin = Coin - 1;
            if (Coin == 0){
                result = 1;
                return;
            }
        }
        map[Px][Py] = Empty;  // Clear Pacman’s previous position
        Px = newX;             // Update Pacman's position
        Py = newY;
        map[Px][Py] = Pacman;  // Place Pacman at the new position
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
    printf("To Quit Game Press Q\n");
    printf("\n\n");
    printf("To Start Game Press Y\n"); // Display prompt to start the game

    // Wait for user input using getch from conio.h (for Windows)
    pf = _getch(); // _getch() gets a single character without waiting for Enter

    if (pf != 'Y' && pf != 'y') {
        printf("Exit Game\n");
        return 1; // Exit if the input is not 'Y' or 'y'
    }
    
    // If 'Y' or 'y' is pressed, continue the game
    printf("Game Starting...\n"); // Indicate the game has started
    CreateMap();
    system("cls"); 

    while (1) {
        DrawMap();
		
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
    }
    return 0;
}
