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
 * Revision     : $Id: homogeneous.h,v 1.6 2008/09/15 14:05:13 cvsuser Exp $
 */


#ifndef HOMOGENEOUS_H
#define HOMOGENEOUS_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif

#include <float.h>
#include <math.h>

#include "matrix_ops.h"

/* \todo investigate how close pitch is to zero for RPY to degenerate */

/**
 * @addtogroup homogeneous Homogeneous Matrix Operations API
 */
/** @{ */

/** 
 * Set the Translational Component of a Homogeneous Matrix
 * 
 * @param vector Input. %Cartesian vector - [x, y, z].
 * @param hMatrix Input/Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 */
int HMatrixSetTranslation(const double *vector, double *hMatrix);

/** 
 * Get the Translational Component of a Homogeneous Matrix
 * 
 * @param hMatrix Input. Homogeneous matrix represented by a 16-vector (column major).
 * @param vector Output.  %Cartesian vector - [x, y, z].
 * 
 */
int HMatrixGetTranslation(const double *hMatrix, double *vector);

/** 
 * Rotation Vector to Homogeneous Matrix
 * 
 * @param theta Input. Rotation angle in radians.
 * @param vector Input. Unit vector represented by a cartesian vector - [x, y, z].
 * @param hMatrix Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 */
int RotVectorToHMatrix(const double theta, const double *vector, double *hMatrix);

/** 
 * Homogeneous Matrix to Rotation Vector
 * 
 * @param hMatrix Input. Homogeneous matrix represented by a 16-vector (column major).
 * @param theta Output. Rotation angle in radians
 * @param vector Output. Unit vector represented by a cartesian vector - [x, y, z].
 * 
 * @return It returns zero if successful. 
 */
int HMatrixToRotVector(const double *hMatrix, double *theta, double *vector);

/** 
 * Euler Angle RPY to Homogeneous Matrix
 * 
 * @param rpyVector Input. %RPY vector - [roll, pitch, yaw].
 * @param hMatrix Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 */
int EulerRPYToHMatrix(const double *rpyVector, double *hMatrix);
/** 
 * Homogeneous Matrix to Euler Angle RPY
 * 
 * @param hMatrix Input. Homogeneous matrix represented by a 16-vector (column major).
 * @param rpyVector Output. %RPY vector  - [roll, pitch, yaw].
 * 
 */
int HMatrixToEulerRPY(const double *hMatrix, double *rpyVector);

/** 
 * Normalize a Homogeneous Matrix
 * 
 * @param hMatrix Input/Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 */
int HMatrixNormalize(double *hMatrix);

/** 
 * Rotation about an Axis to Homogeneous Matrix 
 *
 * Computes a homogeneous transformation representing a rotation of
 * Theta radians about the axis.
 *
 * @param axis Input. Enumeration type, AXIS_X, AXIS_Y, or AXIS_Z.
 * @param theta Input. Rotation angle in radians. 
 * @param hMatrix Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * a undefined enumeration type error occurs.
 */
int RotAxisToHMatrix(Axis_t axis, const double theta, double *hMatrix);

/** 
 * Inverse a Homogeneous Matrix
 * 
 * @param hMatrix Input/Output. Homogeneous matrix represented by a 16-vector (column major).
 * 
 */
int HMatrixInverse(double *hMatrix);

/** 
 * Homogeneous Matrix from Manipulator Linkage Specification 
 * 
 * @param linkLength Link length (a).
 * @param twistAngle  Twist angle (alpha).
 * @param jointOffset Joint offset (d).
 * @param jointAngle Joint angle (theta).
 * @param hMatrix Result homogeneous matrix. 
 */
int HMatrixLink(const double linkLength, const double twistAngle, const double jointOffset, const double jointAngle, double *hMatrix);


/** @} */

#endif

