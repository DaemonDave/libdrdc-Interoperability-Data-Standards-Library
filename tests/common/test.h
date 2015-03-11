#ifndef TEST_H
#define TEST_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif




// global includes
#include <math.h>
#include <stdio.h>

// local includes
#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif

//! convert hex values to double value
double Hex2Double(const uint32_t lsw,const uint32_t msw);
//! 
int doubleChecker(const double t, const int n, const double *v, const double *v_exp);
int intChecker(const int n, const int *v, const int *v_exp);
int charChecker(const int n, const char *v, const char *v_exp);

void printVector(int N, double *v);
void printMatrix(double *m);


//!  epsilon, smallest float value where 1+ epsilon > 1 
//!  It is an upper bound on the relative error due to roundoff of all the individual floating-point operations.
#define EPSILON_FLOAT  2.220446049250313e-016


#define  BASE_FUZZ 0.000001
static double FUZZ_3[]={BASE_FUZZ, BASE_FUZZ, BASE_FUZZ};
static double FUZZ_4[]={BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ};
static double FUZZ_6[] ={BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ};
static double FUZZ_7[] ={BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ};
static double FUZZ_16[]={BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ,
			     BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ,
			     BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ,
			     BASE_FUZZ, BASE_FUZZ, BASE_FUZZ, BASE_FUZZ};

#endif
