/*
 ============================================================================
 Name        : MinesWeeper.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void addProximities(char arr[][32], int r, int c){



	if(arr[r][c] != '*'){

		int count = 0;

		if(r-1 >= 0 && c-1 >= 0){
			if(arr[r-1][c-1] == '*'){
				count++;
			}
		}

		if(r-1 >= 0 ){
			if(arr[r-1][c] == '*'){
				count++;
			}
		}

		if(r-1 >= 0 && c+1 <= 32){
			if(arr[r-1][c+1] == '*'){
				count++;
			}
		}

		if(c-1 >= 0 ){
			if(arr[r][c-1] == '*'){
				count++;
			}
		}

		if(c+1 <= 32 ){
			if(arr[r][c+1] == '*'){
				count++;
			}
		}

		if(r+1 <= 12 && c-1 >= 0){
			if(arr[r+1][c-1] == '*'){
				count++;
			}
		}

		if(r+1 <= 12){
			if(arr[r+1][c] == '*'){
				count++;
			}
		}

		if(r+1 <= 12 && c+1 <= 32){
			if(arr[r+1][c+1] == '*'){
				count++;
			}
		}


	arr[r][c] = count + '0';
	}
}

int main(void) {

	char map[12][30];

	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 32; j++){
			map[i][j] = '.';
		}
		printf("\n");
	}

	int i;
	int row, column;

	for(i = 0; i < 10; i++){

		do{
			row = rand() % 10;
			column = rand() % 32;
			map[row][column] = '*';

		}while(map[row][column] == '.');
	}

	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 32; j++){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}

	printf("Enter the coordinates: ");
	scanf("%i %i", &row, &column);
	addProximities(map, row, column);

	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 32; j++){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}

	return 0;
}
