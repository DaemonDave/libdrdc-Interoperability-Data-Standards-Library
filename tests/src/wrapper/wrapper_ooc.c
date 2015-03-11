// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// (C) HER MAJESTY THE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
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
 * Revision     : $Id: wrapper_ooc.c,v 1.7 2008/09/17 15:33:30 cvsuser Exp $
 */



#ifndef  WRAPPER_H
#include "wrapper.h"
#endif

int wp_compare(void *self, void *object, void *fuzzObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_fuzzObject=fuzzObject;

  return vectorCompare((*_self)->dsize, (*_self)->data, (*_object)->data, (*_fuzzObject)->data);;
}

int wp_compareUTM(void *self, void *object, void *fuzzObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_fuzzObject=fuzzObject;

  drdc_WUTMPosn_t *_selfUTM = self;
  drdc_WUTMPosn_t *_objectUTM = object;

  if (_selfUTM->zone.zoneNumber != _objectUTM->zone.zoneNumber) return 1;
  if (_selfUTM->zone.zoneLetter != _objectUTM->zone.zoneLetter) return 1;

  return vectorCompare((*_self)->dsize, (*_self)->data, (*_object)->data, (*_fuzzObject)->data);;
}

double wp_index(void *self, unsigned char n) {
  drdc_Vector_t **_self=self;
  if (n <= (*_self)->dsize) {
    return (*_self) ->data[n];
  } else {
    Throw UNRECOGNIZED_INDEX;
    return 0;
  }
}

void wp_setFromArray(void *self, const double *array) {
  drdc_Vector_t **_self =  self;
  int i;
  for(i=0; i< (*_self) ->dsize; i++)
    (*_self) ->data[i] = array[i];
}

void wp_toArray(void *self, double *array) 
{
  drdc_Vector_t **_self = self;
  int i;
  for(i=0; i< (*_self) ->dsize; i++)
    array[i] = (*_self) ->data[i];
}

void wp_destroy(void *self) {
  drdc_Vector_t **_self=self;
  if (self && *_self) {
    free((*_self)->data);
    free((*_self));
    free(self);
  }
}

void wp_copy(void *self, void *dest) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_dest=dest;
  vectorCopy((*_self)-> dsize, (*_self)->data, (*_dest)->data);
}

void wp_copyUTM(void *self, void *dest) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_dest=dest;
  drdc_WUTMPosn_t *_selfUTM = self;
  drdc_WUTMPosn_t *_destUTM = dest;
  vectorCopy((*_self)-> dsize, (*_self)->data, (*_dest)->data);
  _destUTM->zone = _selfUTM->zone;
}


void wp_print(void *self) {
  drdc_Vector_t **_self=self;
  int i;
  for(i=0; i< (*_self) ->dsize; i++)
    printf("%f ", (*_self) ->data[i]);
  printf("\n");
}



void wp_set3(void *self, double arg0, double arg1, double arg2) {
   drdc_Vector_t **_self=self;
   (*_self) ->data[0] =  arg0;
   (*_self) ->data[1] =  arg1;
   (*_self) ->data[2] =  arg2;
}

void wp_set4(void *self, double arg0, double arg1, double arg2, double arg3) {
   drdc_Vector_t **_self=self;
   (*_self) ->data[0] =  arg0;
   (*_self) ->data[1] =  arg1;
   (*_self) ->data[2] =  arg2;
   (*_self) ->data[2] =  arg3;
}

double wp_getArg0(void *self) {
  drdc_Vector_t **_self=self;
  return (*_self) ->data[0];
}

double wp_getArg1(void *self) {
  drdc_Vector_t **_self=self;
  return (*_self) ->data[1];
}

double wp_getArg2(void *self) {
  drdc_Vector_t **_self=self;
  return (*_self) ->data[2];
}

double wp_getArg3(void *self) {
  drdc_Vector_t **_self=self;
  return (*_self) ->data[3];
}

