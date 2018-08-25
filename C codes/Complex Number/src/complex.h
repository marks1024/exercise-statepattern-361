/*
 * complex.h
 *
 *  Created on: 4 сент. 2017 г.
 *      Author: zuldyz
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

typedef struct {
	double re;
	double im;
} complex;

complex add(complex x, complex y);

complex sub(complex x, complex y);

void print(complex x);


#endif /* COMPLEX_H_ */
