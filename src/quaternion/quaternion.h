// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
// OF NATIONAL DEFENCE, CANADA, 2007

// Developed by: Tie Peng, Erickson, D. (DRDC Suffield)

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
 * Purpose      : to identify the quaternion-related functions
 * Revision     : $Id: quaternion.h,v 1.8 2008/09/23 14:42:04 cvsuser Exp $
 */


#ifndef QUATERNION_H
#define QUATERNION_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


// global includes
#include <math.h>

// local includes
#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif

#ifndef MATRIX_OPS_H
#include "matrix_ops.h"
#endif


/*!
	\brief
	
	Quaternions, discovered by Hamilton, represent a point on a 4-dimensional hypercube, are suitable for 3-dimensional orientation 
	representation.

	\details
	These functions handle quaternion representations and operations, exclusive of the type of orientation used.	The type of operations contained herein are:
	
	- Conversion to / from Euler Angle RPY  (rotation sequence ZYX)
	- Quaternion conjugates
	- Quaternion multiplication
	- Quaternion inverse
	- Quaternion division
	- Conversion to / from angle-axis / rotation vector representation
	- Conversion to / from rotation matrix
	
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
\see [Kuipers98Quaternions] for more infomrmation see http://www.amazon.com/Quaternions-Rotation-Sequences-Jack-Kuipers/dp/0691058725


*/	


/**
 * @addtogroup quaternion Quaternion Operations API
 */
/** @{ */


/**
  QUAT_ORIGIN The quaternion q = [1.0, 0.0, 0.0, 0.0] is defined as the orientation origin and
represents the System pointing True North, in the sense of Euler yaw, while
having no pitch and no roll. Figure 1, illustrates point p1 is facing North along
the global orientation origin towards the True North pole. Imagine a pencil
facing True North and lying on a perfectly flat desk as an analogy of the
orientation origin in our representation. This orientation remains the origin no
matter where on the Earth the system is. This orientation definition is
JAUS-compliant to Section 2.4. 

  \image html "w_frame_coord.gif" "Figure 1 "
*/
#define QUAT_ORIGIN   [1.0, 0.0, 0.0, 0.0]

/** 
 *  %RPY to %Quaternion
 * 
 * Converts the rotation described by the three Euler angles (yaw,
 * pitch, row) into the four-element quaternion vector q
 *
 * @param rpyVector Input. %RPY vector - [roll, pitch, yaw].
 * @param quaternion Output. %Quaternion vector - \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 */
int EulerRPYToQuat(const double *rpyVector, double *quaternion);

/** 
 * %Quaternion to %RPY
 * 
 * Converts the four-element unit quaternion \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$ into the
 * equivalent three Euler angle rotations (yaw, pitch, row).
 *
 * @param quaternion Intput. %Quaternion vector - \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * @param rpyVector Output. %RPY vector - [roll, pitch, yaw].
 * 
 */
int QuatToEulerRPY(const double *quaternion, double *rpyVector);

/** 
 * %Quaternion Multiplication
 * 
 * Computes %Quaternion-%Quaternion product.
 *
 * @param quaternion1 Input. %Quaternion vector1 - \f$ [q_{s_1},<q_{x_1},q_{y_1},q_{z_1}>]^{T} \f$.
 * @param quaternion2 Input. %Quaternion vector2 - \f$ [q_{s_2},<q_{x_2},q_{y_2},q_{z_2}>]^{T} \f$.
 * @param resultQuaternion Output. %Quaternion Product result - \f$ [q_{s_r},<q_{x_r},q_{y_r},q_{z_r}>]^{T} \f$.
 * 
 */
int QuatQuatMult(double *quaternion1, double *quaternion2, double *resultQuaternion);

