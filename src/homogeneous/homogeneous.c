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
 * Revision     : $Id: homogeneous.c,v 1.5 2008/09/17 15:33:30 cvsuser Exp $
 */

#ifndef HOMOGENEOUS_H
#include "homogeneous.h"
#endif


#define MY_R rpyVector[0]
#define MY_P rpyVector[1]
#define MY_Y rpyVector[2]


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

static int RotX(const double alpha, double *hMatrix);
static int RotY(const double beta, double *hMatrix);
static int RotZ(const double gamma, double *hMatrix);



int HMatrixSetTranslation(const double *vector, double *hMatrix) 
{
  MY_M03 = vector[0];
  MY_M13 = vector[1];
  MY_M23 = vector[2];

  return 0;
}

int HMatrixGetTranslation(const double *hMatrix, double *vector) 
{
  vector[0] = MY_M03;
  vector[1] = MY_M13;
  vector[2] = MY_M23;

  return 0;
}

int RotVectorToHMatrix(const double theta, const double *vector, double *hMatrix) {
   double c, s, omc;
   matrixIdentity(hMatrix);

   s=sin(theta);
   c=cos(theta);
   omc = 1 - c;

   MY_M00 = c + SQ(vector[0]) * omc; 
   MY_M01 = -vector[2] * s + vector[0] * vector[1] * omc;
   MY_M02 =  vector[1] * s + vector[0] * vector[2] * omc;
   
   MY_M10 =  vector[2] * s + vector[1] * vector[0] * omc;
   MY_M11 = c + SQ(vector[1]) * omc;
   MY_M12 = -vector[0] * s + vector[1] * vector[2] * omc;
   
   MY_M20 = -vector[1] * s + vector[2] * vector[0] * omc;
   MY_M21 =  vector[0] * s + vector[2] * vector[1] * omc;
   MY_M22 = c + SQ(vector[2]) * omc;

   return 0;
}

int HMatrixToRotVector(const double *hMatrix, double *theta, double *vector) 
{
   double a, b, c;
   a = (MY_M21-MY_M12);
   b = (MY_M02-MY_M20);
   c = (MY_M10-MY_M01);

   *theta = atan2(sqrt(SQ(a) + SQ(b) + SQ(c)),(MY_M00 + MY_M11 + MY_M22 - 1));

   vector[0] = (MY_M21-MY_M12)/(2*sin(*theta));
   vector[1] = (MY_M02-MY_M20)/(2*sin(*theta));
   vector[2] = (MY_M10-MY_M01)/(2*sin(*theta));
   vectorNormalize(3, vector);
   return 0;
}

/**
	Apply rotation angle about x-axis and insert into homogeneous matrix
*/
int RotX(const double alpha, double *hMatrix) 
{
  double c,s;

  matrixIdentity(hMatrix);
  c = cos(alpha);
  s = sin(alpha);

  MY_M11 = c;
  MY_M22 = c;
  MY_M12 = -s;
  MY_M21 = s;

  return 0;
}

int RotY(const double beta, double *hMatrix) 
{
  double c,s;
  matrixIdentity(hMatrix);
  c = cos(beta);
  s = sin(beta);

  MY_M00 = c;
  MY_M22 = c;
  MY_M02 = s;
  MY_M20 = -s;
  return 0;
}

int RotZ(const double gamma, double *hMatrix) {
  double c,s;
  matrixIdentity(hMatrix);
  c = cos(gamma);
  s = sin(gamma);

  MY_M00 = c;
  MY_M11 = c;
  MY_M01 = -s;
  MY_M10 = s;
  return 0; 
}
/**
	RotAxisToHMatrix rotation applied to homogeneous matrix
	
	
*/
int RotAxisToHMatrix(Axis_t axis, const double theta, double *hMatrix) 
{
  switch (axis) 
	{
  case AXIS_X:
    RotX(theta,hMatrix);
    break;
  case AXIS_Y:
    RotY(theta,hMatrix);
    break;
  case AXIS_Z:
    RotZ(theta,hMatrix);
    break;
  default:
    Throw UNRECOGNIZED_ENUM_ITEM;
  }
  return 0;
}

