/*
 ============================================================================
 Name        : One.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	_Bool hasWall;
	_Bool hasBomb;
	_Bool wallCrashed;
}rectangularField;

int main(void) {
	int n, m;
	scanf("%i%i", &n, &m);

	rectangularField field[n][m];

	for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				field[i][j].hasWall = 0;
				field[i][j].hasBomb = 0;
				field[i][j].wallCrashed = 0;
			}
	}

	int i;
		int walls = rand()%1000;
		int row, column;
		// Add 10 robots to the grid
		for (i = 0; i < walls; i++) {

			do {
					row = rand() % n;
					column = rand() % m;
			} while (field[row][column].hasWall);

			field[row][column].hasWall = 1;
		}

		for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					if(field[i][j].hasWall){
						printf("*");
					}
					else{
						printf(".");
					}
				}
			}

		int x, y;



		for(int i = 0; i < n; i++){
				field[i][1].hasBomb = 1;
				for(int j = 0; j < m; j++){
					if(i == x && j == y){
						for(int k = 0; k < n; k++)
					}
						field[i][j].hasWall = 0;
						field[i][j].hasBomb = 0;
						field[i][j].wallCrashed = 0;
					}
			}

}
