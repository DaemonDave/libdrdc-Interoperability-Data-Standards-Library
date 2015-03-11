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
 * Revision     : $Id: wrapper_cpp.cc,v 1.4 2008/09/15 22:54:14 cvsuser Exp $
 */


#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libdrdc.h"
//#include "sglib.h"
#include "wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "matrix_ops.h"
#include "homogeneous.h"
#include "quaternion.h"
#include "coordinate.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

drdc_lPosn::drdc_lPosn() {
  unsigned char dsize = 3;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_lPosn::set(double x, double y, double z) {
  wp_set3(this, x, y, z);
}

void drdc_lPosn::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_lPosn::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_lPosn::compare(drdc_lPosn localPosition, drdc_lPosn fuzz) {
  return wp_compare(this, &localPosition, &fuzz);
}


double drdc_lPosn::getX() {return wp_index(this, 0);}
double drdc_lPosn::getY() {return wp_index(this, 1);}
double drdc_lPosn::getZ() {return wp_index(this, 2);}

drdc_lPosn &drdc_lPosn::operator = (drdc_lPosn localPosition) {
  wp_copy(&localPosition, this);
  return *this;
}

double drdc_lPosn::operator [] (int n) {
  return wp_index(this, n);
}

drdc_lPosn drdc_lPosn::operator +(drdc_lPosn localPosition) {
  drdc_lPosn result;
  wp_plus(this, &localPosition, &result);
  return result;
}

drdc_lPosn drdc_lPosn::operator -() {
  drdc_lPosn result;
  wp_negate(this, &result);
  return result;
}
  
drdc_lPosn drdc_lPosn::operator -(drdc_lPosn localPosition) {
  drdc_lPosn result;
  wp_minus(this, &localPosition, &result);
  return result;
}

drdc_lPosn drdc_lPosn::operator *(double a) {
  drdc_lPosn result;
  wp_scale(this, a, &result);
  return result;
}

double drdc_lPosn::dot(drdc_lPosn localPosition) {
  return wp_dot(this, &localPosition);
}

drdc_lPosn drdc_lPosn::cross(drdc_lPosn localPosition) 
{
  drdc_lPosn result;
  wp_cross(this, &localPosition, &result);
  return result;
}

void drdc_lPosn::normalize() {
  wp_normalize(this);
} 

double drdc_lPosn::magnitude() {
  return wp_magnitude(this);
}

drdc_WUTMPosn drdc_lPosn::to_WUTMPosn(drdc_UTMZone_t zone) {
  drdc_WUTMPosn result;
  wp_copy(this, &result);
  result.setZone(zone);
  return result;
}

drdc_WPosn drdc_lPosn::to_WPosn(double falseElevation) {
  drdc_WPosn result;
  wp_lPosn_to_WPosn(this, falseElevation, &result);
  return result;
}

///////////////////////////////////////////

drdc_WUTMPosn::drdc_WUTMPosn() {
  unsigned char dsize = 3;
  drdc_Vector_t *ptr;
  this->zone.zoneNumber = 0;
  this->zone.zoneLetter = 'O';
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_WUTMPosn::set(double easting, double northing, double elevation) {
  wp_set3(this, easting, northing, elevation);
}

void drdc_WUTMPosn::set(const double *array) {
  wp_setFromArray(this, array);
}

void  drdc_WUTMPosn::setZone(drdc_UTMZone_t zone) {
  this->zone = zone;
}

drdc_UTMZone_t drdc_WUTMPosn::getZone() {
  return this->zone;
}


void drdc_WUTMPosn::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_WUTMPosn::compare(drdc_WUTMPosn worldUTMPosition, drdc_WUTMPosn fuzz) {
  return wp_compareUTM(this, &worldUTMPosition, &fuzz);
}


double drdc_WUTMPosn::getEasting() {return wp_index(this, 0);}
double drdc_WUTMPosn::getNorthing() {return wp_index(this, 1);}
double drdc_WUTMPosn::getElevation() {return wp_index(this, 2);}

drdc_WUTMPosn &drdc_WUTMPosn::operator = (drdc_WUTMPosn worldUTMPosition) {
  wp_copyUTM(&worldUTMPosition, this);
  //this->setZone(worldUTMPosition.zone);
  return *this;
}

double drdc_WUTMPosn::operator [] (int n) {
  return wp_index(this, n);
}

drdc_WUTMPosn drdc_WUTMPosn::operator +(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_plus(this, &worldUTMPosition, &result);
  return result;
}

drdc_WUTMPosn drdc_WUTMPosn::operator -() {
  drdc_WUTMPosn result;
  wp_negate(this, &result);
  return result;
}
  
drdc_WUTMPosn drdc_WUTMPosn::operator -(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_minus(this, &worldUTMPosition, &result);
  return result;
}

drdc_WUTMPosn drdc_WUTMPosn::operator *(double a) {
  drdc_WUTMPosn result;
  wp_scale(this, a, &result);
  return result;
}

double drdc_WUTMPosn::dot(drdc_WUTMPosn worldUTMPosition) {
  return wp_dot(this, &worldUTMPosition);
}

drdc_WUTMPosn drdc_WUTMPosn::cross(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_cross(this, &worldUTMPosition, &result);
  return result;
}

drdc_lPosn drdc_WUTMPosn::to_lPosn() {
  drdc_lPosn result;
  wp_copy(this, &result);
  return result;
}

drdc_WPosn drdc_WUTMPosn::to_WPosn() {
  drdc_WPosn result;
  wp_WUTMPosn_to_WPosn(this, &result);
  return result;
}

///////////////////////////////////////////

drdc_WPosn::drdc_WPosn() {
  unsigned char dsize = 3;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_WPosn::set(double longtitude, double latitude, double elevation) {
  wp_set3(this, longtitude, latitude, elevation);
}

void drdc_WPosn::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_WPosn::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_WPosn::compare(drdc_WPosn worldPosition, drdc_WPosn fuzz) {
  return wp_compare(this, &worldPosition, &fuzz);
}


double drdc_WPosn::getLongtitude() {return wp_index(this, 0);}
double drdc_WPosn::getLatitude() {return wp_index(this, 1);}
double drdc_WPosn::getElevation() {return wp_index(this, 2);}

drdc_WPosn &drdc_WPosn::operator = (drdc_WPosn worldPosition) {
  wp_copy(&worldPosition, this);
  return *this;
}

double drdc_WPosn::operator [] (int n) {
  return wp_index(this, n);
}



void drdc_WPosn::normalize() {
  wp_WPosnNormalize(this);
} 

drdc_lPosn drdc_WPosn::to_lPosn(double falseElevation) {
  drdc_lPosn result;
  wp_WPosn_to_lPosn(this, falseElevation,  &result);
  return result;
}

drdc_WUTMPosn drdc_WPosn::to_WUTMPosn() {
  drdc_WUTMPosn result;
  wp_WPosn_to_WUTMPosn(this, &result);
  return result;
}

// eOrient - euler RPY

drdc_eOrient::drdc_eOrient() {
  unsigned char dsize = 3;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_eOrient::set(double roll, double pitch, double yaw) {
  wp_set3(this, roll, pitch, yaw);
}

void drdc_eOrient::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_eOrient::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_eOrient::compare(drdc_eOrient eulerRPY, drdc_eOrient fuzz) {
  return wp_compare(this, &eulerRPY, &fuzz);
}


double drdc_eOrient::getRoll() {return wp_index(this, 0);}
double drdc_eOrient::getPitch() {return wp_index(this, 1);}
double drdc_eOrient::getYaw() {return wp_index(this, 2);}

drdc_eOrient &drdc_eOrient::operator = (drdc_eOrient eulerRPY) {
  wp_copy(&eulerRPY, this);
  return *this;
}

double drdc_eOrient::operator [] (int n) {
  return wp_index(this, n);
}


drdc_eOrient drdc_eOrient::operator +(drdc_eOrient eulerRPY) {
  drdc_eOrient result;
  wp_plus(this, &eulerRPY, &result);
  return result;
}

drdc_eOrient drdc_eOrient::operator -() {
  drdc_eOrient result;
  wp_negate(this, &result);
  return result;
}
  
drdc_eOrient drdc_eOrient::operator -(drdc_eOrient eulerRPY) {
  drdc_eOrient result;
  wp_minus(this, &eulerRPY, &result);
  return result;
}


drdc_eOrient drdc_eOrient::operator *(double a) {
  drdc_eOrient result;
  wp_scale(this, a, &result);
  return result;
}

drdc_HMatrix drdc_eOrient::to_HMatrix() {
  drdc_HMatrix result;
  wp_eOrient_to_HMatrix(this, &result);
  return result;
}

drdc_Orient drdc_eOrient::to_Orient() {
  drdc_Orient result;
  wp_eOrient_to_Orient(this, &result);
  return result;
}

// Orient - Quaternion

drdc_Orient::drdc_Orient() {
  unsigned char dsize = 4;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_Orient::set(double w, double x, double y, double z) {
  wp_set4(this, w, x, y, z);
}

void drdc_Orient::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_Orient::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_Orient::compare(drdc_Orient quaternion, drdc_Orient fuzz) {
  return wp_compare(this, &quaternion, &fuzz);
}


double drdc_Orient::getW() {return wp_index(this, 0);}
double drdc_Orient::getX() {return wp_index(this, 1);}
double drdc_Orient::getY() {return wp_index(this, 2);}
double drdc_Orient::getZ() {return wp_index(this, 3);}

drdc_Orient &drdc_Orient::operator = (drdc_Orient quaternion) {
  wp_copy(&quaternion, this);
  return *this;
}

double drdc_Orient::operator [] (int n) {
  return wp_index(this, n);
}


drdc_Orient drdc_Orient::operator +(drdc_Orient quaternion) {
  drdc_Orient result;
  wp_plus(this, &quaternion, &result);
  return result;
}

drdc_Orient drdc_Orient::operator -() {
  drdc_Orient result;
  wp_negate(this, &result);
  return result;
}
  
drdc_Orient drdc_Orient::operator -(drdc_Orient quaternion) {
  drdc_Orient result;
  wp_minus(this, &quaternion, &result);
  return result;
}


drdc_Orient drdc_Orient::operator *(double a) {
  drdc_Orient result;
  wp_scale(this, a, &result);
  return result;
}

drdc_Orient drdc_Orient::operator *(drdc_Orient quaternion) {
  drdc_Orient result;
  wp_QuatMult(this, &quaternion, &result);
  return result;
}

drdc_lPosn drdc_Orient::operator *(drdc_lPosn localPosition) {
  drdc_lPosn result;
  wp_QuatMultVec(this, &localPosition, &result);
  return result;
}

drdc_WUTMPosn drdc_Orient::operator *(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_QuatMultVec(this, &worldUTMPosition, &result);
  return result;
}

void drdc_Orient::normalize() {
  wp_QuatNormalize(this);
} 

double drdc_Orient::magnitude() {
  return wp_QuatMagnitude(this);
}

void drdc_Orient::fromRotAxis(const Axis_t axis, const double theta) {
  wp_QuatRotAxis(this, axis, theta);
}

void drdc_Orient::fromRotVec(double theta, drdc_lPosn unitVector) {
  wp_QuatFromRotVec(this, theta, &unitVector);
}

void drdc_Orient::toRotVec(double *theta, drdc_lPosn *unitVector) {
  wp_QuatToRotVec(this, theta, unitVector);
}

void drdc_Orient::identity() {
  wp_QuatIdentity(this);
}

drdc_Orient drdc_Orient::inverse() {
  drdc_Orient result;
  wp_QuatInverse(this, &result);
  return result;
}


drdc_HMatrix drdc_Orient::to_HMatrix() {
  drdc_HMatrix result;
  wp_Orient_to_HMatrix(this, &result);
  return result;
}

drdc_eOrient drdc_Orient::to_eOrient() {
  drdc_eOrient result;
  wp_Orient_to_eOrient(this, &result);
  return result;  
}

// HMatrix - Homogeneous Matrix

drdc_HMatrix::drdc_HMatrix() {
  unsigned char dsize = 16;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}


void drdc_HMatrix::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_HMatrix::toArray(double *array) 
{
  wp_toArray(this, array);
}

int drdc_HMatrix::compare(drdc_HMatrix homogeneous, drdc_HMatrix fuzz) {
  return wp_compare(this, &homogeneous, &fuzz);
}

drdc_lPosn drdc_HMatrix::getPosition() {
  drdc_lPosn result;
  wp_HMatrixGetTranslation(this, &result);
  return result;
}

void drdc_HMatrix::setPosition(drdc_lPosn localPosition) {
  wp_HMatrixSetTranslation(this, &localPosition);
}

drdc_HMatrix &drdc_HMatrix::operator = (drdc_HMatrix homogeneous) {
  wp_copy(&homogeneous, this);
  return *this;
}

double drdc_HMatrix::operator [] (int n) {
  return wp_index(this, n);
}


drdc_HMatrix drdc_HMatrix::operator +(drdc_HMatrix homogeneous) {
  drdc_HMatrix result;
  wp_plus(this, &homogeneous, &result);
  return result;
}

drdc_HMatrix drdc_HMatrix::operator -() {
  drdc_HMatrix result;
  wp_negate(this, &result);
  return result;
}
  
drdc_HMatrix drdc_HMatrix::operator -(drdc_HMatrix homogeneous) {
  drdc_HMatrix result;
  wp_minus(this, &homogeneous, &result);
  return result;
}


drdc_HMatrix drdc_HMatrix::operator *(double a) {
  drdc_HMatrix result;
  wp_scale(this, a, &result);
  return result;
}

drdc_HMatrix drdc_HMatrix::operator *(drdc_HMatrix homogeneous) {
  drdc_HMatrix result;
  wp_HMatrixMult(this, &homogeneous, &result);
  return result;
}

drdc_lPosn drdc_HMatrix::operator *(drdc_lPosn localPosition) {
  drdc_lPosn result;
  wp_HMatrixMultVec(this, &localPosition, &result);
  return result;
}

drdc_WUTMPosn drdc_HMatrix::operator *(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_HMatrixMultVec(this, &worldUTMPosition, &result);
  return result;
}


void drdc_HMatrix::normalize() {
  wp_HMatrixNormalize(this);
} 

drdc_HMatrix drdc_HMatrix::transpose() {
  drdc_HMatrix result;
  wp_HMatrixTranspose(this, &result);
  return result;
}

void drdc_HMatrix::fromRotAxis(const Axis_t axis, const double theta) {
  wp_HMatrixRotAxis(this, axis, theta);
}

void drdc_HMatrix::fromRotVec(double theta, drdc_lPosn unitVector) {
  wp_HMatrixFromRotVec(this, theta, &unitVector);
}

void drdc_HMatrix::toRotVec(double *theta, drdc_lPosn *unitVector) {
  wp_HMatrixToRotVec(this, theta, unitVector);
}

void drdc_HMatrix::identity() {
  wp_HMatrixIdentity(this);
}

drdc_HMatrix drdc_HMatrix::inverse() {
  drdc_HMatrix result;
  wp_HMatrixInverse(this, &result);
  return result;
}

drdc_lPose drdc_HMatrix::to_lPose() {
  drdc_lPose result;
  wp_HMatrix_to_lPose(this, &result);
  return result;
}

drdc_lePose drdc_HMatrix::to_lePose() {
  drdc_lePose result;
  wp_HMatrix_to_lePose(this, &result);
  return result;
}

drdc_Orient drdc_HMatrix::to_Orient() {
  drdc_Orient result;
  wp_HMatrix_to_Orient(this, &result);
  return result;
}

drdc_eOrient drdc_HMatrix::to_eOrient() {
  drdc_eOrient result;
  wp_HMatrix_to_eOrient(this, &result);
  return result;
}

void drdc_HMatrix::fromDH(double linkLength, double twistAngle, double jointOffset, double jointAngle) {
  wp_HMatrixFromDH(this, linkLength, twistAngle, jointOffset, jointAngle);
}

void drdc_HMatrix::fromLink(drdc_LinkSpecs_t linkSpecs, double jointOffsetOrAngle) {
  wp_HMatrixFromLink(this, &linkSpecs, jointOffsetOrAngle);
}

//Local Pose

drdc_lPose::drdc_lPose() {
  unsigned char dsize = 7;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_lPose::set(drdc_lPosn position, drdc_Orient orientation) {
  wp_setPose(this, &position,  &orientation);
}

void drdc_lPose::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_lPose::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_lPose::compare(drdc_lPose localPose, drdc_lPose fuzz) {
  return wp_compare(this, &localPose, &fuzz);
}

drdc_lPosn drdc_lPose::getPosition() {
  drdc_lPosn result;
  wp_getPosition(this, &result);
  return result;
}

drdc_Orient drdc_lPose::getOrientation() {
  drdc_Orient result;
  wp_getOrientation(this, &result);
  return result;
}

drdc_lPose &drdc_lPose::operator = (drdc_lPose localPose) {
  wp_copy(&localPose, this);
  return *this;
}

double drdc_lPose::operator [] (int n) {
  return wp_index(this, n);
}


drdc_lPose drdc_lPose::operator *(drdc_lPose localPose) {
  drdc_lPose result;
  wp_poseMult(this, &localPose, &result);
  return result;
}

drdc_lPosn drdc_lPose::operator *(drdc_lPosn localPosition) {
  drdc_lPosn result;
  wp_poseMultVec(this, &localPosition, &result);
  return result;
}

drdc_WPose drdc_lPose::to_WPose(double falseElevation) {
  drdc_WPose result;
  wp_lPose_to_WPose(this, falseElevation, &result);
  return result;
}

drdc_lePose drdc_lPose::to_lePose() {
  drdc_lePose result;
  wp_lPose_to_lePose(this, &result);
  return result;
}

drdc_HMatrix drdc_lPose::to_HMatrix() {
  drdc_HMatrix result;
  wp_lPose_to_HMatrix(this, &result);
  return result;
}


drdc_WUTMPose drdc_lPose::to_WUTMPose(drdc_UTMZone_t zone) {
  drdc_WUTMPose result;
  wp_copy(this, &result);
  result.setZone(zone);
  return result;
}

//Local Euler Pose

drdc_lePose::drdc_lePose() {
  unsigned char dsize = 6;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_lePose::set(drdc_lPosn position, drdc_eOrient orientation) {
  wp_setPose(this, &position,  &orientation);
}

void drdc_lePose::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_lePose::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_lePose::compare(drdc_lePose localEulerPose, drdc_lePose fuzz) {
  return wp_compare(this, &localEulerPose, &fuzz);
}

drdc_lPosn drdc_lePose::getPosition() {
  drdc_lPosn result;
  wp_getPosition(this, &result);
  return result;
}

drdc_eOrient drdc_lePose::getOrientation() {
  drdc_eOrient result;
  wp_getOrientation(this, &result);
  return result;
}

drdc_lePose &drdc_lePose::operator = (drdc_lePose localEulerPose) {
  wp_copy(&localEulerPose, this);
  return *this;
}

double drdc_lePose::operator [] (int n) {
  return wp_index(this, n);
}

drdc_lPose drdc_lePose::to_lPose() {
  drdc_lPose result;
  wp_lePose_to_lPose(this, &result);
  return result;
}

drdc_HMatrix drdc_lePose::to_HMatrix() {
  drdc_HMatrix result;
  wp_lePose_to_HMatrix(this, &result);
  return result;
}

//World Pose

drdc_WPose::drdc_WPose() {
  unsigned char dsize = 7;
  drdc_Vector_t *ptr;
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_WPose::set(drdc_WPosn position, drdc_Orient orientation) {
  wp_setPose(this, &position,  &orientation);
}

void drdc_WPose::set(const double *array) {
  wp_setFromArray(this, array);
}

void drdc_WPose::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_WPose::compare(drdc_WPose worldPose, drdc_WPose fuzz) {
  return wp_compare(this, &worldPose, &fuzz);
}

drdc_WPosn drdc_WPose::getPosition() {
  drdc_WPosn result;
  wp_getPosition(this, &result);
  return result;
}

drdc_Orient drdc_WPose::getOrientation() {
  drdc_Orient result;
  wp_getOrientation(this, &result);
  return result;
}

drdc_WPose &drdc_WPose::operator = (drdc_WPose worldPose) {
  wp_copy(&worldPose, this);
  return *this;
}

double drdc_WPose::operator [] (int n) {
  return wp_index(this, n);
}

drdc_lPose drdc_WPose::to_lPose(double falseElevation) {
  drdc_lPose result;
  wp_WPose_to_lPose(this, falseElevation, &result);
  return result;
}

drdc_WUTMPose drdc_WPose::to_WUTMPose() {
  drdc_WUTMPose result;
  wp_WPose_to_WUTMPose(this, &result);
  return result;
}


//World UTM Pose

drdc_WUTMPose::drdc_WUTMPose() {
  unsigned char dsize = 7;
  drdc_Vector_t *ptr;
  this->zone.zoneNumber = 0;
  this->zone.zoneLetter = 'O';
  ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->dsize = dsize;
  ptr->data = (double *) calloc(dsize, sizeof(double));
  if (ptr->data==NULL) Throw CALLOC_NULL_ERROR;
  this->vector = ptr;
}

void drdc_WUTMPose::set(drdc_WUTMPosn position, drdc_Orient orientation) {
  wp_setPose(this, &position,  &orientation);
}

void drdc_WUTMPose::set(const double *array) {
  wp_setFromArray(this, array);
}

void  drdc_WUTMPose::setZone(drdc_UTMZone_t zone) {
  this->zone = zone;
}

drdc_UTMZone_t  drdc_WUTMPose::getZone() {
  return this->zone;
}

void drdc_WUTMPose::toArray(double *array) {
  wp_toArray(this, array);
}

int drdc_WUTMPose::compare(drdc_WUTMPose worldUTMPose, drdc_WUTMPose fuzz) {
  return wp_compareUTM(this, &worldUTMPose, &fuzz);
}

drdc_WUTMPosn drdc_WUTMPose::getPosition() {
  drdc_WUTMPosn result;
  wp_getPosition(this, &result);
  return result;
}

drdc_Orient drdc_WUTMPose::getOrientation() {
  drdc_Orient result;
  wp_getOrientation(this, &result);
  return result;
}

drdc_WUTMPose &drdc_WUTMPose::operator = (drdc_WUTMPose worldUTMPose) {
  wp_copyUTM(&worldUTMPose, this);
  //this->setZone(worldUTMPose.zone);
  return *this;
}

double drdc_WUTMPose::operator [] (int n) {
  return wp_index(this, n);
}

drdc_WUTMPose drdc_WUTMPose::operator *(drdc_WUTMPose worldUTMPose) {
  drdc_WUTMPose result;
  wp_poseMult(this, &worldUTMPose, &result);
  return result;
}

drdc_WUTMPosn drdc_WUTMPose::operator *(drdc_WUTMPosn worldUTMPosition) {
  drdc_WUTMPosn result;
  wp_poseMultVec(this, &worldUTMPosition, &result);
  return result;
}

drdc_WPose drdc_WUTMPose::to_WPose() {
  drdc_WPose result;
  wp_WUTMPose_to_WPose(this, &result);
  return result;
}

drdc_lPose drdc_WUTMPose::to_lPose() {
  drdc_lPose result;
  wp_copy(this, &result);
  return result;
}
