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
 * Revision     : $Id: quaternion.c,v 1.4 2008/09/09 15:22:53 cvsuser Exp $
 */


#ifndef QUATERNION_H
#include "quaternion.h"
#endif

#define MY_R rpyVector[0]
#define MY_P rpyVector[1]
#define MY_Y rpyVector[2]

#define MY_QS quaternion[0]
#define MY_QX quaternion[1]
#define MY_QY quaternion[2]
#define MY_QZ quaternion[3]

#define MY_M00  hMatrix[0]
#define MY_M01  hMatrix[4]
#define MY_M02  hMatrix[8]
#define MY_M03  hMatrix[12]
#define MY_M10  hMatrix[1]
#define MY_M11  hMatrix[5]
#define MY_M12  hMatrix[9]
#define MY_M13  hMatrix[13]
#define MY_M20  hMatrix[2]
#define MY_M21  hMatrix[6]
#define MY_M22  hMatrix[10]
#define MY_M23  hMatrix[14]
#define MY_M30  hMatrix[3]
#define MY_M31  hMatrix[7]
#define MY_M32  hMatrix[11]
#define MY_M33  hMatrix[15]


int EulerRPYToQuat(const double *rpyVector, double *quaternion) {
  double quatY[4] = { cos(MY_Y/2.), 0., 0., sin(MY_Y/2.) };
  double quatP[4] = { cos(MY_P/2.), 0., sin(MY_P/2.), 0. };
  double quatR[4] = { cos(MY_R/2.), sin(MY_R/2.), 0., 0. };

  QuatQuatMult(quatY, quatP, quaternion);
  QuatQuatMult(quaternion,  quatR, quaternion);
  return 0;
}


int QuatToEulerRPY(const double *quaternion, double *rpyVector) {
  double matrix_00,matrix_01,matrix_02;
  double matrix_10,matrix_11,matrix_12;
  double matrix_20,matrix_21,matrix_22;

  matrix_00 = 1 - 2 * (SQ(MY_QY) + SQ(MY_QZ));             // 1 - (2Y^2 + 2Z^2)
  matrix_10 = 2 * (MY_QX * MY_QY + MY_QZ * MY_QS);         // 2XY + 2ZS
  matrix_20 = 2 * (MY_QZ * MY_QX - MY_QY * MY_QS);         // 2XZ - 2YS

  matrix_01 = 2 * (MY_QX * MY_QY - MY_QZ * MY_QS);         // 2XY - 2ZS
  matrix_11 = 1 - 2 * (SQ(MY_QZ) + SQ(MY_QX));             // 1 - (2X^2 + 2Z^2)
  matrix_21 = 2 * (MY_QY * MY_QZ + MY_QX * MY_QS);         // 2YZ + 2XS

  matrix_02 = 2 * (MY_QZ * MY_QX + MY_QY * MY_QS);         // 2XZ + 2YS
  matrix_12 = 2 * (MY_QY * MY_QZ - MY_QX * MY_QS);         // 2YZ - 2XS
  matrix_22 = 1 - 2 * (SQ(MY_QX) + SQ(MY_QY));             // 1 - (2X^2 + 2Y^2)

  MY_P = atan2(-matrix_20, sqrt(SQ(matrix_00) + SQ(matrix_10)));
  
  if (fabs(MY_P - HALF_PI) < RADIAN_FUZZ) {
    MY_R = atan2(matrix_01, matrix_11);
    MY_P = HALF_PI;         
    MY_Y = 0.0;
  } else if (fabs(MY_P + HALF_PI) < RADIAN_FUZZ) {
    MY_R = -atan2(matrix_21, matrix_11);
    MY_P = -HALF_PI;      
    MY_Y = 0.0;
  } else {
    MY_R = atan2(matrix_21, matrix_22);
    MY_Y = atan2(matrix_10, matrix_00);
  }
  return 0;
}


