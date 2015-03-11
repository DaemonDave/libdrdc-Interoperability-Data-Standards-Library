/**	\file $RCSFile$
testcases for finite state machine software 
*/
/* librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

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
/*
 * Description  : libdrdc -  $RCSfile: tscalc.h,v $
 * Author       : Tie Peng
 * Purpose      : testcases for finite state machine software
 * Revision     : $Id: tscalc.h,v 1.1 2008/11/20 23:28:51 cvsuser Exp $
 */

#ifndef FSM_H
#define FSM_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>
#include <stdlib.h>

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif


/*!
	\brief
	
 Timescale Calculus Functions
 
 
	
*/


/**
 * @addtogroup Timescale 
 */
/** @{ */

/**
 * infimum  *
 This function determines the infimum for a (perhaps) partially ordered set of double values
 
 The infimum or greatest lower bound of a subset S is the value that is less than or equal 
 to every number in S.  
 
 Let \f$ A\f$ be a set with a partial order \f$ \leq\f$, 
 and let \f$ S \subseteq A\f$. For any \f$ x \in A\f$, \f$ x\f$ is a lower bound of 
 \f$ S\f$ if \f$ x \leq y\f$ for any \f$ y \in S\f$. The infimum of \f$ S\f$, 
 denoted \f$\inf(S)\f$, is the greatest such lower bound; that is, if \f$ b\f$ 
 is a lower bound of \f$ S\f$, then \f$ b \leq \inf(S)\f$.

Note that it is not necessarily the case that \f$ \inf(S) \in S\f$. 
Suppose \f$ S = (0, 1)\f$; then \f$ \inf(S) = 0\f$, but \f$ 0 \not \in S\f$.
 
 \sa Planet Math page on infimum http://planetmath.org/?op=getobj&from=objects&id=3607
 \sa Time-Scale Calculus by Martin Bohner and Allan Peterson
 
 
	@param array is the array of real values to be scanned
	@param size  is the size of the real array  to be scanned
  
 	@return returns the infimum.  Otherwise, \todo it returns error.	 
*/
double infimum (const double & array, size_t size);

/**
 * fwdjump  *
 This function determines the forward jump operator for a (perhaps) partially ordered set of double values
 
 The infimum or greatest lower bound of a subset S is the value that is less than or equal 
 to every number in S.  
 
 Let \f$ A\f$ be a set with a partial order \f$ \leq\f$, 
 and let \f$ S \subseteq A\f$. For any \f$ x \in A\f$, \f$ x\f$ is a lower bound of 
 \f$ S\f$ if \f$ x \leq y\f$ for any \f$ y \in S\f$. The infimum of \f$ S\f$, 
 denoted \f$\inf(S)\f$, is the greatest such lower bound; that is, if \f$ b\f$ 
 is a lower bound of \f$ S\f$, then \f$ b \leq \inf(S)\f$.

Note that it is not necessarily the case that \f$ \inf(S) \in S\f$. 
Suppose \f$ S = (0, 1)\f$; then \f$ \inf(S) = 0\f$, but \f$ 0 \not \in S\f$.
 
 \sa Planet Math page on infimum http://planetmath.org/?op=getobj&from=objects&id=3607
 \sa Martin Bohner & Allan Peterson (2001). Dynamic Equations on Time Scales. Birkhäuser. http://en.wikipedia.org/wiki/Special:BookSources/9780817642259
 
 
	@param array is the array of real values to be scanned
	@param size  is the size of the real array  to be scanned
  
 	@return returns the infimum.  Otherwise, \todo it returns error.	 
*/

/** @} */
#endif