void wp_plus(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_object)->data, (*_resultObject)->data);
  vectorAxpy((*_self)->dsize, 1.0f, (*_self)->data, (*_resultObject)->data);
}

void wp_minus(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data,  (*_resultObject)->data);
  vectorAxpy((*_self)->dsize, -1.0f, (*_object)->data, (*_resultObject)->data);
}

void wp_negate(void *self, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data, (*_resultObject)->data);
  vectorScale(3, -1.0f, (*_resultObject)->data);
}

void wp_scale(void *self, double scalar, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data, (*_resultObject)->data);
  vectorScale(3, scalar, (*_resultObject)->data);
}

double wp_dot(void *self, void *object) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  return vectorDot((*_self)->dsize, (*_self)->data, (*_object)->data);;
}

void wp_cross(void *self, void *object, void *resultObject) 
{
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCross((*_self)->data, (*_object)->data, (*_resultObject)->data);
}

void wp_normalize(void *self) {
   drdc_Vector_t **_self=self;
   vectorNormalize((*_self)->dsize, (*_self)->data);
}

double wp_magnitude(void *self) {
  drdc_Vector_t **_self=self;
  return vectorMagnitude((*_self)->dsize, (*_self)->data);
}

void wp_lPosn_to_WUTMPosn(void *self, drdc_UTMZone_t zone, void *worldUTMPosition) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldUTMPosition=worldUTMPosition;
  drdc_WUTMPosn_t *worldUTMObject = worldUTMPosition;
  wp_copy(self, worldUTMPosition);
  wp_WUTMPosn_setZone(worldUTMObject, zone);
}

void wp_lPose_to_WUTMPose(void *self, drdc_UTMZone_t zone, void *worldUTMPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldUTMPose=worldUTMPose;
  drdc_WUTMPosn_t *worldUTMObject = worldUTMPose;
  wp_copy(self, worldUTMPose);
  wp_WUTMPose_setZone(worldUTMObject, zone);
}


void wp_lPosn_to_WPosn(void *self, double falseElevation, void *worldPosition) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldPosition=worldPosition;
  lPosn_to_WPosn(DATUM.a, DATUM.f, falseElevation, (*_self)->data, (*_worldPosition)->data);
}

void wp_WUTMPosn_setZone(void *self, drdc_UTMZone_t zone) {
  drdc_WUTMPosn_t *_selfUTM = self;
  _selfUTM->zone = zone;
}

void wp_WUTMPosn_getZone(void *self, drdc_UTMZone_t *zone) {
   drdc_WUTMPosn_t *_selfUTM = self;
  zone->zoneNumber = _selfUTM->zone.zoneNumber;
  zone->zoneLetter = _selfUTM->zone.zoneLetter;
}

void wp_WUTMPose_setZone(void *self, drdc_UTMZone_t zone) {
  drdc_WUTMPose_t *_selfUTM = self;
  _selfUTM->zone = zone;
}

void wp_WUTMPose_getZone(void *self, drdc_UTMZone_t *zone) {
   drdc_WUTMPose_t *_selfUTM = self;
  zone->zoneNumber = _selfUTM->zone.zoneNumber;
  zone->zoneLetter = _selfUTM->zone.zoneLetter;
}


void wp_WUTMPosn_to_WPosn(void *self, void *worldPosition) {
  drdc_Vector_t **_self=self;
  drdc_WUTMPosn_t *worldUTMObject = self;
  drdc_Vector_t **_worldPosition=worldPosition;
  if (worldUTMObject->zone.zoneNumber == 0 || worldUTMObject->zone.zoneLetter == 'O')
    Throw UNINITILIZED_UTM_ZONE;
  WUTMPosn_to_WPosn(DATUM.a, DATUM.f, worldUTMObject->zone.zoneNumber,  worldUTMObject->zone.zoneLetter, (*_self)->data, (*_worldPosition)->data);
}

void wp_WPosn_to_lPosn(void *self, double falseElevation, void *localPosition) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localPosition=localPosition;
  WPosn_to_lPosn(DATUM.a, DATUM.f, falseElevation, (*_self)->data, (*_localPosition)->data);
}

