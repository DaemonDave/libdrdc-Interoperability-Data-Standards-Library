// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
// OF NATIONAL DEFENCE, CANADA, 2007

// Developed by:  Tie Peng and Erickson, D. (DRDC Suffield)

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

/**  $Id: unit_conv.h,v 1.10 2008/10/27 20:29:40 cvsuser Exp $
 * Description  : libdrdc - $RCSfile: unit_conv.h,v $
 * Author       : Tie Peng
 * Purpose      : SI Units and conversions
 * Revision     : $Id: unit_conv.h,v 1.10 2008/10/27 20:29:40 cvsuser Exp $
 */


#ifndef UNIT_CONV_H
#define UNIT_CONV_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif
	

#include <float.h>
#include <string.h>


/*!
	\brief
	
	Units of Measure conventions contains functions to convert various units of measure representations.
	
	- Volume
	- Area
	- Speed
	- Mass
	- Current
	- Temperature
	- 

*/

/**
 * @addtogroup unit_conv Unit Conventions API
 */
/** @{ */


/**
 * Unit Conversion Structure
 


	This data structure to encapsulate data value and unit for units of measure. \
  This is the base class for units of measure at the C level. If there is another unit of \
	measure for the following units described, please provide the conversion and include \
	documentation inside the following code documentation.
	
	\see http://en.wikipedia.org/wiki/SI#Units for a description of System International
		
	-Thanks  Dave
 */
typedef struct 
{
  char   *unit;
  double factor;
} UnitConv_t;


/** \var VOLUME_UNITS 

	volume units of measure

*/
static UnitConv_t VOLUME_UNITS[] = 
{
  { "m^3",    1.000000000000000 },
  { "mm^3",    0.000000001000000 },
  { "cm^3",    0.000001000000000 },
  { "usgallon",    0.003785411784000 },
  { "brgallon",    0.004546090000000 },
  { "ml",    0.000001000000000 },
  { "liter",    0.001000000000000 },
};
/** \def VOLUME_UNITS_NUM
number of units of measure volume units 
*/
#define VOLUME_UNITS_NUM 7  
/** \var DISTANCE_UNITS 
	1 dimensional distance units of measure
*/
static UnitConv_t DISTANCE_UNITS[] = 
{
  { "m",    1.000000000000000 },
  { "mm",    0.001000000000000 },
  { "cm",    0.010000000000000 },
  { "km",    1000.000000000000000 },
  { "inch",    0.025400000000000 },
  { "foot",    0.304800000000000 },
  { "yard",    0.914400000000000 },
  { "mile",    1609.344000000000051 },
};
/** \def DISTANCE_UNITS_NUM 
	number of units of measure distance units
*/
#define DISTANCE_UNITS_NUM 8 

/** \var MASS_UNITS 
	mass units of measure
*/
static UnitConv_t MASS_UNITS[] = 
{
  { "kg",    1.000000000000000 },
  { "g",    0.001000000000000 },
  { "lbs",    0.453592370000000 },
  { "uston",    907.184740000000033 },
  { "brton",    1016.046908800000097 },
};
#define MASS_UNITS_NUM 5 //! \def number of units of measure mass units

/** \var VELOCITY_UNITS 
	velocity / speed  derived units of measure

*/
static UnitConv_t VELOCITY_UNITS[] = 
{
  { "m/s",    1.000000000000000 },
  { "mm/s",    0.001000000000000 },
  { "cm/s",    0.010000000000000 },
  { "km/s",    1000.000000000000000 },
  { "kph",    0.277777777777778 },
  { "mph",    0.447040000000000 },
};
/** \def VELOCITY_UNITS_NUM
 number of units of measure velocity units
*/
#define VELOCITY_UNITS_NUM 6 

/** \var AREA_UNITS 
	describes the type of area units of measure covered in conversions derived units of measure

*/
static UnitConv_t AREA_UNITS[] = 
{
  { "m^2",    1.000000000000000 },
  { "cm^2",    0.000100000000000 },
  { "mm^2",    0.000001000000000 },
  { "km^2",    1000000.000000000000000 },
  { "ft^2",    0.092903040000000 },
  { "yard^2",    0.836127360000000 },
  { "mile^2",    2589988.110336000099778 },
};

/** \def AREA_UNITS_NUM 
number of units of measure for areas units
*/
#define AREA_UNITS_NUM 7 


/** \var CURRENT_UNITS  
defines the electromagnetic current units of measure
 covered in conversions.   \see http://en.wikipedia.org/wiki/SI_electromagnetism_units
  for a complete list of electromagnetic base and derived units.
If there is another unit of measure for voltage, provide the conversion and include it here.
*/
static UnitConv_t CURRENT_UNITS[] = 
{
  { "A",    1.000000000000000 },
  { "unknown",    1.00000000000000 },
};
/** \def CURRENT_UNITS_NUM 
number of units of measure electromagnetic current units
*/
#define CURRENT_UNITS_NUM 2 