/* resultQuaternion = quaternion1 * quaternion2 */
int QuatQuatMult(double *quaternion1, double *quaternion2, double *resultQuaternion) {

  double vector1[] = {quaternion1[1], quaternion1[2], quaternion1[3]};
  double vector2[] = {quaternion2[1], quaternion2[2], quaternion2[3]};
  double resultVector[3];
  double quaternion1_0=quaternion1[0];
  double quaternion2_0=quaternion2[0];
  
  resultQuaternion[0] = quaternion1_0*quaternion2_0 - vectorDot(3, vector1, 1, vector2, 1);
  vectorCross(vector1, vector2, resultVector);
  vectorAxpy(3, quaternion1_0, vector2, resultVector);
  vectorAxpy(3, quaternion2_0, vector1, resultVector);

  resultQuaternion[1] = resultVector[0]; 
  resultQuaternion[2] = resultVector[1]; 
  resultQuaternion[3] = resultVector[2];
  return 0;
}


/* resultQuaternion = quaternion1 / quaternion2 */
int QuatQuatDiv(double *quaternion1, double *quaternion2, double *resultQuaternion) {
  double invQuaternion[4];
  vectorCopy(4, quaternion2, invQuaternion);
  QuatInverse(invQuaternion);
  QuatQuatMult(quaternion1, invQuaternion, resultQuaternion);
  return 0;
}

int QuatInverse(double *quaternion) {
  double norm=SQ(QuatMagnitude(quaternion));
  if (DOUBLE_IS_ZERO(norm)) {
    Throw DIVIDED_BY_ZERO;
  }
  QuatConjugate(quaternion);
  vectorScale(4, 1.0f/norm, quaternion);
  return 0;
}


int QuatConjugate(double *quaternion) {
  quaternion[0] =  quaternion[0];
  quaternion[1] = -quaternion[1];
  quaternion[2] = -quaternion[2];
  quaternion[3] = -quaternion[3];
  return 0;
}

double QuatMagnitude(const double *quaternion) {
  return vectorMagnitude(4,quaternion);
}

/* vector = quaternion * vector1 * quaternion^1 */
int QuatVectorMult(double *quaternion, double *vector, double *resultVector) {
  double resultQuaternion[4], tmpQuaternion[4];

  tmpQuaternion[1] = vector[0];
  tmpQuaternion[2] = vector[1];
  tmpQuaternion[3] = vector[2];
  tmpQuaternion[0] = 0;
  QuatQuatMult(quaternion, tmpQuaternion, resultQuaternion);

  vectorCopy(4, quaternion, tmpQuaternion);
  QuatInverse(tmpQuaternion);
  QuatQuatMult(resultQuaternion, tmpQuaternion, resultQuaternion);

  resultVector[0] = resultQuaternion[1];
  resultVector[1] = resultQuaternion[2];
  resultVector[2] = resultQuaternion[3];
  return 0;
}

int HMatrixToQuat(const double *hMatrix, double *quaternion) {
  double T;
  double S;

  // compute trace of matrix
  T = 1 + MY_M00 + MY_M11 + MY_M22;
  if ( T > RADIAN_FUZZ ) {
      S = sqrt(T) * 2;
      MY_QX = (MY_M21 - MY_M12) / S;
      MY_QY = (MY_M02 - MY_M20) / S;
      MY_QZ = (MY_M10 - MY_M01) / S;
      MY_QS = 0.25 * S;
  } else {
    if ( MY_M00 > MY_M11 && MY_M00 > MY_M22 ) {   // Column 0:
      S  = sqrt( 1.0 + MY_M00 - MY_M11 - MY_M22 ) * 2;
      MY_QX = 0.25 * S;
      MY_QY = (MY_M10 + MY_M01) / S;
      MY_QZ = (MY_M02 + MY_M20) / S;
      MY_QS = (MY_M21 - MY_M12) / S;
    } else if ( MY_M11 > MY_M22 ) {              // Column 1:
      S = sqrt( 1.0 + MY_M11 - MY_M00 - MY_M22 ) * 2;
      MY_QX = (MY_M10 + MY_M01) / S;
      MY_QY = 0.25 * S;
      MY_QZ = (MY_M21 + MY_M12) / S;
      MY_QS = (MY_M02 - MY_M20) / S;
    } else {                                     // Column 2:
      S = sqrt( 1.0 + MY_M22 - MY_M00 - MY_M11 ) * 2;
      MY_QX = (MY_M02 + MY_M02) / S;
      MY_QY = (MY_M21 + MY_M12) / S;
      MY_QZ = 0.25 * S;
      MY_QS = (MY_M10 - MY_M01) / S;
    }
  }
  return 0;
}

