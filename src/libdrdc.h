/***\file librdc.h   *********************************************************
                           
 H.File   $Header:  $
     
 Date Started: -2015

 Date: 	$Date:  $
 * 
 Author:  $Name:   $

 Purpose:  The toplevel C header

 Version:  $Id: doublerow.h,v 1.2 2007/08/24 14:27:29 cvsuser Exp $

 Revision: $Revision:  $
 * 
 * 
 Log:   $Log:   $
 *
 * \brief librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

 HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
 OF NATIONAL DEFENCE, CANADA, 2007

 Developed by: Tie Peng and Erickson, D. (DRDC Suffield)

 This library is free software;.  You can redistribute it and/or modify
 it under the terms and conditions of the GNU Lesser General Public
 License as published by the Free Software Foundation; either

 Version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 	You should have received a copy of the GNU Lesser General Public
 	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 	USA

 Licence is located in license.txt in libdrdc source root
*/


#ifndef LIBDRDC_H
#define LIBDRDC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <stdio.h>
#include "except.h"
//#include "sglib.h"

/**
 * @mainpage libdrdc API Documentation 
 * 
 * The libdrc package contains the libdrdc software standards library
 * including internal nomenclature, definitions, units of measure,
 * coordinate reference frames, and representations for use in
 * autonomous systems research.  This library is a configurable,
 * portable C-function wrapped C++ / Object Oriented C library
 * developed to be independent of software middleware, system
 * architecture, processor, or operating system.  It is designed to
 * use the automatically-tuned linear algebra suite (ATLAS) and Basic
 * Linear Algebra Suite (BLAS) and port to firmware and software.  The
 * library goal is to unify data collection and representation for
 * various microcontrollers and Central Processing Unit (CPU) cores
 * and to provide a common Application Binary Interface (ABI) for
 * research projects at all scales.  The library supports
 * multi-platform development and currently works on Windows, Unix,
 * GNU/Linux, and Real-Time Executive for Multiprocessor Systems
 * (RTEMS). This library is made available under LGPL version 2.1
 * license.
 *
 * For more information, please see 
 * http://aiss.suffield.drdc-rddc.gc.ca/libdrdc/doku.php
 */


/** \note
	These are the data types that all functions should agree with:
	JAUS Data Types 
 - Data Type	        Size (in Bytes)					Representation
 - Byte	               	 	1										8 bit unsigned integer
 - Short Integer	        	2										16 bit signed integer
 - Integer	                4										32 bit signed integer
 - Long Integer	        	8										64 bit signed integer
 - Unsigned Short Integer	2										16 bit unsigned integer
 - Unsigned Integer	      4										32 bit unsigned integer
 - Unsigned Long Integer		8										64 bit unsigned integer
 - Float	                	4										IEEE 32 bit floating point number
 - Long Float	            8										IEEE 64 bit floating point number (double precision)
*/


//! Local constants defines
#define PI         3.14159265358979323846
#define HALF_PI    1.57079632679489661923
#define TWO_PI     6.28318530717958647693

#define DOUBLE_FUZZ 2.2204460492503131e-16
#define RADIAN_FUZZ 0.000001

#define DRDC_BIG_ENDIAN  0

/**
  * Radians to/from Degrees conversions -DRE 2008
  */
#define deg2rad   PI / 180.0
#define rad2deg   180.0 / PI

/**
  * Degrees to Radians DEG2RAD -DRE 2008
	* @param x: degree value to convert to radians.
  */
#define DEG2RAD(x)  ( x * deg2rad)
/**
  * Radians to Degrees  RAD2DEG -DRE 2008
	* @param x: radian value to convert to degrees.	
  */
#define RAD2DEG(x)  ( x * rad2deg)

typedef unsigned char        uint8_t;
typedef char                 sint8_t;
typedef unsigned short       uint16_t;
typedef short                sint16_t;
typedef unsigned long        uint32_t;
typedef long                 sint32_t;
typedef unsigned long long   uint64_t;
typedef long long            sint64_t;
//typedef float                float32;
//typedef double               float64;


//! Axis define which axis involved in operation
typedef enum 
{
  AXIS_ERR,
  AXIS_X, 
  AXIS_Y, 
  AXIS_Z,
	AXIS_NUMBER
} Axis_t;

/**
 * Union for Double precision Floating Point Data and other types that can fit that space.
 */
typedef union 
{
  uint64_t dWord;
  uint32_t word[2];
  uint8_t  byte[8];
  double value;
} DoubleUnion_t;

/**
 * Union for Single precision Floating Point Data and other types that can fit that space.
 */
typedef union 
{
  uint32_t word;
  uint8_t  byte[4];
  float  value;
} FloatUnion_t;

/**
 *  Square defined as SQ() macro
 */
#define SQ(x) ((x)*(x))
#define CLOSE(a, b, eps) ((fabs((a) - (b)) < (eps)) ? 1 : 0)
#define DOUBLE_IS_ZERO(d) ((fabs(d) < DOUBLE_FUZZ) ? 1 : 0)


/*
	Include the libdrdc exception context
*/
define_exception_type(int);
extern struct exception_context the_exception_context[1];

#define UNRECOGNIZED_UNIT       (11)
#define UNRECOGNIZED_ENUM_ITEM  (12)
#define DIVIDED_BY_ZERO         (13)
#define BLAS_TRANSPOSE_OPTION_ERROR (14)
#define CALLOC_NULL_ERROR           (15)
#define UNRECOGNIZED_INDEX       (16)
#define UNINITILIZED_UTM_ZONE    (17)
#endif
