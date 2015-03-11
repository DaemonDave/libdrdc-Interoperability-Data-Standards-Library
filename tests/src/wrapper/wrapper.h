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
 * Purpose      : wrapper header for common ObjectiveC classes
 * Revision     : $Id: wrapper.h,v 1.10 2008/10/27 20:29:40 cvsuser Exp $
 */


/**


	 
	 \todo  document all C++ and OOC classes interface with existing information
*/

#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif
	

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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


/**
 * \struct  %drdc_UTMZone_t  
 * 
 %UTM Zone Structure
 */
typedef struct 
{
  unsigned char   zoneNumber;
  char            zoneLetter;
} drdc_UTMZone_t;



/**
 *  \struct drdc_DMS_t
  Degree-Minute-Second Structure
	@param degrees of arc 
	@param minutes of arc
  @param seconds of arc
 * 
 */
typedef struct
{
  double degree;   
  double minute;	  
  double second;	 
} drdc_DMS_t;

/**
 *  \struct drdc_Datum_t 
 *  %Global Datum
 * 
 *	 @param a degrees of arc 
 *	 @param f degrees of arc 	 
 */
typedef struct {
  double a;
  double f;
} drdc_Datum_t;



/**
 *  \struct drdc_LinkSpecs_t 
 Manipulator Linkage Specification
 * 
 */
typedef struct {
  uint8_t jointType;
  double  linkLength;
  double  twistAngle;
  double  jointOffsetOrAngle;
} drdc_LinkSpecs_t;

/** 
	\enum drdc_Joint_t
*/
typedef enum {
  JOINT_TYPE_ERR,
  JOINT_REVOLUTE,
  JOINT_PRISMATIC,
} drdc_Joint_t; 


/** \var DATUM 
*/
static drdc_Datum_t DATUM={WGS84_A, WGS84_F};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int wp_compare(void *self, void *object, void *fuzzObject);
int wp_compareUTM(void *self, void *object, void *fuzzObject);
double wp_index(void *self, unsigned char n);
void wp_setFromArray(void *self, const double *array);
void wp_toArray(void *self, double *array);
void wp_destroy(void *self);
void wp_copy(void *self, void *dest);
void wp_copyUTM(void *self, void *dest);
void wp_set3(void *self, double arg0, double arg1, double arg2);
void wp_print(void *self);
void wp_set4(void *self, double arg0, double arg1, double arg2, double arg3);
double wp_getArg0(void *self);
double wp_getArg1(void *self);
double wp_getArg2(void *self);
double wp_getArg3(void *self);
void wp_plus(void *self, void *object, void *resultObject);
void wp_minus(void *self, void *object, void *resultObject);
void wp_negate(void *self, void *resultObject);
void wp_scale(void *self, double scalar, void *resultObject);
double wp_dot(void *self, void *object);
void wp_cross(void *self, void *object, void *resultObject);
void wp_normalize(void *self);
double wp_magnitude(void *self);
void wp_lPosn_to_WUTMPosn(void *self, drdc_UTMZone_t zone, void *worldUTMPosition);
void wp_lPose_to_WUTMPose(void *self, drdc_UTMZone_t zone, void *worldUTMPose);
void wp_lPosn_to_WPosn(void *self, double falseElevation, void *worldPosition);
void wp_WUTMPosn_to_WPosn(void *self, void *worldPosition);
void wp_WUTMPosn_setZone(void *self, drdc_UTMZone_t zone);
void wp_WUTMPosn_getZone(void *self, drdc_UTMZone_t *zone);
void wp_WUTMPose_setZone(void *self, drdc_UTMZone_t zone);
void wp_WUTMPose_getZone(void *self, drdc_UTMZone_t *zone);
void wp_WPosn_to_lPosn(void *self, double falseElevation, void *localPosition);
void wp_WPosnNormalize(void *self);
void wp_WPosn_to_WUTMPosn(void *self, void *worldUTMPosition);
void wp_eOrient_to_HMatrix(void *self, void *homogeneous);
void wp_eOrient_to_Orient(void *self, void *quaternion);
void wp_QuatMult(void *self, void *object, void *resultObject);
void wp_QuatMultVec(void *self, void *object, void *resultObject);
void wp_QuatDiv(void *self, void *object, void *resultObject);
void wp_QuatInverse(void *self, void *resultObject);
double wp_QuatMagnitude(void *self);
void wp_QuatNormalize(void *self);
void wp_Orient_to_eOrient(void *self, void *eulerRPY);
void wp_Orient_to_HMatrix(void *self, void *homogeneous);
void wp_QuatToRotVec(void *self, double *theta, void *unitVector);
void wp_QuatFromRotVec(void *self, double theta, void *unitVector);
void wp_QuatIdentity(void *self);
void wp_QuatRotAxis(void *self, const Axis_t axis, const double theta);
void wp_HMatrixMult(void *self, void *object, void *resultObject);
void wp_HMatrixMultVec(void *self, void *object, void *resultObject);
void wp_HMatrixToRotVec(void *self, double *theta, void *unitVector);
void wp_HMatrixFromRotVec(void *self,  double theta, void *unitVector);
void wp_HMatrixNormalize(void *self);
void wp_HMatrix_to_eOrient(void *self, void *eulerRPY);
void wp_HMatrix_to_Orient(void *self, void *quaternion);
void wp_HMatrixIdentity(void *self);
void wp_HMatrixRotAxis(void *self, const Axis_t axis, const double theta);
void wp_HMatrixTranspose(void *self, void *resultObject);
void wp_HMatrixGetTranslation(void *self, void *resultObject);
void wp_HMatrixSetTranslation(void *self, void *object);
void wp_HMatrixFromDH(void *self, double linkLength, double twistAngle, double jointOffset, double jointAngle);
void wp_HMatrixFromLink(void *self, drdc_LinkSpecs_t *linkSpecs, double jointOffsetOrAngle);
void wp_HMatrixInverse(void *self, void *resultObject);
void wp_setPose(void *self, void *position, void *orientation);
void wp_getPosition(void *self, void *position);
void wp_getOrientation(void *self, void *orientation);
void wp_poseMult(void *self, void *object, void *resultObject);
void wp_poseMultVec(void *self, void *object, void *resultObject);
void wp_WPose_to_WUTMPose(void *self, void *worldUTMPose);
void wp_WPose_to_lPose(void *self, double falseElevation, void *localPose);
void wp_lPose_to_WPose (void *self, double falseElevation, void *worldPose);
void wp_lPose_to_lePose (void *self, void *localEulerPose);
void wp_lPose_to_HMatrix (void *self, void *homogeneous);
void wp_WUTMPose_to_WPose (void *self, void *worldPose);
void wp_lePose_to_lPose (void *self, void *localPose);
void wp_lePose_to_HMatrix (void *self, void *homogeneous);
void wp_HMatrix_to_lPose(void *self, void *localPose);
void wp_HMatrix_to_lePose(void *self, void *localEulerPose);