int QuatToHMatrix(const double *quaternion, double *hMatrix) {

  matrixIdentity(hMatrix);

  MY_M00 = 1 - 2 * (SQ(MY_QY) + SQ(MY_QZ));             // 1 - (2Y^2 + 2Z^2)
  MY_M10 = 2 * (MY_QX * MY_QY + MY_QZ * MY_QS);         // 2XY + 2ZS
  MY_M20 = 2 * (MY_QZ * MY_QX - MY_QY * MY_QS);         // 2XZ - 2YS

  MY_M01 = 2 * (MY_QX * MY_QY - MY_QZ * MY_QS);         // 2XY - 2ZS
  MY_M11 = 1 - 2 * (SQ(MY_QZ) + SQ(MY_QX));             // 1 - (2X^2 + 2Z^2)
  MY_M21 = 2 * (MY_QY * MY_QZ + MY_QX * MY_QS);         // 2YZ + 2XS

  MY_M02 = 2 * (MY_QZ * MY_QX + MY_QY * MY_QS);         // 2XZ + 2YS
  MY_M12 = 2 * (MY_QY * MY_QZ - MY_QX * MY_QS);         // 2YZ - 2XS
  MY_M22 = 1 - 2 * (SQ(MY_QX) + SQ(MY_QY));             // 1 - (2X^2 + 2Y^2)
  return 0;
}

int QuatNormalize(double *quaternion) {
  double size = QuatMagnitude(quaternion);

  if (DOUBLE_IS_ZERO(size)) {
    Throw DIVIDED_BY_ZERO;
  }
  
  if (MY_QS >= 0.0) {
    vectorScale(4, 1.0f/size, quaternion);
  } else {
    vectorScale(4, -1.0f/size, quaternion);
  }
  return 0;
}

int RotAxisToQuat(const Axis_t axis, const double theta, double *quaternion) {
  double sh;

  sh  = sin(theta*0.5);
  MY_QS = cos(theta*0.5);

  switch (axis) {
  case AXIS_X:
    MY_QX = sh;
    MY_QY = 0.0;
    MY_QZ = 0.0;
    break;
  case AXIS_Y:
    MY_QX = 0.0;
    MY_QY = sh;
    MY_QZ = 0.0;
    break;
  case AXIS_Z:
    MY_QX = 0.0;
    MY_QY = 0.0;
    MY_QZ = sh;
    break;
  default:
    Throw UNRECOGNIZED_ENUM_ITEM;
  }

  if( MY_QS < 0.0 ) {
    vectorScale(4, -1.0f, quaternion);
  }
  return 0;
}

int QuatToRotVector(const double *quaternion, double *theta, double *vector) 
{
  double sh;

  sh = sqrt(SQ(MY_QX) + SQ(MY_QY) + SQ(MY_QZ));

  if (sh > RADIAN_FUZZ) 
	{
    *theta = 2.0 * atan2(sh, MY_QS);
    vector[0] = MY_QX / sh;
    vector[1] = MY_QY / sh;
    vector[2] = MY_QZ / sh;
  } 
	else 
	{
    *theta = 0.0;
    vector[0] = 0.0;
    vector[1] = 0.0;
    vector[2] = 0.0;
  }
  return 0;
}


int RotVectorToQuat(const double theta, const double *vector, double *quaternion) 
{
  double sh;

  if (CLOSE(theta, 0.0, RADIAN_FUZZ)) 
	{
    MY_QS = 1.0f;
    MY_QX = MY_QY = MY_QZ = 0.0;
  }
  
  sh  = sin(theta * 0.5);
  MY_QS = cos(theta * 0.5);
  

  if (MY_QS >= 0.0) 
	{
    MY_QX = vector[0] * sh;
    MY_QY = vector[1] * sh;
    MY_QZ = vector[2] * sh;
  } else {
    MY_QS *= -1;
    MY_QX = -vector[0] * sh;
    MY_QY = -vector[1] * sh;
    MY_QZ = -vector[2] * sh;
  }
  return 0;
}
