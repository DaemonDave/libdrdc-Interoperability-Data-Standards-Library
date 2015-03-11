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

// \note Some functions are copied and modified from OpenJaus.

/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: data_conv.h,v 1.5 2008/09/15 14:05:13 cvsuser Exp $
 */


#ifndef DATA_CONV_H
#define DATA_CONV_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif


typedef uint32_t ieeeFpd32;
typedef uint64_t ieeeFpd64;

#define JAUS_BYTE_RANGE         											255.0
#define JAUS_INTEGER_RANGE             								4294967294.0    //! \note This range is incorrect, but is as defined by Jaus
#define JAUS_LONG_RANGE                			 (double) 18446744073709551614.0
#define JAUS_SHORT_RANGE                							65534.0 // \note This range is incorrect, but is as defined by Jaus
#define JAUS_UNSIGNED_INTEGER_RANGE          				  4294967294.0 // \note This range is incorrect, but is as defined by Jaus
#define JAUS_UNSIGNED_LONG_RANGE             (double) 1.8446744073709552e19
#define JAUS_UNSIGNED_SHORT_RANGE               			65535.0 // \note This range is incorrect, but is as defined by Jaus


/*!
	\brief
	
	Data Format Conversions for data conventions:
	
	- IEEE single precision 
	- IEEE double precision
	- Double
	- Float
	- JAUS data formats
	
*/


/**
 * @addtogroup data_conv Data Format Conversions
 */
/** @{ */

/** 
 * Converts single to float point data represented by 32-bit unsigned integer format.
 * 
 * @param value Input. Single float point data.
 * 
 * @return Converted float point data represented by uint32 data type.
 */
ieeeFpd32 ieeeFpd32FromFloat(const float value);
	
/** 
 * Converts double to float point data represented by 64-bit unsigned integer format.
 * 
 * @param value Input. Double float point data array.
 * 
 * @return Converted float point data represented by uint64 data type.
 */
ieeeFpd64 ieeeFpd64FromDouble(const double value);

/** 
 * Converts float point data represented by 32-bit unsigned integer format to single.
 * 
 * @param input Input. Float point data represented by uint32 data type.
 * 
 * @return Converted single float point data.
 */
float ieeeFpd32ToFloat(const ieeeFpd32 input);

/** 
 * Converts float point data represented by 64-bit unsigned integer format to double.
 * 
 * @param input Input. Float point data array represented by uint64 data type.
 * 
 * @return Converted double float point data.
 */
double ieeeFpd64ToDouble(const ieeeFpd64 input);

/** 
 * Double to Jaus Byte Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns unsigned 8-bit Jaus byte.
 */
uint8_t jausByteFromDouble(double value, const double min, const double max);

/** 
 * Jaus Byte to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausByteToDouble(const uint8_t value, const double min, const double max);

/** 
 * Jaus Integer to Double Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausIntegerToDouble(const sint32_t value, const double min, const double max);


/** 
 * Double to Jaus Integer Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns signed 32-bit Jaus integer data.
 */
sint32_t jausIntegerFromDouble(double value, const double min, const double max);


/** 
 * Jaus Long Type to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausLongToDouble(const sint64_t value, const double min, const double max);


/** 
 * Double to Jaus Long Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns signed 64-bit Jaus long integer data.
 */
sint64_t jausLongFromDouble(double value, const double min, const double max);


/** 
 * Jaus Short Type to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausShortToDouble(const sint16_t value, const double min, const double max);


/** 
 * Double to Jaus Short Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns signed 16-bit Jaus short integer data.
 */
sint16_t jausShortFromDouble(double value, const double min, const double max);


/** 
 * Jaus Unsigned Integer Type to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausUnsignedIntegerToDouble(const uint32_t value, const double min, const double max);


/** 
 * Double to Jaus Unsigned Integer Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns unsigned 32-bit Jaus integer data.
 */
uint32_t jausUnsignedIntegerFromDouble(double value, const double min, const double max);


/** 
 * Jaus Unsigned Long Type to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausUnsignedLongToDouble(const uint64_t value, const double min, const double max);


/** 
 * Double to Jaus Unsigned Long Type Conversion 
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns unsigned 64-bit Jaus long integer data.
 */
uint64_t jausUnsignedLongFromDouble(double value, const double min, const double max);


/** 
 * Jaus Unsigned Short Type to Double Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns double float point data.
 */
double jausUnsignedShortToDouble(const uint16_t value, const double min, const double max);


/** 
 * Double to Jaus Unsigned Short Type Conversion
 * 
 * @param value Data to be converted.
 * @param min Lower limit.
 * @param max Upper limit.
 * 
 * @return It returns unsigned 16-bit Jaus short integer data.
 */
uint16_t jausUnsignedShortFromDouble(double value, const double min, const double max);


/** @} */
#endif
