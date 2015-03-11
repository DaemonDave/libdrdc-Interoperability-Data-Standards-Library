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
 * Description  : libdrdc - $RCSfile: fsm.c,v $
 * Author       : dave
 * Purpose      : SI Units and conversions
 * Revision     : $Id: fsm.c,v 1.6 2008/11/19 22:06:55 cvsuser Exp $
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif



#ifndef FSM_H
#include "fsm.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#undef DEBUG
//#define DEBUG




/** 
 * Constructor CreateFSM
 *
 * This function allocates for a fsm_t type struct.
 *

 * 
 * @return It returns construct if successful. Otherwise, it returns error.
 */
fsm_t * CreateFSM()
{
	return (fsm_t *)malloc(sizeof(fsm_t));
}

/** 
 * Destructor CreateFSM
 *
 * This function destroys fsm_t type struct.
 *
 * @param void * in. input fsm_t pointer.
 * 
 * @return It returns construct if successful. Otherwise, it returns error.
 */
int	DestroyFSM(  fsm_t * in)
{
	free ((fsm_t *)in);
	
	return 0;
}


/** 
 * SetFSMState
 *
 * This function sets the state of the  FSM
 *
 * @param const int * st. integer state to place state machine into.
 * @param void * out fsm struct to manipulate
 *
 * @return It returns new state if successful. Otherwise, it returns -1 error.
 */
int SetFSMState( const int * st,  fsm_t * out)
{
	fsm_t * ptr;
	ptr = (fsm_t *)out;	

#ifdef DEBUG
	printf("[%u]", *st);
#endif
	if ( *st >= 0 && *st < ptr->num)
	{
		ptr->st = (unsigned int) *st;
		return (int) ptr->st;
	}
	else
	{
		return -1;
	}
}
/** 
 * GetFSMState
 *
 * This function returns the integer state fsm_t.
 *
 * @param void * out. input fsm_t pointer to manipulate
 * 
 * @return It returns value of state; Otherwise, it returns error.
 */
int GetFSMState(   fsm_t * out )
{
	fsm_t * ptr;
	ptr = (fsm_t*)out;	
	
	return (int) ptr->st;

}
//! Increase the type of the  FSM
int IncreaseFSMState(   fsm_t *out )
{
	fsm_t * ptr;
	ptr = (fsm_t*)out;	

	ptr->st++; 
	if ( ptr->st >=  ptr->num)
	{
		ptr->st = 0;
	}
	return (int) ptr->st;
}
//! Decrease the type of the  FSM
int DecreaseFSMState(   fsm_t *out )
{
	fsm_t * ptr;
	ptr = (fsm_t*)out;	

	ptr->st--;
	if ( ptr->st <  0)
	{
		ptr->st = ptr->num;
	}
	return (int) ptr->st;
}


/** initialize the FSM

	
*/
int InitFSM (  const size_t *num, const size_t type,  fsm_t * out  )
{
	fsm_t * ptr;
	
	ptr = (fsm_t*)out;
	
	// assign pointers
	ptr->create=CreateFSM;
	ptr->destroy=DestroyFSM;
	ptr->init=InitFSM;
	ptr->getstate=GetFSMState;
	ptr->setstate=SetFSMState;
	ptr->increase=IncreaseFSMState;
	ptr->decrease=DecreaseFSMState;
	ptr->transition=transition_rule;
	
	if(num > 0)
	{
		ptr->num = num;
	}
	else
	{
		ptr->num = 2; // default to 2 states
	}
	
	if(type > 0)
	{
		ptr->type = type;
	}
	else
	{
		ptr->type = 0;	
	}
	

	return 0;
}


/** Generic rule for adjusting state based on a single input */
static float transition_rule( const void * in ,  fsm_t * out  )
{
	int * val;
	fsm_t * ptr;
	ptr = (fsm_t*)out;
	
	val = (int * ) in;
	
	if (val > 10)
	{
		ptr->st = 10;
	}
	else
	{
		ptr->st++;
	}
	return (float)(ptr->st);	
}
//! Check Finite State Machine if it is in range from upper to lower, return 0 if yes; -1 if not
int CheckFSMRange (const int * lower, const int * upper,  fsm_t * out )
{
	int val;
	int val2;
	fsm_t * ptr;
	ptr = (fsm_t*)out;
	// boundary check for lower value and change lower value if needed
	if (*lower < 0 || *lower > ptr->num )
	{
		val = 0;
	}
	else
	{
		val = *lower;
	}
	// boundary check for upper value and change if needed
	if( *upper > ptr->num )
	{
		val2 = ptr->num;
	}
	else
	{
		val2 = *upper;
	}
	//boundary check and then success
	if (ptr->st >= *lower && ptr->st <= *upper )
	{
		return 0;
	}
	// or return fail as the value is beyond the range given
	return -1;	
}
//! SetFSMTransitionRule aims the struct pointer function to the given ptr address
int SetFSMTransitionRule(const void * ptr,  fsm_t * out )
{	
	out->transition=ptr;	
	return 0;
}


#ifdef __cplusplus
} /* matches extern "C" for C++ */
#endif