void wp_WPosnNormalize(void *self) {
  drdc_Vector_t **_self=self;
  double longtitude = (*_self)->data[0];
  double latitude = (*_self)->data[1];

  if (latitude > HALF_PI - RADIAN_FUZZ) {
    latitude   = HALF_PI - RADIAN_FUZZ;
    longtitude = 0.0f;
  } else if (latitude < -HALF_PI + RADIAN_FUZZ) {
    latitude   = -HALF_PI + RADIAN_FUZZ;
    longtitude = 0.0f;
  } else {
    while (longtitude <= -PI) longtitude += TWO_PI;
    while (longtitude > PI)   longtitude -= TWO_PI;
  }

  (*_self)->data[0] = longtitude;
  (*_self)->data[1] = latitude;
  
}

void wp_WPosn_to_WUTMPosn(void *self, void *worldUTMPosition) {
  drdc_Vector_t **_self=self;
  drdc_WUTMPosn_t *worldUTMObject = worldUTMPosition;
  drdc_Vector_t **_worldUTMPosition=worldUTMPosition;
  unsigned char zoneNumber;
  char zoneLetter;

  WPosn_to_WUTMPosn(DATUM.a, DATUM.f, (*_self)->data, &zoneNumber, &zoneLetter, (*_worldUTMPosition)->data);
  worldUTMObject->zone.zoneNumber = zoneNumber; worldUTMObject->zone.zoneLetter = zoneLetter;
}

void wp_eOrient_to_HMatrix(void *self, void *homogeneous) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_homogeneous=homogeneous;
  EulerRPYToHMatrix((*_self)->data, (*_homogeneous)->data);
}

void wp_eOrient_to_Orient(void *self, void *quaternion) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_quaternion=quaternion;
  EulerRPYToQuat((*_self)->data, (*_quaternion)->data);
}

void wp_QuatMult(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  QuatQuatMult((*_self)->data, (*_object)->data, (*_resultObject)->data);
  
}
void wp_QuatMultVec(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  QuatVectorMult((*_self)->data, (*_object)->data, (*_resultObject)->data);
}

void wp_QuatDiv(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  QuatQuatDiv((*_self)->data, (*_object)->data, (*_resultObject)->data);
}
void wp_QuatInverse(void *self, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data, (*_resultObject)->data);
  QuatInverse((*_resultObject)->data);
}

double wp_QuatMagnitude(void *self) {
  drdc_Vector_t **_self=self;
  return QuatMagnitude((*_self)->data);
}
void wp_QuatNormalize(void *self) {
  drdc_Vector_t **_self=self;
  QuatNormalize((*_self)->data);
}

void wp_Orient_to_eOrient(void *self, void *eulerRPY) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_eulerRPY=eulerRPY;
  QuatToEulerRPY((*_self)->data, (*_eulerRPY)->data);
}

void wp_Orient_to_HMatrix(void *self, void *homogeneous) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_homogeneous=homogeneous;
  QuatToHMatrix((*_self)->data, (*_homogeneous)->data);
}

void wp_QuatToRotVec(void *self, double *theta, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  QuatToRotVector((*_self)->data, theta, (*_resultObject)->data);
}

void wp_QuatFromRotVec(void *self, double theta, void *unitVector) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_unitVector=unitVector;
  RotVectorToQuat(theta, (*_unitVector)->data, (*_self)->data);
}

void wp_QuatIdentity(void *self) {
  drdc_Vector_t **_self=self;
  (*_self)->data[0]=1.0;
  (*_self)->data[1]=0.0;
  (*_self)->data[2]=0.0;
  (*_self)->data[3]=0.0;
}

void wp_QuatRotAxis(void *self, const Axis_t axis, const double theta) {
  drdc_Vector_t **_self=self;
  RotAxisToQuat(axis, theta, (*_self)->data);
}