#ifdef __cplusplus
}
#endif /* __cplusplus */




/**
 * \struct drdc_Vector_t 
 Generic Vector Type
 * 
 		drdc_Vector_t is a generic data type containing a size and data value
 */
typedef struct 
{
  unsigned char dsize;
  double *data;
} drdc_Vector_t;



/**
 * \struct drdc_lPosn_t  
 	<b>	OOC Local Position Representation </b>
 * 
 */
typedef struct {
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the Local Position object by specifying cartesian x, y and z values.
  void (*set) (void *self, double x, double y, double z);
  /// Return the cartesian x value from the Local Position object.
  double (*getX) (void *self);
  /// Return the cartesian y value from the Local Position object.
  double (*getY) (void *self);
  /// Return the cartesian z value from the Local Position object.
  double (*getZ) (void *self);
  /// Plus operator, resultObject = self + object.
  void (*plus) (void *self, const void *object, void *resultObject);
  /// Minus operator, resultObject = self - object.
  void (*minus) (void *self, void *object, void *resultObject);
  /// Negate operator, resultObject = - self.
  void (*negate) (void *self, void *resultObject);
  /// Scale operator, resultObject = self * scalar.
  void (*scale) (void *self, double scalar, void *resultObject);
  /// Vector dot operator. It returns vector dot result.
  double (*dot) (void *self, void *object);
  /// Vector cross operator, resultObject = self cross object.
  void (*cross) (void *self, void *object, void *resultObject);
  /// Normalize the self object (vector norm).
  void (*normalize) (void *self);
  /// Return the magnitude of the self object.
  double (*magnitude) (void *self);
  /**
   * Map Local Position to World UTM Position  
   *
   * It is a simple mapping function. The mapping scheme is shown as follows:
   * - x - Easting
   * - y - Northing
   * - z - Elevation
   * 
   * Other mapping schemes can be achieved by using coordinate transformations.
   */
  void (*to_WUTMPosn) (void *self, drdc_UTMZone_t zone, void *worldUTMPosition); 

  /**
   * Convert ECEF Position to World Position 
   * 
   * ECEF is a global position representation. Here we use Local
   * Position, which is really a cartesian system, to represent ECEF
   * system. 
   *
   * @param falseElevation False elevation.
   */
  void (*to_WPosn) (void *self, double falseElevation, void *worldPosition);
} drdc_lPosn_t;


/**
 * \struct drdc_WUTMPosn_t 
 
 		<b>OOC World UTM Position Representation</b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  drdc_UTMZone_t zone;		/**< UTM Zone. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  void (*setFromArray) (void *self, const double *array);
  void (*toArray) (const void *self, double *array);
  void (*destroy) (void *self);
  /// Set the World UTM Position object by specifying Easting, Northing and Elevation values.
  void (*set) (void *self, double easting, double northing, double elevation);
  /// Return the Easting value from the World UTM Position object.
  double (*getEasting) (void *self);
  /// Return the Northing value from the World UTM Position object.
  double (*getNorthing) (void *self);
  /// Return the Elevation value from the World UTM Position object.
  double (*getElevation) (void *self);
  /// Set UTM Zone.
  void (*setZone) (void *self, drdc_UTMZone_t zone);
  /// Return UTM Zone.
  void (*getZone) (void *self, drdc_UTMZone_t *zone);
  /// Plus operator, resultObject = self + object.
  void (*plus) (void *self, const void *object, void *resultObject);
  /// Minus operator, resultObject = self - object.
  void (*minus) (void *self, void *object, void *resultObject);
  /// Negate operator, resultObject = - self.
  void (*negate) (void *self, void *object, void *resultObject);
  /// Scale operator, resultObject = self * scalar.
  void (*scale) (void *self, double scalar, void *resultObject);
  /// Vector dot operator. It returns vector dot result.
  double (*dot) (void *self, void *object);
  /// Vector cross operator, resultObject = self cross object.
  void (*cross) (void *self, void *object, void *resultObject);
  /**
   * Map World UTM Position to Local Position
   * It is a simple mapping function. The mapping scheme is shown as follows:
   * - x - Easting
   * - y - Northing
   * - z - Elevation
   * 
   * Other mapping schemes can be achieved by using coordinate transformations.
   */
  void (*to_lPosn) (void *self, void *localPosition); 
  /**
   * Convert World UTM Position to World Position
   *
   *
   */
  void (*to_WPosn) (void *self, void *worldPosition);
} drdc_WUTMPosn_t;


