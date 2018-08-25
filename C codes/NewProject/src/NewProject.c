/*
 ============================================================================
 Name        : NewProject.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>

int func(double x){
	return  x * x * x + 2 * x * x - 2;
}

double zeroFinder(double min, double max, double error){

	while(max - min > error){

		double guess = (max + min)/2;

		if(func(guess) == 0){
			return guess;
		}else if(func(guess) > 0){
			min = guess;
		}else{
			max = guess;
		}
	}
	return min;
}

double zeroFindRec(double min, double max, double error){

	if(max - min > error){
		double guess = (max + min)/2;

		if(func(guess) == 0){
			return guess;
		}else if(func(guess) > 0){
			return zeroFindRec(guess, max, error);
		}else{
			return zeroFindRec(min, guess, error);
		}
	}
	return min;
}
int main(){

	printf("zero: %f \n", zeroFindRec(-1.33, 0.0, 0.01));
	printf("zero: %f \n", zeroFinder(-1.33, 0.0, 0.001));
	printf("zero: %f \n", zeroFindRec(0.0, 1.0, 0.000001));
	printf("zero: %f \n", zeroFinder(0.0, 1.0, 0.0000000001));

    return 0;
}