void wp_HMatrixMult(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  vectorZeros(16, (*_resultObject)->data);
  matrixMmp('N', 'N', 1.0f, (*_self)->data, (*_object)->data, 0.0f, (*_resultObject)->data);
}

void wp_HMatrixMultVec(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;

  double v[]={(*_object)->data[0], (*_object)->data[1], (*_object)->data[2], 0.0};
  double vout[4];
  matrixMvp('N', 1.0f, (*_self)->data, v, 0.0f, vout);
  (*_resultObject)->data[0] = vout[0];
  (*_resultObject)->data[0] = vout[1];
  (*_resultObject)->data[0] = vout[2];
}

void wp_HMatrixToRotVec(void *self, double *theta, void *unitVector) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_unitVector=unitVector;
  HMatrixToRotVector((*_self)->data, theta, (*_unitVector)->data);
}

void wp_HMatrixFromRotVec(void *self,  double theta, void *unitVector) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_unitVector=unitVector;
  RotVectorToHMatrix(theta, (*_unitVector)->data, (*_self)->data);
}

void wp_HMatrixNormalize(void *self) {
  drdc_Vector_t **_self=self;
  HMatrixNormalize((*_self)->data);
}

void wp_HMatrix_to_eOrient(void *self, void *eulerRPY) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_eulerRPY=eulerRPY;
  HMatrixToEulerRPY((*_self)->data, (*_eulerRPY)->data);
}

void wp_HMatrix_to_Orient(void *self, void *quaternion) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_quaternion=quaternion;
  HMatrixToQuat((*_self)->data, (*_quaternion)->data);
}

void wp_HMatrixIdentity(void *self) {
  drdc_Vector_t **_self=self;
  matrixIdentity((*_self)->data);
}

void wp_HMatrixRotAxis(void *self, const Axis_t axis, const double theta) 
{
  drdc_Vector_t **_self=self;
  RotAxisToHMatrix(axis, theta, (*_self)->data);
}

void wp_HMatrixTranspose(void *self, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data, (*_resultObject)->data);
  matrixTranspose((*_resultObject)->data);
}

void wp_HMatrixGetTranslation(void *self, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  HMatrixGetTranslation((*_self)->data, (*_resultObject)->data);
}

void wp_HMatrixSetTranslation(void *self, void *object) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  HMatrixSetTranslation((*_object)->data, (*_self)->data);
}

void wp_HMatrixFromDH(void *self, double linkLength, double twistAngle, double jointOffset, double jointAngle) {
  drdc_Vector_t **_self=self;
  HMatrixLink(linkLength, twistAngle, jointOffset, jointAngle, (*_self)->data);
}

void wp_HMatrixFromLink(void *self, drdc_LinkSpecs_t *linkSpecs, double jointOffsetOrAngle) {
  drdc_Vector_t **_self=self;
  switch (linkSpecs->jointType) {
  case JOINT_REVOLUTE:
    HMatrixLink(linkSpecs->linkLength, linkSpecs->twistAngle, linkSpecs->jointOffsetOrAngle, jointOffsetOrAngle, (*_self)->data);
    break;
  case JOINT_PRISMATIC:
    HMatrixLink(linkSpecs->linkLength, linkSpecs->twistAngle, jointOffsetOrAngle, linkSpecs->jointOffsetOrAngle, (*_self)->data);
    break; 
  default:
    Throw UNRECOGNIZED_ENUM_ITEM;
  }
}

void wp_HMatrixInverse(void *self, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_resultObject=resultObject;
  vectorCopy((*_self)->dsize, (*_self)->data, (*_resultObject)->data);
  HMatrixInverse((*_resultObject)->data);
}

void wp_setPose(void *self, void *position, void *orientation) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_position=position;
  drdc_Vector_t **_orientation=orientation;
  vectorJoin((*_position)->dsize, (*_orientation)->dsize, (*_position)->data, (*_orientation)->data, (*_self)->data);
}

void wp_getPosition(void *self, void *position) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_position=position;
  double temp[4];
  vectorSplit((*_position)->dsize,(*_self)->dsize-(*_position)->dsize, (*_self)->data, (*_position)->data, temp);
}

