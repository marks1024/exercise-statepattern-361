/*
 ============================================================================
 Name        : Complex.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include "complex.h"

complex add(complex x, complex y) {

	complex result;
	result.re = x.re + y.re;
	result.im = x.im + y.im;
	return result;
}

complex sub(complex x, complex y) {

	complex result;
	result.re = x.re - y.re;
	result.im = x.im - y.im;
	return result;
}

void print(complex x) {
	printf("(%f, %f)\n", x.re, x.im);
}