/**
 * \struct  drdc_WPosn_t 
 
 		<b> OOC World Position Representation </b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the World Position object by specifying longtitude, latitude and elevation values.
  void (*set) (void *self, double longtitude, double latitude, double elevation);
  /// Return the longtitude value from the World Position Object.
  double (*getLongtitude) (void *self);
  /// Return the latitude value from the World Position Object.
  double (*getLatitude) (void *self);
  /// Return the elevation value from the World Position Object.
  double (*getElevation) (void *self);
  /// Normalize lontitude to -180 to 180 degree and latitude to -90 to 90 degree.
  void (*normalize) (void *self);
  /**
   * Convert World Position to ECEF position
   */
  void (*to_lPosn) (void *self, double falseElevation, void *localPosition); 
  /**
   * Convert World Position to World UTM Position
   */
  void (*to_WUTMPosn) (void *self, void *worldUTMPosition);
} drdc_WPosn_t;


/**
 * \struct drdc_eOrient_t 
 
 		<b> OOC Euler RPY Representation </b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
 /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
 /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the Euler RPY object by specifying roll, pitch and yaw values.
  void (*set) (void *self, double roll, double pitch, double yaw);
  /// Return roll component of Euler RPY
  double (*getRoll) (void *self);
  /// Return pitch component of Euler RPY
  double (*getPitch) (void *self);
  /// Return yaw component of Euler RPY
  double (*getYaw) (void *self);
  /// Plus operator, resultObject = self + object.
  void (*plus) (void *self, const void *object, void *resultObject);
  /// Minus operator, resultObject = self - object.
  void (*minus) (void *self, void *object, void *resultObject);
  /// Negate operator, resultObject = - self.
  void (*negate) (void *self, void *object, void *resultObject);
  /// Scale operator, resultObject = self * scalar.
  void (*scale) (void *self, double scalar, void *resultObject);
  /**
   * Convert Euler RPY to Homogeneous Matrix
   */
  void (*to_HMatrix) (void *self, void *homogeneous);
  /**
   * Convert Euler RPY to Quaternion
   */
  void (*to_Orient) (void *self, void *quaternion);
} drdc_eOrient_t;

/**
 * \struct drdc_Orient_t 
 
 	<b> OOC Quaternion Representation </b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the Auaternion object by specifying w, x, y and z components.
  void (*set) (void *self, double w, double x, double y, double z);
  /// Return w component of Quaternion
  double (*getW) (void *self);
  /// Return x component of Quaternion
  double (*getX) (void *self);
  /// Return y component of Quaternion
  double (*getY) (void *self);
  /// Return z component of Quaternion
  double (*getZ) (void *self);
  /// Plus operator, resultObject = self + object.
  void (*plus) (void *self, const void *object, void *resultObject);
  /// Minus operator, resultObject = self - object.
  void (*minus) (void *self, void *object, void *resultObject);
  /// Negate operator, resultObject = - self.
  void (*negate) (void *self, void *object, void *resultObject);
  /// Scale operator, resultObject = self * scalar.
  void (*scale) (void *self, double scalar, void *resultObject);
  /**
   * Quaternion multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are drdc_Orient_t type.
   */
  void (*mult) (void *self, void *object, void *resultObject);
  /**
   * Quaternion-Vector multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are drdc_lPosn_t or drdc_WUTMPosn_t type.
   */
  void (*multVec) (void *self, void *object, void *resultObject);
  /// Normalize Quaternion
  void (*normalize) (void *self);
  /// Return magnitude of Quaternion
  double (*magnitude) (void *self);
  /// Create identity Quaternion
  void (*identity) (void *self);
  /// Inverse a Quaternion
  void (*inverse) (void *self, void *resultObject);
  /// Construct Quaternion from Rotation of a axis
  void (*fromRotAxis) (void *self, Axis_t axis, double angle);
  /// Construct Quaternion from rotating an angle about a unit vector
  void (*fromRotVec) (void *self, double angle, void *unitVector);
  /// Convert Quaternion to Rotation Vector (angle and unit vector).
  void (*toRotVec) (void *self, double *angle, void *unitVector);
  /// Convert Quaternion to Homogeneous Matrix
  void (*to_HMatrix) (void *self, void *homogeneous);
  /// Convert Quaternion to Euler RPY
  void (*to_eOrient) (void *self, void *eulerRPY); 
} drdc_Orient_t;

/**
 * \struct drdc_HMatrix_t 
 
 	<b> OOC Homogeneous Matrix Representation </b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /**
   * Homogeneous Matrix multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are Homogeneous Matrix type..
   */
  void (*mult) (void *self, void *object, void *resultObject);
  /**
   * Homogeneous-Vector multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are drdc_lPosn or drdc_WUTMPosn type.
   */
  void (*multVec) (void *self, void *object, void *resultObject);
  /// Set position component of Homogeneous Matrix
  void (*setPosition) (void *self, drdc_lPosn_t *position);
  /// Return position component of Homogeneous Matrix
  void (*getPosition) (void *self, drdc_lPosn_t *position);
  /// Normalize a Homogeneous Matrix
  void (*normalize) (void *self);
  /// Create identity Homogeneous Matrix
  void (*identity) (void *self);
  /// Inverse a Homogeneous Matrix
  void (*inverse) (void *self, void *resultObject);
  /// Transpose a Homogeneous Matrix
  void (*transpose) (void *self, void *resultObject);
  /// Construct Homogeneous Matrix from DH representation
  void (*fromDH) (void *self, double linkLength, double twistAngle, double jointOffset, double jointAngle);
  /// Construct Homogeneous Matrix from link specification struct
  void (*fromLink) (void *linkSpec, double jointOffsetOrAngle);
  /// Construct Homogeneous Matrix from rotation of an axis
  void (*fromRotAxis) (void *self, Axis_t axis, double angle);
  /// Construct Homogeneous Matrix from rotation vector
  void (*fromRotVec) (void *self, double angle, void *unitVector);
  /// Convert Homogeneous Matrix to rotation vector
  void (*toRotVec) (void *self, double *angle, void *unitVector);
  /// Convert Homogeneous Matrix to Quaternion
  void (*to_Orient) (void *self, void *homogeneous);
  /// Convert Homogeneous Matrix to Euler RPY 
  void (*to_eOrient) (void *self, drdc_eOrient_t *eulerRPY); 
  /// Convert Homogeneous Matrix to Local Pose
  void (*to_lPose) (void *self, void *localPose);
  /// Convert Homogeneous Matrix to Local Euler Pose
  void (*to_lePose) (void *self, void *localEulerPose);
} drdc_HMatrix_t;