int EulerRPYToHMatrix(const double *rpyVector, double *hMatrix) 
{
  double cr, sr, cp, sp, cy, sy;

  matrixIdentity(hMatrix);
  cr = cos(MY_R);
  sr = sin(MY_R);
  cp = cos(MY_P);
  sp = sin(MY_P);
  cy = cos(MY_Y);
  sy = sin(MY_Y);

  MY_M00 = cp*cy;
  MY_M01 = sr*sp*cy-cr*sy;
  MY_M02 = cr*sp*cy+sr*sy;
  
  MY_M10 = cp*sy;
  MY_M11 = sr*sp*sy+cr*cy;
  MY_M12 = cr*sp*sy-sr*cy;
  
  MY_M20 = -sp;
  MY_M21 = sr*cp;
  MY_M22 = cr*cp;
  return 0;
}

int HMatrixToEulerRPY(const double *hMatrix, double *rpyVector) 
{
  MY_P = atan2(-MY_M20, sqrt(SQ(MY_M00) + SQ(MY_M10)));
  
  if (fabs(MY_P - HALF_PI) < RADIAN_FUZZ) {
    MY_R = atan2(MY_M01, MY_M11);
    MY_P =HALF_PI;       
    MY_Y = 0.0;
  } else if (fabs(MY_P + HALF_PI) < RADIAN_FUZZ) {
    MY_R = -atan2(MY_M21, MY_M11);
    MY_P = -HALF_PI;        
    MY_Y = 0.0;
  } else {
    MY_R = atan2(MY_M21, MY_M22);
    MY_Y = atan2(MY_M10, MY_M00);
  }
  return 0;
}

int HMatrixNormalize(double *hMatrix) 
{
  double v1[]={MY_M01, MY_M11, MY_M21};
  double v2[]={MY_M02, MY_M12, MY_M22};
  double v[3];

  vectorCross(v1, v2, v);
  vectorNormalize(3,v);
  vectorNormalize(3,v1);
  vectorNormalize(3,v2);

  MY_M30=MY_M31=MY_M32=0.0f;
  MY_M33=1.0f;
  MY_M00=v[0];  MY_M10=v[1];  MY_M20=v[2];
  MY_M01=v1[0]; MY_M11=v1[1]; MY_M21=v1[2];
  MY_M02=v2[0]; MY_M12=v2[1]; MY_M22=v2[2];
  return 0;
}


int HMatrixInverse(double *hMatrix) 
{
  double T[16];

  vectorCopy(16,hMatrix,T);

  hMatrix[0]=T[0]; hMatrix[1]=T[4]; hMatrix[2] =T[8];
  hMatrix[4]=T[1]; hMatrix[5]=T[5]; hMatrix[6] =T[9];
  hMatrix[8]=T[2]; hMatrix[9]=T[6]; hMatrix[10]=T[10];

  hMatrix[12] = -(hMatrix[0]*T[12] + hMatrix[4]*T[13] + hMatrix[8] *T[14]);
  hMatrix[13] = -(hMatrix[1]*T[12] + hMatrix[5]*T[13] + hMatrix[9] *T[14]);
  hMatrix[14] = -(hMatrix[2]*T[12] + hMatrix[6]*T[13] + hMatrix[10]*T[14]);
  return 0;
}


int HMatrixLink(const double linkLength, const double twistAngle, const double jointOffset, const double jointAngle, double *hMatrix) 
{
   double ct, st, ca, sa;

   matrixIdentity(hMatrix);

   ct = cos(jointAngle);
   st = sin(jointAngle);
   ca = cos(twistAngle);
   sa = sin(twistAngle);

   MY_M00 = ct;
   MY_M10 = st * ca;
   MY_M20 = st * sa;
   MY_M01 = -st;
   MY_M11 = ca * ct;
   MY_M21 = sa * ct;
   MY_M02 = 0;
   MY_M12 = -sa;
   MY_M22 = ca;
   
   MY_M03 = linkLength;
   MY_M13 = -sa * jointOffset;
   MY_M23 = ca * jointOffset;
   return 0;
}


