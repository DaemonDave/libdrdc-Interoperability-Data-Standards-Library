// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
// OF NATIONAL DEFENCE, CANADA, 2007

// Developed by:  Erickson, D. (DRDC Suffield)

// This library is free software;.  You can redistribute it and/or modify
// it under the terms and conditions of the GNU Lesser General Public
// License as published by the Free Software Foundation; either

// Version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA

// Licence is located in license.txt in libdrdc source root

/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: matrix_ops.h,v 1.8 2008/09/23 14:42:03 cvsuser Exp $
 */


#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <math.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif


#include "except.h"


/*!
	\brief 	Matrix operations includes vector and matrix operations.
	
	\details Matrix operations includes vector and matrix operations. These functions are: 
		
	- vector compare
	- vector dot product
	- vector magnitude 
	- vector normalize 
	- vector cross product
	- vector scalar multiply
	- vector copy
	- vector split / join
	- matrix vector product
	- matrix matrix product
	- matrix determinant
	- matrix identity
	- matrix transpose
	
 
*/ 


/**
 * @addtogroup Matrix  Vector Matrix Operations API
 */
/** @{ */



/** 
 * Vector Comparison
 * 
 * @param n Input. Number of vector elements.
 * @param vector1 Input. n-vector 1.
 * @param vector2  Input. n-vector 2.
 * @param fuzzVector Input. n-vector. How close the two vectors are considered to be equal.
 * 
 * @return It returns zero if not equal. Otherwise, it returns one if two vectors are equal.
 */
int vectorCompare(const int n, const double *vector1, const double *vector2, const double *fuzzVector);

/** 
 * Vector Dot Product
 * 
 * @param n Input. Number of vector elements.
 * @param vector1 Input. n-vector 1.
 * @param vector2 Input. n-vector 2.
 * 
 * @return It returns the dot product result of two vectors.
 */
double vectorDot(const int n, const double *vector1, const double *vector2);

/** 
 * Vector Magnitude
 * 
 * @param n Input. Number of vector elements.
 * @param vector Input. n-vector.
 * 
 * @return It returns the magnitude of the vector.
 */
double vectorMagnitude(const int n, const double *vector);

/** 
 * Unitize Vector
 * 
 * @param n Input. Number of vector elements.
 * @param vector Input. n-vector.
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * a divied-by-zero error occurs.
 */
void vectorNormalize(const int n, double *vector);
/** 
 * Vector Cross Product
 * 
 * @param vector1 Input. 3-vector 1.
 * @param vector2 Input. 3-vector 2.
 * @param resultVector Output. 3-vector. The cross product result.
 * 
 */
void vectorCross(const double *vector1, const double *vector2, double *resultVector);

/** 
 * Vector Scaling
 *
 * This function performs a vector-vector operation defined as X = alpha*X.
 *
 * @param n Input. Number of vector elements.
 * @param alpha Input. Scalar.
 * @param vector Input. n-vector.
 * 
 * @return 
 */
void vectorScale(const int n, const double alpha, double *vector);

/** 
 * Copy Vector
 * 
 * This function performs a vector-vector operation defined as Y = X.
 * 
 * @param n Input. Number of vector elements.
 * @param srcVector Input. n-vector.
 * @param destVector Output. n-vector.
 * 
 */
void vectorCopy(const int n, const double *srcVector, double *destVector);

/** 
 * Scalar-Vector Product
 *
 * This function performs a vector-vector operation defined as y = alpha*x + y.
 * 
 * @param n Input. Number of vector elements.
 * @param alpha Input. Scalar
 * @param x Input. n-vector.
 * @param y Output. n-vector.
 * 
 */
void vectorAxpy(const int n, const double alpha, const double *x, double *y);

/** 
 * Zero Vector
 * 
 * This function sets all the elements of a vector to zeros.
 *
 * @param n Input. Number of vector elements.
 * @param vector Output. n-vector.
 * 
 */
void vectorZeros(const int n, double *vector);

