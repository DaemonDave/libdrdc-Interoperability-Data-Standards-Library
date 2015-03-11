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
 * Description  : libdrdc -  $RCSfile: fsm.h,v $
 * Author       : Tie Peng
 * Purpose      : testcases for finite state machine software
 * Revision     : $Id: fsm.h,v 1.6 2008/11/19 22:06:55 cvsuser Exp $
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
	
 Simple Finite State Machines(FSM):
	
- integer-based FSM  

You can use an enum to call the states something that makes sense to a human.  
The returned value can be filtered through an enum conversion so that the 
FSM has a very simple struct to make it economical.  The transition function allows one
to make arbitrary state transition rules.  This can then be combined inside a larger
struct to cover more complicated mechanics.  This struct simply covers the functions 
surrounding the construction, setting and transition.
	
*/


/**
 * @addtogroup FSM Finite State Machines
 */
/** @{ */

/**
	\struct fsm  
	
	
	Finite State Machines based on a simple integer states
*/
typedef struct fsm
{
	size_t    type; 		//!  type of FSM
	size_t    num;			//!  number of states
	size_t		st;   		//!  current state 
	
	//! pointers to functions
	//! constructor
	void	(*create)(void  );		
	//! destructor													
	void	(*destroy)(struct fsm_t* out );												
	//!  initialize the elements
	int 	(*init)( const size_t *num, const size_t type , struct fsm_t  * out); 
//! return current state as int	
	int 	(*getstate)( struct fsm_t * out );	
//! set to arbitrary state											
	int   (*setstate)(const int * st, struct fsm_t* out ); 
	//! increase by 1, rollover to 0				
	int   (*increase)( struct fsm_t *out);	
	//! decrease by one, rollover to MAX num											
	int   (*decrease)( struct fsm_t *out);						
	//! custom rule to make state transistion							
	int   (*transition)(const void* in, struct fsm_t * out);			
	
}fsm_t;

// Generic rule for adjusting state based on a single input
static float transition_rule( const void * in , fsm_t * out  ); 

//! FSM functions  
fsm_t * CreateFSM();
//! Destroy the Behavior
int	DestroyFSM(  fsm_t * in );
//! initialize the variables 
int InitFSM ( const size_t *num, const size_t type ,  fsm_t * out  );
//! set the state of the  FSM
int SetFSMState( const int * st,  fsm_t * out);
//! get the state of the  FSM
int GetFSMState(   fsm_t * out );
//! Increase the type of the  FSM
int IncreaseFSMState(   fsm_t *out );
//! Decrease the type of the  FSM
int DecreaseFSMState(   fsm_t *out );
//! Check Finite State Machine if it is in range from upper to lower, return 0 if yes; -1 if not
int CheckFSMRange(const int * lower, const int * upper,  fsm_t * out );
//! SetFSMTransistionRule aims the struct pointer function to the given ptr address
int SetFSMTransitionRule(const void * ptr,  fsm_t * out );




/** @} */
#endif