/**
 * \struct drdc_WPose_t  
 
 	<b> OOC World Pose Representation </b>  
 *
 * \sa drdc_WPose
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
   /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set World Pose object by specifying World Position and Quaternion orientation
  void (*set) (void *self, void *position, void *orientation);
  /// Return World Position of World Pose
  void (*getPosition) (void *self, void *position);
  /// Return Quaternion orientation of World Pose
  void (*getOrientation) (void *self, void *orientation);
  /// Convert World Pose to World UTM Pose
  void (*to_WUTMPose) (void *self, void *worldUTMPose);
  /// Convert World Pose to Local Pose
  void (*to_lPose) (void *self, double falseElevation, void *localPose);
} drdc_WPose_t;

/**
 * \struct drdc_lPose_t 
 
 		<b> OOC World Pose Representation </b> 
 
 			\sa drdc_lPose
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the Local Pose object by specifying Local Position and Quaternion.
  void (*set) (void *self, void *position, void *orientation);
  /// Return Local Position of Local Pose 
  void (*getPosition) (void *self, void *position);
  /// Return Quaternion orientation of Local Pose 
  void (*getOrientation) (void *self, void *orientation);
  /**
   * Local Pose multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are drdc_lPose type.
   */
  void (*mult) (void *self, void *object, void *resultObject);
  /**
   * Local Pose - Local Position multiplication operator
   *
   * resultObject = self * object. 
   *
   * Object and resultObject are drdc_lPosn type.
   */
  void (*multVec) (void *self, void *object, void *resultObject);
  /// Convert Local Pose to World Pose
  void (*to_WPose) (void *self, double falseElevation, void *worldPose);
  /**
   * Map World UTM Pose to Local Pose
   * It is a simple mapping function. The mapping scheme is shown as follows:
   * - x - Easting
   * - y - Northing
   * - z - Elevation
   * - Orientation - Orientation
   * 
   * Other mapping schemes can be achieved by using coordinate transformations.
   */  
  void (*to_WUTMPose) (void *self, drdc_UTMZone_t zone, void *worldUTMPose); 
  /// Convert Local Pose to Local Euler Pose
  void (*to_lePose) (void *self, void *localEulerPose);
  /// Convert Local Pose to Homogeneous Matrix
  void (*to_HMatrix) (void *self, void *homogeneous);
} drdc_lPose_t;

/**
 * \struct drdc_WUTMPose_t 
 
 	<b> OOC World UTM Pose Representation</b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  drdc_UTMZone_t zone;		/**< UTM Zone */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
  /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the World UTM Pose object by specifying World UTM Position and Quaternion..
  void (*set) (void *self, void *position, void *orientation);
  /// Return World UTM Position of World UTM Pose
  void (*getPosition) (void *self, void *position);
  /// Return Quaternion orientation of World UTM Pose 
  void (*getOrientation) (void *self, void *orientation);
  /// Set UTM Zone
  void (*setZone) (void *self, drdc_UTMZone_t zone);
  /// Return UTM Zone
  void (*getZone) (void *self, drdc_UTMZone_t *zone);
  /**
   * Local Pose multiplication operator
   *
   * resultObject = self * object
   *
   * Object and resultObject are drdc_WUTMPose type.
   */
  void (*mult) (void *self, void *object, void *resultObject);
  /**
   * World UTM Pose -World UTM Position multiplication operator.
   * 
   * resultObject = self * object.
   *
   *  Object and resultObject are drdc_WUTMPosn type.
   */
  void (*multVec) (void *self, void *object, void *resultObject);
  /// Convert World UTM Pose to World Pose
  void (*to_WPose) (void *self, void *worldPose);
  /// Map World UTM Pose to Local Pose
  void (*to_lPose) (void *self, void *localPose);
} drdc_WUTMPose_t;


/**
 * \struct drdc_lePose_t 
 
 	<b> OOC Local Euler Pose Representation</b>
 * 
 */
typedef struct 
{
  const void *vector;		/**< Protected data vector. */
  /// Return the nth element from the object data vector.
  double (*index) (void *self, unsigned char n);
  /// Compare two objects, self and object. The fuzzObject determines how close they are considered to be equal. 
  int (*compare) (void *self, void *object, void *fuzzObject);
  /// Copy data in the self object to the dest object.
  void (*copy) (void *self, void *dest);
  /// Set the self object by using array data type.
  void (*setFromArray) (void *self, const double *array);
   /// Convert data in the self object to data array type.
  void (*toArray) (const void *self, double *array);
  /// Delete the self object.
  void (*destroy) (void *self);
  /// Set the Local Euler Pose object by specifying Local Position and Euler RPY..
  void (*set) (void *self, void *position, void *orientation);
  /// Return Local Position of Local Euler Pose 
  void (*getPosition) (void *self, void *position);
  /// Return Euler RPY orientation of Local Euler Pose 
  void (*getOrientation) (void *self, void *orientation);
  /// Convert Local Euler Pose to Local Pose
  void (*to_lPose) (void *self, void *localPose);
  /// Convert Local Euler Pose to Homogeneous Matrix
  void (*to_HMatrix) (void *self, void *homogeneous);
} drdc_lePose_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

drdc_Vector_t *new_Vector(unsigned char dsize);

/** 
 * Local Position Constructor
 * 
 * 
 * @return 
 */
drdc_lPosn_t *new_lPosn();

