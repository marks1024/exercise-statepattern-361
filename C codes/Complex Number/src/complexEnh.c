/*
 * complexEnh.c
 *
 *  Created on: 4 сент. 2017 г.
 *      Author: zuldyz
 */

#include <math.h>
#include "complexEnh.h"

double mag(complex x) {
	return sqrt(x.re * x.re + x.im * x.im);
}

complex norm(complex x) {

	complex result;
	double norm = mag(x);
	result.re = x.re / norm;
	result.im = x.im / norm;
	return result;
}
