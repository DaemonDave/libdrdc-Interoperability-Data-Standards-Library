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
 * Revision     : $Id: unit_conv.c,v 1.4 2008/09/29 14:13:14 cvsuser Exp $
 */





/** \todo make the opposite conversion functions : I propose to just make a second function for all units of measure types, called unitFromSi___
that simply returns the inverse of the unit. That solves the two basic cases, later on we could add inter-unit conversions

\todo document this code better, for future readers. I started with one so I understood Tie's code.

DRE 2008

*/

#ifndef UNIT_CONV_H
#include "unit_conv.h"
#endif


double unitToSiVolume(const char *unit) 
{
  unsigned int i;

  for(i = 0; i < VOLUME_UNITS_NUM; i++) {
    if (!strcmp(unit, VOLUME_UNITS[i].unit)) {
      return VOLUME_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}


double unitConvertVolume(const char *srcUnit, const char *destUnit) {
  double srcFactor, destFactor;

  if (!strcmp(srcUnit, destUnit)) {
    return 1.0f;
  } else if (!strcmp(destUnit, VOLUME_UNITS[0].unit)) {
    return unitToSiVolume(srcUnit);
  } else {
    srcFactor  = unitToSiVolume(srcUnit);
    destFactor = unitToSiVolume(destUnit);
    return srcFactor / destFactor;
  }
}



double unitToSiDistance(const char *unit) {
  unsigned int i;
  for(i = 0; i < DISTANCE_UNITS_NUM; i++) {
    if (!strcmp(unit, DISTANCE_UNITS[i].unit)) {
      return DISTANCE_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}


double unitConvertDistance(const char *srcUnit, const char *destUnit) {
  double srcFactor, destFactor;

  if (!strcmp(srcUnit, destUnit)) {
    return 1.0f;
  } else if (!strcmp(destUnit, DISTANCE_UNITS[0].unit)) {
    return unitToSiDistance(srcUnit);
  } else {
    srcFactor  = unitToSiDistance(srcUnit);
    destFactor = unitToSiDistance(destUnit);
    return srcFactor / destFactor;
  }
}

// This function iterates through 
// units of mass and returns the conversion
// factor that will convert the mass to SI units
// if the factor doesn't exist then throw an exception
// dre 2008 from ac839 frankfurt to calgary 
double unitToSiMass(const char *unit) 
{
  unsigned int i;// iterator
  for(i = 0; i < MASS_UNITS_NUM; i++)
	 {
	   // check units comparison
    if (!strcmp(unit, MASS_UNITS[i].unit)) 
		{
		  // return factor
      return MASS_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}
// same function as unitToSiMass only returns the inverse value for conversion
// from SI units to the other unit
double unitFromSiMass(const char *unit) 
{
  unsigned int i;// iterator
  for(i = 0; i < MASS_UNITS_NUM; i++)
	 {
	   // check units comparison
    if (!strcmp(unit, MASS_UNITS[i].unit)) 
		{
		  // return factor
      return (1.0/MASS_UNITS[i].factor);
    }
  }
  Throw UNRECOGNIZED_UNIT;
}


double unitConvertMass(const char *srcUnit, const char *destUnit) {
  double srcFactor, destFactor;

  if (!strcmp(srcUnit, destUnit)) {
    return 1.0f;
  } else if (!strcmp(destUnit, MASS_UNITS[0].unit)) {
    return  unitToSiMass(srcUnit);
  } else {
    srcFactor  = unitToSiMass(srcUnit);
    destFactor = unitToSiMass(destUnit);
    return srcFactor / destFactor;
  }
}


double unitToSiVelocity(const char *unit) {
  unsigned int i;
  for(i = 0; i < VELOCITY_UNITS_NUM; i++) {
    if (!strcmp(unit, VELOCITY_UNITS[i].unit)) {
      return VELOCITY_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}


double unitConvertVelocity(const char *srcUnit, const char *destUnit) {
  double srcFactor, destFactor;

  if (!strcmp(srcUnit, destUnit)) {
    return 1.0f;
  } else if (!strcmp(destUnit, VELOCITY_UNITS[0].unit)) {
    return unitToSiVelocity(srcUnit);
  } else {
    srcFactor  = unitToSiVelocity(srcUnit);
    destFactor = unitToSiVelocity(destUnit);
    return srcFactor / destFactor;
  }
}



double unitToSiArea(const char *unit) {
  unsigned int i;
  for(i = 0; i < AREA_UNITS_NUM; i++) {
    if (!strcmp(unit, AREA_UNITS[i].unit)) {
      return AREA_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}


double unitConvertArea(const char *srcUnit, const char *destUnit) 
{
  double srcFactor, destFactor;

  if (!strcmp(srcUnit, destUnit)) {
    return 1.0f;
  } else if (!strcmp(destUnit, AREA_UNITS[0].unit)) {
    return unitToSiArea(srcUnit);
  } else {
    srcFactor  = unitToSiArea(srcUnit);
    destFactor = unitToSiArea(destUnit);
    return srcFactor / destFactor;
  }
}

double unitToSiTemperature(const char *unit)
{
  unsigned int i;
  for(i = 0; i < TEMPERATURE_UNITS_NUM; i++) 
	{
    if (!strcmp(unit, TEMPERATURE_UNITS[i].unit)) 
		{
      return TEMPERATURE_UNITS[i].factor;
    }
  }
  Throw UNRECOGNIZED_UNIT;
}

double unitConvertTemperature(const char *srcUnit, const char *destUnit)
{
  double srcFactor, destFactor;

	// if same units, return unitary factor
  if (!strcmp(srcUnit, destUnit)) 
	{
    return 1.0f;
  } 
	else if (!strcmp(destUnit, TEMPERATURE_UNITS[0].unit)) 
	{
    return unitToSiArea(srcUnit);
  }
	else 
	{
    srcFactor  = unitToSiTemperature(srcUnit);
    destFactor = unitToSiArea(destUnit);
    return srcFactor / destFactor;
  }
	
}