/** \var VOLTAGE_UNITS  
defines the electromagnetic potential difference or electromotive force units of measure
 covered in conversions.   \see http://en.wikipedia.org/wiki/SI_electromagnetism_units
  for a complete list of electromagnetic base and derived units
	
	If there is another unit of measure for voltage, provide the conversion and include it here
*/
static UnitConv_t VOLTAGE_UNITS[] = 
{
  { "V",    1.000000000000000 },
  { "unknown",    1.00000000000000 },
};
/** \def VOLTAGE_UNITS_NUM 
number of units of measure electromagnetic potential difference or electromotive force units of measure
*/
#define VOLTAGE_UNITS_NUM 2 




#define CELSIUS     (double) 273.15
#define FAHRENHEIT  (double) 5.0 / 9.0
#define RANKINE     FAHRENHEIT

/** TEMPERATURE_UNITS  defines the thermodynamic temperature units of measure
 covered in conversions.   \see http://en.wikipedia.org/wiki/Kelvin
  for a complete list of temperature base units
	If there is another unit of measure for temperature, provide the conversion and include it here
	
	\note The libdrdc default  temperature is CELSIUS, Centigrade,  which is Kelvin at an offset from the SI unit zero. This was chosen due to the large amount of data that is available on Celsius, therefore the reduced need for conversion, and that it is intuitive for most applications.
	
	
	If there is another unit of measure for temperature, provide the conversion and include it here
*/
static UnitConv_t TEMPERATURE_UNITS[] = 
{
  { "K",    1.000000000000000 },
  { "C",    1.000000000000000 },	
  { "F",    FAHRENHEIT },
  { "Rankine",    1.00000000000000 },
  { "unknown",    1.00000000000000 },		
};
/** TEMPERATURE_UNITS_NUM number of units of measure electromagnetic potential difference or electromotive force units of measure
*/
#define TEMPERATURE_UNITS_NUM 4




/** 
 * Converts the volume units to the SI unit - \f$ m^3 \f$.
 *
 * Units:
 * - usgallon
 * - brgallon
 * - ml
 * - \f$ cm^3 \f$
 * - \f$ mm^3 \f$
 * - litre
 *
 * @param unit Input. Unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the input units to the SI unit.
 */
double unitToSiVolume(const char *unit);

/** 
 * Converts the distance units to the SI unit - m.
 * 
 * Units:
 * - mm
 * - cm
 * - km
 * - inch
 * - foot
 * - yard
 * - mile
 *
 * @param unit Input. Unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the input units to the SI unit.
 */
double unitToSiDistance(const char *unit);
/** 
 * Converts the mass units to the SI unit - kg .
 * 
 * Units:
 * - g
 * - lbs
 * - uston
 * - brton
 *
 * @param[in] unit Input. Unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the input units to the SI unit.
 */
double unitToSiMass(const char *unit);

/** 
 * Converts the velocity units to the SI unit - m/s.
 *
 * Units:
 * - mm/s
 * - cm/s
 * - km/s
 * - kph
 * - mph
 * 
 * @param unit Input. Unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the input units to the SI unit.
 */
double unitToSiVelocity(const char *unit);
/** 
 * Converts the area units to the SI unit - \f$ m^2 \f$.
 *
 * Units:
 * - \f$ cm^2 \f$
 * - \f$ mm^2 \f$ 
 * - \f$ km^2 \f$ 
 * - \f$ ft^2 \f$ 
 * - \f$ yard^2 \f$
 * - \f$ mile^2 \f$
 *
 * @param unit Input.  Unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the input units to the SI unit.
 */
double unitToSiArea(const char *unit);
/** 
 * Converts between volume units.
 * 
 * @param srcUnit Input. Source unit string.
 * @param destUnit Input. Destination unit string.
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertVolume(const char *srcUnit, const char *destUnit);
/** 
 * Converts between distance units.
 * 
 * @param srcUnit Input. Source unit string
 * @param destUnit Input. Destination unit string
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertDistance(const char *srcUnit, const char *destUnit);
/** 
 * Converts between mass units.
 * 
 * @param srcUnit 
 * @param destUnit Input. Destination unit string
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertMass(const char *srcUnit, const char *destUnit);
/** 
 *  Converts between velocity units.
 * 
 * @param srcUnit Input. Source unit string.
 * @param destUnit Input. Destination unit string
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertVelocity(const char *srcUnit, const char *destUnit);

/** 
 * Converts between area units.
 * 
 * @param srcUnit Input. Source unit string.
 * @param destUnit Input. Destination unit string 
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertArea(const char *srcUnit, const char *destUnit);

/** 
 * Converts between temperature units.
 * 
 * @param srcUnit Input. Source unit string.
 * @param destUnit Input. Destination unit string 
 * 
 * @return It returns the conversion multiplication factor needed for
 * converting the source units to the destination units.
 */
double unitConvertTemperature(const char *srcUnit, const char *destUnit);

/** @} */
#endif
