/* #! /cygdrive/c/WINDOWS/system32/ch */
#ifndef TEST_H
#include "test.h"
#endif
//* convert hex value to double
double Hex2Double(const uint32_t lsw,const uint32_t msw) 
{
  DoubleUnion_t d;
  d.word[0]=lsw;
  d.word[1]=msw;
  return d.value;
}

/** tests the difference of doubles  "double checker"  HAHA

	compares v versus v_exp (value expected) and determines if it is within tolerance
	@param [in] t 		constant tolerance factor, multiplied by EPSILON_FLOAT f
	@param [in] n 		constant number of values to check, array
	@param [in] v 		constant pointer to array of test values
	@param [in] v_exp constant pointer to  value expected

*/
int doubleChecker(const double t, const int n, const double *v, const double *v_exp) 
{
  double diff;
  int i;
  int ret = 0; 

	double * p0 = (double *) v;
	double * p1 = (double *) v_exp;
		
	// interate for n values
  for(i=0;i<n;i++) 
	{
		 // store the value difference
     diff = (*p0 - *p1);
		 
     printf("Info: data = %.16g, expect = %.16g, diff=%g\n", *p0, *p1,diff);
		 // test for  tolerance
     if ( fabs(diff) > (EPSILON_FLOAT *t) ) 
		 {
       printf("Error: data = %.16g, but expect %.15g, diff=%g\n", *p0, *p1,diff);
       ret = 1;// return ERROR
     }
     p0++;   	// post increment 
		 p1++; // post increment to next data
  }
  return ret;
}

int intChecker(const int n, const int *v, const int *v_exp)
{
  int i;
  int ret = 0; 

  for(i=0;i<n;i++) {
    if (*v != *v_exp) {
      printf("Error: data = %d, but expect %d\n", *v, *v_exp);
      ret = 1;
    }
    *v++;
		*v_exp++;
  }
  return ret;
}

int charChecker(const int n, const char *v, const char *v_exp)
{
  int i;
  int ret = 0; 

  if (n == 1) {
    printf("Info: data = %c, expect = %c\n", *v, *v_exp);
    if (*v == *v_exp) {
      ret=0;
    } else {
      ret=1;
    }
  } else {
    printf("Info: data = %s, expect = %s\n", v, v_exp);
    ret = strncmp(v, v_exp, n);
  }
  if (ret == 1) {
    //printf("Error: data = %s, but expect %s\n", v, v_exp);
  }
/*   for(i=0;i<n;i++) { */
/*     if (*v != *v_exp) { */
/*       printf("data = %c, but expect %c\n", *v, *v_exp); */
/*       ret = 1; */
/*     } */
/*     *v++;*v_exp++; */
/*   } */
  return ret;
}

/* #include <stdio.h> */
/* #include <assert.h> */
/* int main(void) { */
/*   int z; */
/*   double x[2];  */
/*   double y[2]; */

/*   x[0]=hex2double(0x47ae147b,0x400c7ae1); */
/*   x[1]=hex2double(0x47ae147b,0x400c7ae1); */

/*   y[0]=hex2double(0x47ae147b,0x400c7ae1); */
/*   y[1]=hex2double(0x47ae147b,0x400c7ae1); */

/*   assert(0 == CheckDouble(1,2,x,y)); */
/*   printf("Haha\n"); */
/* } */






void printVector(int N, double *v) {
  int i;
  for (i=0; i < N; i++) {
    printf("%.6f ",v[i]);
  }
  printf("\n");
}

void printMatrix(double *m) {
  int i,j;
  for (i=0; i < 4; i++) {
    for (j=0; j < 4; j++) {
      printf("%-.6f ",m[j*4+i]);
    }
    printf("\n");
  }
  printf("\n");
}