/** 
 * World Position (UTM) Constructor
 * 
 * 
 * @return 
 */
drdc_WUTMPosn_t *new_WUTMPosn();


/** 
 * World Position Constructor
 * 
 * 
 * @return 
 */
drdc_WPosn_t *new_WPosn();

/** 
 * Euler RPY Constructor
 * 
 * 
 * @return 
 */
drdc_eOrient_t *new_eOrient();

/** 
 * Quaternion Constructor
 * 
 * 
 * @return 
 */
drdc_Orient_t *new_Orient();

/** 
 * Homogeneous Constructor
 * 
 * 
 * @return 
 */
drdc_HMatrix_t *new_HMatrix();

/** 
 * World Pose Constructor
 * 
 * 
 * @return 
 */
drdc_WPose_t *new_WPose();

/** 
 * Local Pose Constructor
 * 
 * 
 * @return 
 */
drdc_lPose_t *new_lPose();

/** 
 * World Pose (UTM) Constructor
 * 
 * 
 * @return 
 */
drdc_WUTMPose_t *new_WUTMPose();

/** 
 * Local Pose (Euler RPY) Constructor
 * 
 * 
 * @return 
 */
drdc_lePose_t *new_lePose();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef __cplusplus


class drdc_lPosn;
class drdc_WUTMPosn;
class drdc_WPosn;
class drdc_eOrient;
class drdc_Orient;
class drdc_HMatrix;
class drdc_lPose;
class drdc_lePose;
class drdc_WPose;
class drdc_WUTMPose;



/**
 * \class drdc_lPosn 
 
 	<b> C++ Local Position Representation</b>
 * 
 */
class drdc_lPosn 
{
 protected:
  drdc_Vector_t *vector;	/**< Protected data vector */

 public:
  /// Constructor
  drdc_lPosn();

  /// Set the object by specifying cartesian x, y and z values
  void set(double x, double y, double z);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare two objects, self and object. The fuzz determines how
  /// close they are considered to be equal.
  int compare(drdc_lPosn localPosition, drdc_lPosn fuzz);
  /// Return the cartesian x value from the object.
  double getX();
  /// Return the cartesian y value from the object.
  double getY();
  /// Return the cartesian z value from the object.
  double getZ();
  /// Copy object.
  drdc_lPosn &operator = (drdc_lPosn localPosition);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Plus operator.
  drdc_lPosn operator +(drdc_lPosn localPosition);
  /// Negate operator.
  drdc_lPosn operator -();
  /// Minus operator.
  drdc_lPosn operator -(drdc_lPosn localPosition);
  /// Scale operator.
  drdc_lPosn operator *(double a);
  /// Vector dot operator.
  double dot(drdc_lPosn localPosition);
  /// Vector cross operator.
  drdc_lPosn cross(drdc_lPosn localPosition);
  /// Normalize the object.
  void normalize();
  /// Return the magnitude of the object.
  double magnitude();
  /**
   * Map Local Position to World UTM Position  
   *
   * It is a simple mapping function. The mapping scheme is shown as follows:
   * - x - Easting
   * - y - Northing
   * - z - Elevation
   * 
   * Other mapping schemes can be achieved by using coordinate transformations.
   */  
  drdc_WUTMPosn to_WUTMPosn(drdc_UTMZone_t zone);
  /**
   * Convert ECEF Position to World Position 
   * 
   * ECEF is a global position representation. Here we use Local
   * Position, which is really a cartesian system, to represent ECEF
   * system. 
   *
   * @param falseElevation False elevation.
   */
  drdc_WPosn to_WPosn(double falseElevation);  
};




/**
 * \class drdc_WUTMPosn 
 
 	<b>C++ World UTM Position Representation</b>
 *
 */
class drdc_WUTMPosn 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */
  drdc_UTMZone_t zone;          /**< UTM zone */

 public:
  /// Constructor
  drdc_WUTMPosn();

  //~drdc_WUTMPosn();
  /// Set the object by specifying UTM easting, northing and elevation.
  void set(double easting, double northing, double elevation);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Set UTM zone
  void setZone(drdc_UTMZone_t zone);
  /// Return UTM zone
  drdc_UTMZone_t getZone();
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_WUTMPosn worldUTMPosition, drdc_WUTMPosn fuzz);
  /// Return the Easting value from the object.
  double getEasting();
  /// Return the Northing value from the object.
  double getNorthing();
  /// Return the Elevation value from the object.
  double getElevation();
  /// Copy object.
  drdc_WUTMPosn &operator = (drdc_WUTMPosn worldUTMPosition);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Plus operator.
  drdc_WUTMPosn operator +(drdc_WUTMPosn worldUTMPosition);
  /// Negate operator.
  drdc_WUTMPosn operator -();
  /// Minus operator.
  drdc_WUTMPosn operator -(drdc_WUTMPosn worldUTMPosition);
  /// Scale operator.
  drdc_WUTMPosn operator *(double a);
  /// Vector dot operator.
  double dot(drdc_WUTMPosn worldUTMPosition);
  /// Vector cross operator.
  drdc_WUTMPosn cross(drdc_WUTMPosn worldUTMPosition);

  /**
   * Map World UTM Position to Local Position
   *
   * It is a simple mapping function. The mapping scheme is shown as follows:
   * - x - Easting
   * - y - Northing
   * - z - Elevation
   *
   * Other mapping schemes can be achieved by using coordinate transformations.
   *
   * @return Local Position
   */
  drdc_lPosn to_lPosn();

  /**
   * Convert World UTM Position to World Position
   *
   *
   * @return World Position
   */
  drdc_WPosn to_WPosn();

};


/**
 * \class drdc_WPosn 
 
 	<b> C++ World Position Represenation</b>
 *
 */
