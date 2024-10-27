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