void wp_getOrientation(void *self, void *orientation) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_orientation=orientation;
  double temp[3];
  vectorSplit((*_self)->dsize-(*_orientation)->dsize, (*_orientation)->dsize, (*_self)->data, temp, (*_orientation)->data);
}

void wp_poseMult(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  double  orientation1[4], orientation2[4];
  double position1[3], position2[3], resultPosition[3];

  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position1, orientation1);
  vectorSplit(3, (*_object)->dsize - 3, (*_object)->data, position2, orientation2);
  QuatVectorMult(orientation1, position2, resultPosition);
  vectorAxpy(3, 1.0f, position1, resultPosition);
  QuatQuatMult(orientation1, orientation2, orientation1);
  vectorJoin(3, (*_self)->dsize - 3, resultPosition, orientation1, (*_resultObject)->data);
}

void wp_poseMultVec(void *self, void *object, void *resultObject) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_object=object;
  drdc_Vector_t **_resultObject=resultObject;
  double  orientation[4];
  double position[3];
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  QuatVectorMult(orientation, (*_object)->data, (*_resultObject)->data);
  vectorAxpy(3, 1.0f, position, (*_resultObject)->data);
}

void wp_WPose_to_WUTMPose(void *self, void *worldUTMPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldUTMPose=worldUTMPose;
  drdc_WUTMPose_t *worldUTMObject = worldUTMPose;
  double  orientation[4];
  double position[3];
  double utm[3];

  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  WPosn_to_WUTMPosn(DATUM.a, DATUM.f, position, &(worldUTMObject->zone.zoneNumber), &(worldUTMObject->zone.zoneLetter), utm);
  vectorJoin(3, (*_worldUTMPose)->dsize - 3, utm, orientation, (*_worldUTMPose)->data);
}

void wp_WPose_to_lPose(void *self, double falseElevation, void *localPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localPose=localPose;
  double  orientation[4];
  double position[3], newPosition[3];
  
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  WPosn_to_lPosn(DATUM.a, DATUM.f, falseElevation, position, newPosition);
  vectorJoin(3, (*_localPose)->dsize - 3, newPosition, orientation, (*_localPose)->data);

}
void wp_lPose_to_WPose (void *self, double falseElevation, void *worldPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldPose=worldPose;
  double  orientation[4];
  double position[3], newPosition[3];
  
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  lPosn_to_WPosn(DATUM.a, DATUM.f, falseElevation, position, newPosition);
  vectorJoin(3, (*_worldPose)->dsize - 3, newPosition, orientation, (*_worldPose)->data);
}

void wp_lPose_to_lePose (void *self, void *localEulerPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localEulerPose=localEulerPose;
  double  orientation[4], newOrientation[3];
  double position[3];
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  QuatToEulerRPY(orientation, newOrientation);
  vectorJoin(3, (*_localEulerPose)->dsize - 3, position, newOrientation, (*_localEulerPose)->data);
}
void wp_lPose_to_HMatrix (void *self, void *homogeneous) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_homogeneous=homogeneous;
  double  orientation[4];
  double position[3];
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  QuatToHMatrix(orientation, (*_homogeneous)->data);
  HMatrixSetTranslation(position, (*_homogeneous)->data);
}

void wp_WUTMPose_to_WPose(void *self, void *worldPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_worldPose=worldPose;
  drdc_WUTMPose_t *worldUTMObject = worldPose;
  double  orientation[4];
  double position[3], newPosition[3];
  
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  if (worldUTMObject->zone.zoneNumber == 0 || worldUTMObject->zone.zoneLetter == 'O')
    Throw UNINITILIZED_UTM_ZONE;
  WUTMPosn_to_WPosn(DATUM.a, DATUM.f, worldUTMObject->zone.zoneNumber, worldUTMObject->zone.zoneLetter, position, newPosition);
  vectorJoin(3, (*_worldPose)->dsize - 3, newPosition, orientation, (*_worldPose)->data);
}

