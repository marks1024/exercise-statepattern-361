/*
 ============================================================================
 Name        : MyProj.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<math.h>

int main (void){

	int n, div;
	double x, result, t;

	result = 0;
	x = 2.0;
	div = 1;
	t = 1;

	for(n = 0; n < 10; n++){
		for(int i = 1; i <= n; i++){
			div *= i;
			t = pow(x, n)/div;
		}
		result+=t;
		div = 1;
	}


	printf("%f\n", result);


	return 0;
}
