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
 * Revision     : $Id: matrix_ops.c,v 1.3 2008/09/03 22:04:39 cvsuser Exp $
 */



#ifndef MATRIX_OPS_H
#include "matrix_ops.h"
#endif



#define MY_M00  matrix[0]
#define MY_M01  matrix[4]
#define MY_M02  matrix[8]
#define MY_M03  matrix[12]
#define MY_M10  matrix[1]
#define MY_M11  matrix[5]
#define MY_M12  matrix[9]
#define MY_M13  matrix[13]
#define MY_M20  matrix[2]
#define MY_M21  matrix[6]
#define MY_M22  matrix[10]
#define MY_M23  matrix[14]
#define MY_M30  matrix[3]
#define MY_M31  matrix[7]
#define MY_M32  matrix[11]
#define MY_M33  matrix[15]

int vectorCompare(const int n, const double *vector1, const double *vector2, const double *fuzzVector) {
  int i;
  for(i=0; i<n; i++) {
    if (fabs(vector1[i] - vector2[i]) > fuzzVector[i]) {
      return 1;
    }
  }
  return 0;
}


double vectorDot(const int n, const double *vector1, const double *vector2) {
  int incx=1;
  int incy=1;
  return ddot_(&n, vector1, &incx, vector2, &incy);
}

double vectorMagnitude(const int n, const double *vector) {
  int incx=1;
  return dnrm2_(&n, vector, &incx);
}

void vectorNormalize(const int n, double *vector) {
  double norm=vectorMagnitude(n,vector);

  if (DOUBLE_IS_ZERO(norm)) {
    Throw DIVIDED_BY_ZERO;
  }
  vectorScale(n,1.0f/norm,vector);
}

void vectorCross(const double *vector1, const double *vector2, double *resultVector) {
   resultVector[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
   resultVector[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
   resultVector[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

void vectorScale(const int n, const double alpha, double *vector) {
  int incx=1;
  dscal_(&n, &alpha, vector, &incx);
}

void vectorCopy(const int n, const double *srcVector, double *destVector) {
  int incx=1;
  int incy=1;
  dcopy_(&n, srcVector, &incx, destVector, &incy);
}

void vectorAxpy(const int n, const double alpha, const double *x, double *y) {
  int incx=1;
  int incy=1;  
  daxpy_(&n, &alpha, x, &incx, y, &incy);
}

void vectorZeros(const int n, double *vector) {
  int i;
  for(i=0; i<n; i++) {
    vector[i]=0.0f;
  }
}

void vectorSplit(const int n, const int m, const double *orgVector, double *vector1, double *vector2) {
  int i;
  for(i=0; i<n; i++) {
    vector1[i] = orgVector[i];
  }
  for(i=0; i<m; i++) {
    vector2[i] = orgVector[i + n];
  }
}

void vectorJoin(const int n, const int m, const double *vector1, const double *vector2, double *resultVector) {
  int i;
  for(i = 0; i < n; i++) {
    resultVector[i] = vector1[i];
  }
  for(i = 0; i < m; i++) {
    resultVector[i + n] = vector2[i];
  }
}

void matrixMvp(const char transA, const double alpha, const double *a, const double *x, const double beta, double *y) {
  int m,n,lda,incx,incy;
  m=4; n=4; lda=4;
  incx=1; incy=1;
  dgemv_(&transA, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


void matrixMmp(const char transA, const char transB, const double alpha, const double *a, const double *b, const double beta, double *c) {
  int m,n,k,lda,ldb,ldc;
  m=4; n=4; k=4;
  lda=4; ldb=4; ldc=4;
  dgemm_(&transA, &transB, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}

double matrixDeterminant(const double *matrix) {
  return MY_M00 * (MY_M11 * (MY_M22 * MY_M33 - MY_M32 * MY_M23) + MY_M21 * (MY_M32 * MY_M13 - MY_M12 * MY_M33) + MY_M31 * (MY_M12 * MY_M23 - MY_M22 * MY_M13))
       - MY_M10 * (MY_M21 * (MY_M32 * MY_M03 - MY_M02 * MY_M33) + MY_M31 * (MY_M02 * MY_M23 - MY_M22 * MY_M03) + MY_M01 * (MY_M22 * MY_M33 - MY_M32 * MY_M23))
       + MY_M20 * (MY_M31 * (MY_M02 * MY_M13 - MY_M12 * MY_M03) + MY_M01 * (MY_M12 * MY_M33 - MY_M32 * MY_M13) + MY_M11 * (MY_M32 * MY_M03 - MY_M02 * MY_M33))
       - MY_M30 * (MY_M01 * (MY_M12 * MY_M23 - MY_M22 * MY_M13) + MY_M11 * (MY_M22 * MY_M03 - MY_M02 * MY_M23) + MY_M21 * (MY_M02 * MY_M13 - MY_M12 * MY_M03));
}

void matrixTranspose(double *matrix) {
  double T[16];
  vectorCopy(16, matrix,T);
  MY_M01 = T[1];
  MY_M02 = T[2];
  MY_M03 = T[3];
  MY_M10 = T[4];
  MY_M12 = T[6];
  MY_M13 = T[7];
  MY_M20 = T[8];
  MY_M21 = T[9];
  MY_M23 = T[11];
  MY_M30 = T[12];
  MY_M31 = T[13];
  MY_M32 = T[14];
}

void matrixIdentity(double *matrix) {
  MY_M00 = 1.0;
  MY_M01 = 0.0;
  MY_M02 = 0.0;
  MY_M03 = 0.0;
  MY_M10 = 0.0;
  MY_M11 = 1.0;
  MY_M12 = 0.0;
  MY_M13 = 0.0;
  MY_M20 = 0.0;
  MY_M21 = 0.0;
  MY_M22 = 1.0;
  MY_M23 = 0.0;
  MY_M30 = 0.0;
  MY_M31 = 0.0;
  MY_M32 = 0.0;
  MY_M33 = 1.0;
}