class drdc_WPosn 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */

 public:
  /// Constructor
  drdc_WPosn();

  //~drdc_WPosn();
  /// Set the object by specifying longtitude, latitude and elevation.
  void set(double longtitude, double latitude, double elevation);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_WPosn worldPosition, drdc_WPosn fuzz);
  /// Return the longtitude value from the object.
  double getLongtitude();
  /// Return the latitude value from the object.
  double getLatitude();
  /// Return the Elevation value from the object.
  double getElevation();
  /// Copy object.
  drdc_WPosn &operator = (drdc_WPosn worldPosition);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Normalize lontitude to -180 to 180 degree and latitude to -90 to 90 degree.
  void normalize();
  /**
   * Convert World Position to ECEF Position
   *
   * @param falseElevation
   *
   * @return Cartesian position represented by Local Position
   */
  drdc_lPosn to_lPosn(double falseElevation);
  /**
   * Convert World Position to World UTM Position
   *
   *
   * @return
   */
  drdc_WUTMPosn to_WUTMPosn();
};





/**
 *\class drdc_eOrient
 
	 	<b>  C++ Euler RPY Representation</b>
 *
 */
class drdc_eOrient
{
 protected:
  drdc_Vector_t *vector;

 public:
  drdc_eOrient();

  //~drdc_eOrient();

  /// Set the object by specifying roll, pitch and yaw values
  void set(double roll, double pitch, double yaw);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_eOrient eulerRPY, drdc_eOrient fuzz);
  /// Return roll value
  double getRoll();
  /// Return pitch value
  double getPitch();
  /// Return yaw value
  double getYaw();
  /// Copy object.
  drdc_eOrient &operator = (drdc_eOrient eulerRPY);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Plus operator.
  drdc_eOrient operator +(drdc_eOrient eulerRPY);
  /// Negate operator.
  drdc_eOrient operator -();
  /// Minus operator.
  drdc_eOrient operator -(drdc_eOrient eulerRPY);
  /// Scale operator.
  drdc_eOrient operator *(double a);
  /**
   * Convert Euler RPY to Homogeneous Matrix
   *
   *
   * @return Homogeneous Matrix
   */
  drdc_HMatrix to_HMatrix();
  /**
   * Convert Euler RPY to Quaternion
   *
   *
   * @return Quaternion
   */
  drdc_Orient to_Orient();
};


/** \class drdc_Orient
 * <b> C++ Quaternion Representation </b>
 *
  Orientation for global and local poses should be represented by
quaternions. Quaternions are hypercomplex numbers discovered by W.R.
Hamilton in 1833. Unit quaternion representations, also known as Euler
parameters, of orientation are unique and exhibit the property that their
inverse is equal to their conjugate. Quaternions do not suffer from gimbal lock
because quaternion rotation operators are singularity-free unlike Euler Angles
and every other rotation operator in <b>SO</b>(3). 
The transmission of unique pose requires only 4 real numbers in comparison with 9 for a rotation matrix.
The quaternion \f$ \vec q \f$ representation used here follows this convention:
\f$ \vec q \equiv (q_{s},\vec{\mathbf{q}}) \equiv[q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$
where \f$ \vec q  =  q_s + q_x i + q_y j + q_z k \f$
where q_x is the imaginary projection along the i axis, q_y is the imaginary
projection along the j axis, q_z is the imaginary projection along the k axis, and
qs is the real scalar.

 <b> Quaternion Origin </b> 
 The quaternion q = [1.0, 0.0, 0.0, 0.0] is defined as the orientation origin and
represents the System pointing True North, in the sense of Euler yaw, while
having no pitch and no roll. Figure 1, illustrates point p1 is facing North along
the global orientation origin towards the True North pole. Imagine a pencil
facing True North and lying on a perfectly flat desk as an analogy of the
orientation origin in our representation. This orientation remains the origin no
matter where on the Earth the system is. This orientation definition is
JAUS-compliant to Section 2.4. 

  \image html "w_frame_coord.gif" "Figure 1 "



\sa  drdc_Orient_t   OOC Quaternion Representation

\see [Kuipers98Quaternions] for more infomrmation see http://www.amazon.com/Quaternions-Rotation-Sequences-Jack-Kuipers/dp/0691058725


 
 */
class drdc_Orient 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */

 public:
  /// Constructor
  drdc_Orient();

  //~drdc_Orient();
  /// Set the object by specifying Quaternion w, x, y and z components.
  void set(double w, double x, double y, double z);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_Orient quaternion, drdc_Orient fuzz);
  /// Return w component of the Quaternion
  double getW();
  /// Return x component of the Quaternion
  double getX();
  /// Return y component of the Quaternion
  double getY();
  /// Return z component of the Quaternion
  double getZ();
  /// Copy object.
  drdc_Orient &operator = (drdc_Orient quaternion);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Plus operator.
  drdc_Orient operator +(drdc_Orient quaternion);
  /// Negate operator.
  drdc_Orient operator -();
  /// Minus operator.
  drdc_Orient operator -(drdc_Orient quaternion);
  /// Scale operator.
  drdc_Orient operator *(double a);
  /// Quaternion multiplication operator
  drdc_Orient operator *(drdc_Orient quaternion);
  /// Quaternion - Local Position multiplication operator
  drdc_lPosn  operator *(drdc_lPosn localPosition);
  /// Quaternion - World UTM Position multiplication operator
  drdc_WUTMPosn operator *(drdc_WUTMPosn worldUTMPosition);
  /// Normalize Quaternion
  void normalize();
  /// Return magnitude of Quaternion
  double magnitude();
  /// Construct Quaternion from Rotation of a axis
  void fromRotAxis(const Axis_t axis, const double theta);
  /// Construct Quaternion from rotating an angle about a unit vector
  void fromRotVec(double theta, drdc_lPosn unitVector);
  /// Convert Quaternion to Rotation Vector (angle and unit vector).
  void toRotVec(double *theta, drdc_lPosn *unitVector);
  /// Create identity Quaternion
  void identity();
   /// Inverse a Quaternion
  drdc_Orient inverse();
  /**
   * Convert Quaternion to Homogeneous Matrix
   *
   *
   * @return
   */
  drdc_HMatrix to_HMatrix();
  /**
   *  Convert Quaternion to Euler RPY
   *
   *
   * @return
   */
  drdc_eOrient to_eOrient();
};