/** 
 * %Quaternion Division
 * 
 * Computes %Quaternion-%Quaternion division.
 *
 * @param quaternion1 Input. %Quaternion vector1 - \f$ [q_{s_1},<q_{x_1},q_{y_1},q_{z_1}>]^{T} \f$.
 * @param quaternion2 Input. %Quaternion vector2 - \f$ [q_{s_2},<q_{x_2},q_{y_2},q_{z_2}>]^{T} \f$.
 * @param resultQuaternion Output. %Quaternion Product result - \f$ [q_{s_r},<q_{x_r},q_{y_r},q_{z_r}>]^{T} \f$.
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * a divied-by-zero error occurs.
 */
int QuatQuatDiv(double *quaternion1, double *quaternion2, double *resultQuaternion);

/** 
 * %Quaternion Inversion
 *
 * Computes the inversion of a %Quaternion.
 * 
 * @param quaternion Input/Output. Input is overwritten by the inversed
 * %Quaternion -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * a divied-by-zero error occurs.
 */
int QuatInverse(double *quaternion);

/** 
 * Conjugate %Quaternion
 *
 * Computes the conjugate of a %Quaternion.
 * 
 * @param quaternion Input/Output. Input is overwritten by the conjugate
 * %Quaternion -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 */
int QuatConjugate(double *quaternion);

/** 
 * Quaterion Magnitude
 * 
 * Computes the magnitude of a quaternion.
 *
 * @param quaternion Intput. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 * @return It returns quaterion magnitude.
 */
double QuatMagnitude(const double *quaternion);

/** 
 * %Quaternion and Vector Product 
 * 
 * @param quaternion Intput. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * @param vector Input. %Cartesian vector - [x, y, z].
 * @param resultVector Output. %Cartesian vector - [x, y, z].
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * divied-by-zero error occurs.
 */
int QuatVectorMult(double *quaternion, double *vector, double *resultVector);

/** 
 * %Quaternion to Homogeneous Transformation
 *
 * Converts a quaternion to a rotation matrix ( inside homogeneous matrix ).
 * 
 * @param hMatrix Input. Homogeneous matrix described by a 16-vector.
 * @param quaternion Output. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 */
int HMatrixToQuat(const double *hMatrix, double *quaternion);

/** 
 * Homogeneous Transformation to %Quaternion
 * 
 * Converts a rotation matrix ( inside homogeneous matrix ) to a quaternion.
 *
 * @param quaternion Intput. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * @param hMatrix Output. Homogeneous matrix described by a 16-vector.
 * 
 * @return 
 */
int QuatToHMatrix(const double *quaternion, double *hMatrix) ;

/** 
 * Unitize a %Quaternion
 * 
 * Computes normalized quaternion.
 *
 * @param quaternion Input/Output. Input  is overwritten by the unitized
 * Quaternion -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 * @return zero if successful. Otherwise, it returns one if
 * a divied-by-zero error occurs. 
 */
int QuatNormalize(double *quaternion);

/** 
 * Rotation about an Axis to %Quaternion
 * 
 * Computes a quaternion from a rotation about an cartesian axis.
 *
 * @param axis Input. Enumeration type, AXIS_X, AXIS_Y, or AXIS_Z.
 * @param theta Input. Rotation angle in radians. 
 * @param quaternion  Output. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * a undefined AXIS type error occurs.
 */
int RotAxisToQuat(const Axis_t axis, const double theta, double *quaternion);
/** 
 * %Quaternion to Rotation Vector
 *
 * Computes a rotation vector from a quaternion.
 * 
 * @param quaternion Input. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * @param theta Output. Rotation angle in radians.
 * @param vector Output. %Cartesian vector - [x, y, z].
 * 
 * @return 
 */
int QuatToRotVector(const double *quaternion, double *theta, double *vector);
/** 
 * Rotation Vector to %Quaternion
 * 
 * Computes a quaternion from a rotation about a vector.
 *
 * @param theta Input. Rotation angle in radians. 
 * @param vector Input. %Cartesian vector - [x, y, z].
 * @param quaternion Output. %Quaternion vector -  \f$ [q_{s},<q_{x},q_{y},q_{z}>]^{T} \f$.
 * 
 */
int RotVectorToQuat(const double theta, const double *vector, double *quaternion);

/** @} */

#endif 
