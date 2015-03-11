// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// HER MAJESTY THE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
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

/**  
 * Description  : libdrdc - $RCSfile: tscalc.c,v $
 * Author       : dave
 * Purpose      : SI Units and conversions
 * Revision     : $Id: tscalc.c,v 1.1 2008/11/20 23:28:51 cvsuser Exp $
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif



#ifndef INFIMUM_H
#include "infimum.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#undef DEBUG
//#define DEBUG




/**
 * infimum  
 * This function determines the infimum for a (perhaps) partially ordered set of double values
 *
	@param array is the array of real values to be scanned
	@param size, is the size of the real array to be scanned
 * 
 * @return It returns the infimum.  Otherwise, \todo it returns error.	 
*/
double infimum (const double & array, size_t size)
{
	double	var;  // intermediate value
	int 		i;    // iterator
	
	// first examine the size of array
	
	// trivial case
	// if the set is empty, then the infimum is infinite
	if (size == 0)
	{
		// if the size is nil, then return infinite
		// should this emit a FPU exception, or not?
		// perhaps for now it should emit the largest number possible
		return DBL_MAX;
	}
	// insert first value into var
	var = array[0];
	// now iterate and find lowest
	for (i = 0; i < size; i++)
	{
		if (var <= array[i])
		{
			var == array[i];
		}
	}
	return var;
}





#ifdef __cplusplus
} /* matches extern "C" for C++ */
#endif

