#include <stdio.h>

void map(){
	#define Height 26
    #define Width 60
    #define Wall '#'
    #define Empty '.'
	char map[Height][Width];
	for (int i=0; i < Height; i++) {
    	for (int j=0;j < Width; j++) {
        	if(i == 0 || j == Width -1 || j == 0 || i == Height -1) {
                map[i][j] = Wall;
                printf("%c", map[i][j]);
            }else{
                map[i][j] = Empty;
                printf("%c", map[i][j]);
            }
        }printf("\n");
  	}
}
int main(){
    map();
}