/** 
 * C++ Homogeneous Matrix Representation
 *
 */
class drdc_HMatrix 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */

 public:
  /// Constructor
  drdc_HMatrix();

  //~drdc_HMatrix();
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_HMatrix homogeneous, drdc_HMatrix fuzz);
  /// Return the translation part of the Homogeneous Matrix
  drdc_lPosn getPosition();
  /// Set the translation part of the Homogeneous Matrix
  void setPosition(drdc_lPosn localPosition);
  /// Copy object.
  drdc_HMatrix &operator = (drdc_HMatrix homogeneous);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Plus operator.
  drdc_HMatrix operator +(drdc_HMatrix homogeneous);
  /// Negate operator.
  drdc_HMatrix operator -();
  /// Minus operator.
  drdc_HMatrix operator -(drdc_HMatrix homogeneous);
  /// Scale operator.
  drdc_HMatrix operator *(double a);
  /// Homogeneous Matrix multiplication operator
  drdc_HMatrix operator *(drdc_HMatrix homogeneous);
  /// Homogeneous Matrix - Local Position multiplication operator
  drdc_lPosn  operator *(drdc_lPosn localPosition);
  /// Homogeneous Matrix - World UTM Position multiplication operator
  drdc_WUTMPosn operator *(drdc_WUTMPosn worldUTMPosition);
 /// Normalize a Homogeneous Matrix
  void normalize();
  /// Transpose a Homogeneous Matrix
  drdc_HMatrix transpose();
  /// Construct Homogeneous Matrix from rotation of an axis
  void fromRotAxis(const Axis_t axis, const double theta);
  /// Construct Homogeneous Matrix from rotation vector
  void fromRotVec(double theta, drdc_lPosn unitVector);
  /// Construct Homogeneous Matrix from DH representation
  void fromDH(double linkLength, double twistAngle, double jointOffset, double jointAngle);
  /// Construct Homogeneous Matrix from link specification struct
  void fromLink(drdc_LinkSpecs_t linkSpec, double jointOffsetOrAngle);
  /// Convert Homogeneous Matrix to rotation vector
  void toRotVec(double *theta, drdc_lPosn *unitVector);
  /// Create an identity Homogeneous Matrix
  void identity();
  /**
   * Inverse a Homogeneous Matrix
   *
   *
   * @return
   */
  drdc_HMatrix inverse();
  /**
   * Convert Homogeneous Matrix to Local Pose
   *
   *
   * @return
   */
  drdc_lPose to_lPose();
  /**
   * Convert Homogeneous Matrix to Local Euler Pose
   *
   *
   * @return
   */
  drdc_lePose to_lePose();
  /**
   * Convert Homogeneous Matrix to Quaternion
   *
   *
   * @return
   */
  drdc_Orient to_Orient();
  /**
   * Convert Homogeneous Matrix to Euler RPY
   *
   *
   * @return
   */
  drdc_eOrient to_eOrient();
};




/**
 * \class drdc_lPose 
 
 	<b> C++ Local Pose Representation </b> 
   Robot Frame of Reference            or Local Pose
The definition applies to the local robot coordinate frame of reference . The
robot origin/frame of reference shall attach itself to the centre of the front
axle/rotation axis, or single axis of wheels. If the robot has legs, then shall
attach itself to the bottom centre of the front hip joint. The exact placement
must be visible from outside of the vehicle so as to allow for calibration
through survey. Figure 2 demonstrates the local coordinate frame of reference
  affixed to the front axle of a multi-axle UGV. If it is an aerial vehicle, the
reference frame shall attach to the bottom centre of the fuselage for fixed
wing or rotary aircraft. Note in Figure 2 that the z-axis points downward from
 . This z-axis direction means that clockwise rotations are positive. This
selection coincides with the de facto aerospace standard as well as the
coordinate frame of reference for most commercial inertial measurement unit
(IMU) sensors. The x-axis extends forward from the vehicle in the along-axis
direction. This means that forward motion is positive when measured relative to a previous pose. The y-axis, or across-axis, extends out from the local pose
origin in the right-handed sense.

\image html "local_frame.gif" "Figure 2 "

\image html "local_frame_leg.gif" "Figure 3"

 *
 */
class drdc_lPose 
{
 protected:
  drdc_Vector_t *vector;
 public:
  /// Constructor
  drdc_lPose();

  //~drdc_lPose();
  /// Set the object by specifying Local Position and Quaternion orientation
  void set(drdc_lPosn position, drdc_Orient orientation);
  /// Set the object by using array data type.
  void set(const double *array);
   /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_lPose localPose, drdc_lPose fuzz);
  /// Return Local Position
  drdc_lPosn getPosition();
  /// Return Quaternion orientation
  drdc_Orient getOrientation();
  /// Copy object.
  drdc_lPose &operator = (drdc_lPose localPose);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// Local Pose multiplication operator
  drdc_lPose operator *(drdc_lPose localPose);
  ///  Local Pose - Local Position multiplication operator
  drdc_lPosn operator *(drdc_lPosn localPosition);
  /**
   * Convert ECEF Pose to World Pose
   *
   * @param falseElevation
   *
   * @return
   */
  drdc_WPose to_WPose(double falseElevation);
  /**
   * Convert Local Pose to Local Euler Pose
   *
   *
   * @return
   */
  drdc_lePose to_lePose();
  /**
   * Convert Local Pose to Homogeneous Matrix
   *
   *
   * @return
   */
  drdc_HMatrix to_HMatrix();
  /**
   * Convert Local Pose to World UTM Pose
   *
   * @param zone
   *
   * @return
   */
  drdc_WUTMPose to_WUTMPose(drdc_UTMZone_t zone);

};