void wp_lePose_to_lPose(void *self, void *localPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localPose=localPose;
  double  orientation[4], newOrientation[3];
  double position[3];
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  EulerRPYToQuat(orientation, newOrientation);
  vectorJoin(3, (*_localPose)->dsize - 3, position, newOrientation, (*_localPose)->data);
}

void wp_lePose_to_HMatrix(void *self, void *homogeneous) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_homogeneous=homogeneous;
  double  orientation[3];
  double position[3];
  vectorSplit(3, (*_self)->dsize - 3, (*_self)->data, position, orientation);
  EulerRPYToHMatrix(orientation, (*_homogeneous)->data);
  HMatrixSetTranslation(position, (*_homogeneous)->data);
}

void wp_HMatrix_to_lPose(void *self, void *localPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localPose=localPose;
  double  orientation[4];
  double position[3];

  HMatrixToQuat((*_self)->data,  orientation);
  HMatrixGetTranslation((*_self)->data, position);
  vectorJoin(3, (*_localPose)->dsize - 3, position, orientation, (*_localPose)->data);
}

void wp_HMatrix_to_lePose(void *self, void *localEulerPose) {
  drdc_Vector_t **_self=self;
  drdc_Vector_t **_localEulerPose=localEulerPose;
  double  orientation[3];
  double position[3];

  HMatrixToEulerRPY((*_self)->data,  orientation);
  HMatrixGetTranslation((*_self)->data, position);
  vectorJoin(3, (*_localEulerPose)->dsize - 3, position, orientation, (*_localEulerPose)->data);
}