/** 
 * Split Vector
 * 
 * This function splits a n+m vector orgVector into a n-vector vector1 and a m-vector vector2.
 * 
 * @param n Input. Number of vector1 vector elements.
 * @param m Input. Number of vector2 vector elements.
 * @param orgVector Input. n+m vector.
 * @param vector1 Output. n-vector.
 * @param vector2 Output. m-vector.
 * 
 */
void vectorSplit(const int n, const int m, const double *orgVector, double *vector1, double *vector2);

/** 
 * Join Vector
 * 
 * This function joins a n-vector vector1 and a m-vector vector2 into a n+m vector resultVector.
 *
 * @param n Input. Number of vector1 vector elements.
 * @param m Input. Number of vector2 vector elements.
 * @param vector1 Input. n-vector.
 * @param vector2 Input. m-vector.
 * @param resultVector Output. n+m vector.
 * 
 */
void vectorJoin(const int n, const int m, const double *vector1, const double *vector2, double *resultVector);

/** 
 * 4x4 Matrix-Vector Product
 *
 * This function performs a 4x4 matrix-vector operation defined as  y = alpha*a*x + beta*y or
 * y = alpha*a'*x + beta*y. a' is the transpose of a.
 * 
 * @param transA Input. Specifies the operation to be performed. N or n - No transpose. T or t - Transpose.
 * @param alpha Input. Scalar.
 * @param a Input. 4x4 matrix.
 * @param x Input. 4-vector.
 * @param beta Input. Scalar.
 * @param y Output. 4-vector.
 * 
 */
void matrixMvp(const char transA, const double alpha, const double *a, const double *x, const double beta, double *y);
/**
 * 4x4 Matrix-Matrix Product 
 *
 * This function performs a 4x4 matrix-matrix operation defined as c =
 * alpha*op(a)*op(b) + beta*c, where op(x) is one of op(x) = x or
 * op(x) = x'. x' is the transpose of x.
 *
 * @param transA Input. Specifies the operation to be performed on A. N or n - No transpose. T or t - Transpose.
 * @param transB Input. Specifies the operation to be performed on B. N or n - No transpose. T or t - Transpose.
 * @param alpha Input. Scalar.
 * @param a Input. 4x4 matrix.
 * @param b Input. 4x4 matrix.
 * @param beta Input. Scalar.
 * @param c Output. 4x4 matrix.
 *
 * @return 
 */
void matrixMmp(const char transA, const char transB, const double alpha, const double *a, const double *b, const double beta, double *c);

/** 
 * 4x4 Matrix Determint
 * 
 * This function computes the determint of a 4x4 matrix.
 *
 * @param matrix Input. 4x4 matrix. 
 * 
 * @return The determint of the matrix.
 */
double matrixDeterminant(const double *matrix);


/** 
 * 4x4 Matrix Transpose
 * 
 * This function transposes a matrix.
 *
 * @param matrix Input/Output. 4x4 matrix. 
 * 
 */
void matrixTranspose(double *matrix);


/** 
 * 4x4 Identity Matrix. 
 *
 * This function sets an 4x4 identity matrix.
 * 
 * @param matrix Input/Output. 4x4 matrix. 
 * 
 */
void matrixIdentity(double *matrix);


/** @} */

extern double ddot_(const int *n, const double *dx, const int *incx, const double *dy, const int *incy);
extern double dnrm2_(const int *n, const double *x, const int *incx);
extern int dscal_(const int *n, const double *da, double *dx, const int *incx);
extern int dcopy_(const int *n, const double *dx, const int *incx,  double *dy, const int *incy);
extern int daxpy_(const int *n, const double *da, const double *dx, const int *incx, double *dy, const int *incy);
extern int dgemv_(const char *trans, const int *m, const int *n, const double *alpha, 
		  const double *a, const int *lda, const double *x, const int *incx, 
		  const double *beta, double *y, const int *incy);

extern int dgemm_(const char *transa, const char *transb, const int *m, const int *n, 
		  const int *k, const double *alpha, const double *a, const int *lda,
		  const double *b, const int *ldb, const double *beta, double *c,
		  const int *ldc);


#endif