/** \class drdc_lePose
 *  <b>C++ Local Euler Pose Representation</b>
  *
 */
class drdc_lePose 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */

 public:
  /// Constructor
  drdc_lePose();

  //~drdc_lePose();
  /// Set the object by specifying Local Position and Euler RPY orientation.
  void set(drdc_lPosn position, drdc_eOrient orientation);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_lePose localEulerPose, drdc_lePose fuzz);
  /// Return Local Position
  drdc_lPosn getPosition();
  /// Return Euler RPY orientation
  drdc_eOrient getOrientation();
  /// Copy object.
  drdc_lePose &operator = (drdc_lePose localEulerPose);
  /// Return the nth element from the object.
  double operator [] (int n);
  /**
   * Convert Local Euler Pose to Local Pose
   *
   *
   * @return
   */
  drdc_lPose to_lPose();
  /**
   * Convert Local Euler Pose to Homogeneous Matrix
   *
   *
   * @return
   */
  drdc_HMatrix to_HMatrix();
};


/** \class drdc_WPose
 * World Coordinate Frame of Reference <b> {W} </b> or Global Pose

		C++ World Pose Representation
 The global pose, or frame \em W, provides an unambiguous world reference that should allow experimentation and
operation over long distances. This section outlines the adopted convention for global pose with respect to
the Earth. The world or global coordinate frame of reference can be referred
to as W and represents the pose of the object with respect to the global origin.
The global position in W shall be represented internally by the 2-dimensional
spherical coordinates: latitude, longitude, and elevation (height). Refer to Figure 1 below.

\image html "w_frame_coord.gif" "Figure 1 "

  The Cartesian coordinates at the centre of 1 denote the origin, \f$ \alpha \f$  is
the latitude angle, and \f$ \beta \f$ is the longitude angle. Longitude angle measurement
is measured from X-axis origin, Greenwich Meridian (Prime Meridian),
where positive values are East from Greenwich and negative values are West
from Greenwich. The Y-axis origin is the Equator for latitude angle
measurement, where positive values are northward from the Equator to the
North Pole and negative values are southward from the Equator to the South
Pole. The radius \f$ r_i \f$ origin is the centre of the Earth. This standard proposes
adding a False Elevation to the radius origin to represent elevation from Mean
Sea Level (MSL), also known as orthometric height, where positive values are
above MSL (accounting for geoid gravity model variances which may perturb
local values) and negative values are below MSL. Elevation in this standard is
assumed constant and does not take into account gravity models to adjust
MSL regionally. The world coordinate frame of reference will use the
geographic coordinates latitude, longitude, and elevation as the position
3-vector.

Latitude and longitude represent angles measured from an arbitrary global
origin. Elevation represents distance from an arbitrary origin. The World
coordinate frame W will use the World Geodetic System 1984 (WGS84)
geodetic datum. The WGS84 ellipsoid parameters are listed in Table 3. Please
refer to Figure 1 for a representation of the W frame.


  
 *
 */
class drdc_WPose 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */
 public:
  /// Constructor
  drdc_WPose();

  //  ~drdc_WPose();
  /// Set the object by specifying World Position and Quaternion orientation
  void set(drdc_WPosn position, drdc_Orient orientation);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_WPose worldPose, drdc_WPose fuzz);
  /// Return World Position
  drdc_WPosn getPosition();
  /// Return Quaternion orientation
  drdc_Orient getOrientation();
  /// Copy object.
  drdc_WPose &operator = (drdc_WPose worldPose);
  /// Return the nth element from the object.
  double operator [] (int n);
  /**
   * Convert World Pose to Local Pose
   *
   * @param falseElevation
   *
   * @return
   */
  drdc_lPose to_lPose(double falseElevation);
  /**
   *  Convert World Pose to World UTM Pose
   *
   *
   * @return
   */
  drdc_WUTMPose to_WUTMPose();
};





/** \class drdc_WUTMPose
 * World UTM Pose Representation
 *
 */
class drdc_WUTMPose 
{
 protected:
  drdc_Vector_t *vector;        /**< Data vector */
  drdc_UTMZone_t zone;          /**< UTM zone */

 public:
  /// Constructor
  drdc_WUTMPose();

  //  ~drdc_WUTMPose();
  /// Set the object by specifying World UTM Position and quaternion.
  void set(drdc_WUTMPosn position, drdc_Orient orientation);
  /// Set the object by using array data type.
  void set(const double *array);
  /// Set UTM zone
  void setZone(drdc_UTMZone_t zone);
  /// Return UTM zone
  drdc_UTMZone_t getZone();
  /// Convert data in the object to data array type.
  void toArray(double *array);
  /// Compare the two objects. The fuzz determines how close they are
  /// considered to be equal.
  int compare(drdc_WUTMPose worldPose, drdc_WUTMPose fuzz);
  /// Return World UTM Position
  drdc_WUTMPosn getPosition();
  /// Return Quaternion orientation
  drdc_Orient getOrientation();
  /// Copy object.
  drdc_WUTMPose &operator = (drdc_WUTMPose worldUTMPose);
  /// Return the nth element from the object.
  double operator [] (int n);
  /// World UTM Pose multiplication
  drdc_WUTMPose operator *(drdc_WUTMPose worldUTMPose);
  /// World UTM Pose - Position multiplication
  drdc_WUTMPosn operator *(drdc_WUTMPosn worldUTMPosition);
  /**
   * Convert World UTM Pose to World Pose
   *
   *
   * @return
   */
  drdc_WPose to_WPose();
  /**
   * Map World UTM Pose to Local Pose
   *
   *
   * @return
   */
  drdc_lPose to_lPose();

};


#endif /* __cplusplus */


#endif