drdc_Vector_t *new_Vector(unsigned char dsize) {
  int i;
  drdc_Vector_t *ptr = (drdc_Vector_t *) calloc(1, sizeof(drdc_Vector_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;

  ptr->dsize = dsize;
  ptr->data=(double *) calloc(dsize, sizeof(double));
  if (ptr->data == NULL) {
    wp_destroy(ptr);
    Throw CALLOC_NULL_ERROR;
  }
  for (i=0; i < dsize; i++) {
    ptr->data[i] = 0.0;
  }
  return ptr;
}


drdc_lPosn_t *new_lPosn() {
  drdc_lPosn_t *ptr = (drdc_lPosn_t*) calloc(1, sizeof(drdc_lPosn_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(3);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->compare = (void *)wp_compare;
  ptr->index = (void *)wp_index;
  ptr->copy = (void *) wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_set3;
  ptr->getX = (void *)wp_getArg0;
  ptr->getY = (void *)wp_getArg1;
  ptr->getZ = (void *)wp_getArg2;
  ptr->plus = (void *)wp_plus;
  ptr->minus = (void *)wp_minus;
  ptr->negate = (void *)wp_negate;
  ptr->scale = (void *)wp_scale;
  ptr->dot = (void *)wp_dot;
  ptr->cross = (void *)wp_cross;
  ptr->normalize = (void *)wp_normalize;
  ptr->magnitude = (void *)wp_magnitude;
  ptr->to_WUTMPosn = (void *)wp_lPosn_to_WUTMPosn; 
  ptr->to_WPosn = (void *)wp_lPosn_to_WPosn;  
  return ptr;
}


drdc_WUTMPosn_t *new_WUTMPosn() {
  drdc_WUTMPosn_t *ptr = (drdc_WUTMPosn_t *) calloc(1, sizeof(drdc_WUTMPosn_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->zone.zoneNumber = 0;
  ptr->zone.zoneLetter = 'O';
  ptr->vector = (void *)new_Vector(3);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compareUTM;
  ptr->copy = (void *)wp_copyUTM;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_set3;
  ptr->getEasting = (void *)wp_getArg0;
  ptr->getNorthing = (void *)wp_getArg1;
  ptr->getElevation = (void *)wp_getArg2;
  ptr->setZone = (void *) wp_WUTMPosn_setZone;
  ptr->getZone = (void *) wp_WUTMPosn_getZone;
  ptr->plus = (void *)wp_plus;
  ptr->minus = (void *)wp_minus;
  ptr->negate = (void *)wp_negate;
  ptr->scale = (void *)wp_scale;
  ptr->dot = (void *)wp_dot;
  ptr->cross = (void *)wp_cross;
  ptr->to_lPosn = (void *)wp_copy;
  ptr->to_WPosn = (void *)wp_WUTMPosn_to_WPosn;
  return ptr;
}


drdc_WPosn_t *new_WPosn() {
  drdc_WPosn_t *ptr = (drdc_WPosn_t*) calloc(1, sizeof(drdc_WPosn_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(3);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_set3;
  ptr->getLongtitude = (void *)wp_getArg0;
  ptr->getLatitude = (void *)wp_getArg1;
  ptr->getElevation = (void *)wp_getArg2;
  ptr->normalize = (void *)wp_WPosnNormalize;
  ptr->to_lPosn = (void *)wp_WPosn_to_lPosn;
  ptr->to_WUTMPosn = (void *)wp_WPosn_to_WUTMPosn;
  return ptr;
}

drdc_eOrient_t *new_eOrient() {
  drdc_eOrient_t *ptr = (drdc_eOrient_t*) calloc(1, sizeof(drdc_eOrient_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(3);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_set3;
  ptr->getRoll = (void *)wp_getArg0;
  ptr->getPitch = (void *)wp_getArg1;
  ptr->getYaw = (void *)wp_getArg2;
  ptr->plus = (void *)wp_plus;
  ptr->minus = (void *)wp_minus;
  ptr->negate = (void *)wp_negate;
  ptr->scale = (void *)wp_scale;
  ptr->to_HMatrix = (void *)wp_eOrient_to_HMatrix;
  ptr->to_Orient = (void *)wp_eOrient_to_Orient;
  return ptr;
}

drdc_Orient_t *new_Orient() {
  drdc_Orient_t *ptr = (drdc_Orient_t*) calloc(1, sizeof(drdc_Orient_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(4);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_set4;
  ptr->getW = (void *)wp_getArg0;
  ptr->getX = (void *)wp_getArg1;
  ptr->getY = (void *)wp_getArg2;
  ptr->getZ = (void *)wp_getArg3;
  ptr->plus = (void *)wp_plus;
  ptr->minus = (void *)wp_minus;
  ptr->negate = (void *)wp_negate;
  ptr->scale = (void *)wp_scale;
  ptr->mult = (void *)wp_QuatMult;
  ptr->multVec = (void *)wp_QuatMultVec;
  ptr->normalize = (void *)wp_QuatNormalize;
  ptr->magnitude = (void *)wp_QuatMagnitude;
  ptr->to_HMatrix = (void *)wp_Orient_to_HMatrix;
  ptr->to_eOrient = (void *)wp_Orient_to_eOrient;
  ptr->fromRotAxis = (void *)wp_QuatRotAxis;
  ptr->fromRotVec = (void *)wp_QuatFromRotVec;
  ptr->toRotVec = (void *)wp_QuatToRotVec;
  ptr->identity = (void *)wp_QuatIdentity;
  ptr->inverse = (void *)wp_QuatInverse;
  return ptr;
}

drdc_HMatrix_t *new_HMatrix() {
  drdc_HMatrix_t *ptr = (drdc_HMatrix_t*) calloc(1, sizeof(drdc_HMatrix_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(16);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->mult = (void *)wp_HMatrixMult;
  ptr->multVec = (void *)wp_HMatrixMultVec;
  ptr->normalize = (void *)wp_HMatrixNormalize;
  ptr->to_Orient = (void *)wp_HMatrix_to_Orient;
  ptr->to_eOrient = (void *)wp_HMatrix_to_eOrient;
  ptr->fromRotAxis = (void *)wp_HMatrixRotAxis;
  ptr->fromRotVec = (void *)wp_HMatrixFromRotVec;
  ptr->toRotVec = (void *)wp_HMatrixToRotVec;
  ptr->fromDH = (void *)wp_HMatrixFromDH;
  ptr->fromLink = (void *)wp_HMatrixFromLink;
  ptr->getPosition = (void *)wp_HMatrixGetTranslation;
  ptr->setPosition = (void *)wp_HMatrixSetTranslation;
  ptr->identity = (void *)wp_HMatrixIdentity;
  ptr->inverse = (void *)wp_HMatrixInverse;
  ptr->transpose = (void *)wp_HMatrixTranspose;
  ptr->to_lPose = (void *)wp_HMatrix_to_lPose;
  ptr->to_lePose = (void *)wp_HMatrix_to_lePose;
  return ptr;
}

drdc_WPose_t *new_WPose() {
  drdc_WPose_t *ptr = (drdc_WPose_t*) calloc(1, sizeof(drdc_WPose_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(7);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_setPose;
  ptr->getPosition = (void *)wp_getPosition;
  ptr->getOrientation = (void *)wp_getOrientation;
  ptr->to_WUTMPose = (void *)wp_WPose_to_WUTMPose;
  ptr->to_lPose = (void *)wp_WPose_to_lPose;
  return ptr;
}

drdc_lPose_t *new_lPose() {
  drdc_lPose_t *ptr = (drdc_lPose_t*) calloc(1, sizeof(drdc_lPose_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(7);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_setPose;
  ptr->getPosition = (void *)wp_getPosition;
  ptr->getOrientation = (void *)wp_getOrientation;
  ptr->mult = (void *)wp_poseMult;
  ptr->multVec = (void *)wp_poseMultVec;
  ptr->to_WPose = (void *)wp_lPose_to_WPose;
  ptr->to_WUTMPose = (void *)wp_lPose_to_WUTMPose;
  ptr->to_lePose = (void *)wp_lPose_to_lePose;
  ptr->to_HMatrix = (void *)wp_lPose_to_HMatrix;
  return ptr;
}

drdc_WUTMPose_t *new_WUTMPose() {
  drdc_WUTMPose_t *ptr = (drdc_WUTMPose_t*) calloc(1, sizeof(drdc_WUTMPose_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->zone.zoneNumber = 0;
  ptr->zone.zoneLetter = 'O';
  ptr->vector = (void *)new_Vector(7);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compareUTM;
  ptr->copy = (void *)wp_copyUTM;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_setPose;
  ptr->getPosition = (void *)wp_getPosition;
  ptr->getOrientation = (void *)wp_getOrientation;
  ptr->setZone = (void *) wp_WUTMPose_setZone;
  ptr->getZone = (void *) wp_WUTMPose_getZone;
  ptr->mult = (void *)wp_poseMult;
  ptr->multVec = (void *)wp_poseMultVec;
  ptr->to_WPose = (void *)wp_WUTMPose_to_WPose;
  ptr->to_lPose = (void *)wp_copy;
  return ptr;
}

drdc_lePose_t *new_lePose() {
  drdc_lePose_t *ptr = (drdc_lePose_t*) calloc(1, sizeof(drdc_lePose_t));
  if (ptr==NULL) Throw CALLOC_NULL_ERROR;
  ptr->vector = (void *)new_Vector(6);
  if (ptr->vector==NULL) Throw CALLOC_NULL_ERROR;
  ptr->index = (void *)wp_index;
  ptr->compare = (void *)wp_compare;
  ptr->copy = (void *)wp_copy;
  ptr->setFromArray = (void *)wp_setFromArray;
  ptr->toArray = (void *)wp_toArray;
  ptr->destroy = (void *)wp_destroy;
  ptr->set = (void *)wp_setPose;
  ptr->getPosition = (void *)wp_getPosition;
  ptr->getOrientation = (void *)wp_getOrientation;
  ptr->to_lPose = (void *)wp_lePose_to_lPose;
  ptr->to_HMatrix = (void *)wp_lePose_to_HMatrix;
  return ptr;
}
