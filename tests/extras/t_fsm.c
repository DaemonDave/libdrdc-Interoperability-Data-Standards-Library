/**	\file $Id: t_fsm.c,v 1.5 2008/11/19 22:06:55 cvsuser Exp $
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
 * Description  : libdrdc -  $RCSfile: t_fsm.c,v $
 * Author       : dave
 * Purpose      : testcases for finite state machine software
 * Revision     : $Id: t_fsm.c,v 1.5 2008/11/19 22:06:55 cvsuser Exp $
 */

/**
	\brief 	test cases for cpp wrapped functions
	
		  
	\todo $RCSfile: t_fsm.c,v $ add a complete suite of test operations to verify operation.
	
*/


#ifndef FSM_H
#include "fsm.h"
#endif

#include <unistd.h>


//#undef DEBUG
#define DEBUG

#define NUM   20


//local functions
/** Generic rule for adjusting state based on a single input */
static float new_transition( const void * in ,  fsm_t * out  )
{
	int * val;
	fsm_t * ptr;
	ptr = (fsm_t*)out;
	
	val = (int * ) in;
	

	ptr->st = 66;

	return (float)(ptr->st);	
}



int main(void) 
{
	fsm_t * testp;
	int i;
  int  state = NUM -1;
	
	int upper = 40;
	
	int lower = 5;

	testp = CreateFSM();
	// test raw initialize
	InitFSM(  (const size_t *)NUM, (const size_t) 1 , testp  );
#ifdef DEBUG
	printf("FSM states: %d \n", testp->num);
#endif
	// test initialize pointer fcn	
	testp->init(  (const size_t *)30, (const size_t) 1 , testp  );
#ifdef DEBUG	
	printf("FSM states: %d \n", testp->num);
#endif
	// get FSM state
	if (GetFSMState(  testp )  == 0 )
	{
		printf("FSM state: %d OK  GetFSMState\n", testp->st);	
	}
	else
	{
		printf("FSM states: %d FAIL\n",GetFSMState(  testp ));	
		return -1;
	}	
	// increase state
	testp->increase(  testp  );	
	if (GetFSMState(  testp )  == 1 )
	{
		printf("FSM state: %d OK  increase \n", testp->st);	
	}
	else
	{
		printf("FSM state: %d FAIL\n", testp->st);		
		return -1;
	}
	// decrease state
	testp->decrease( testp );	
	if (GetFSMState( testp )  == 0 )
	{
		printf("FSM state: %d OK  decrease \n", testp->st);	
	}
	else
	{
		printf("FSM state: %d FAIL\n", testp->st);		
		return -1;
	}	
 	// test setstate to arbitrary
	testp->setstate( (const int *) & state, testp );
	if (GetFSMState(  testp )  == (unsigned int) NUM-1 )
	{
		printf("FSM state: %d OK  setstate\n", testp->st);	
	}
	else
	{
		printf("FSM state: %u FAIL setstate  %d\n", testp->st, state);		
		return -1;
	}
			
	for ( i = NUM-1; i >= 1; i--)
	{
	 testp->decrease( testp );
	 printf("\r*FSM state: %2d", testp->st);
	 usleep(50000);	 
	 fflush(stdout);
	}
	if (GetFSMState(  testp )  == 0 )
	{
		printf("FSM state: %d OK  iterate decrease\n", testp->st);	
	}
	else
	{
		printf("FSM state: %d FAIL iterate decrease\n", testp->st);		
		return -1;
	}	
	for ( i = 0 ; i <= NUM-1; i++)
	{
	 testp->increase( testp );
	 printf("\r*FSM state: %2d", testp->st);
	 usleep(50000);
	 fflush(stdout);	 
	}	
	if (GetFSMState(  testp )  == NUM )
	{
		printf("FSM state: %d OK  iterate increase\n", testp->st);	
	}
	else
	{
		printf("FSM state: %d FAIL iterate increase\n", testp->st);		
		return -1;
	}		
	// test arbitrary state transition
	testp->setstate( (const int *) & state, testp );
	// now transition
	testp->transition( (const void*) &state, testp );	
	if (GetFSMState(  testp )  == 10 )
	{
		printf("FSM state: %d OK  transition\n", testp->st);	
	}
	else
	{
		printf("FSM state: %d FAIL  transition\n", testp->st);		
		return -1;
	}			
	// test that it falls within range	- it should because it is at 10 and the limits are 5 and 40
	// the 40 should change to FSM state max of 30
	if ( CheckFSMRange( &lower, &upper, testp ))
	{
		printf("FSM state: %d FAIL  CheckFSMRange\n", testp->st);	
		return -1;		
	}
	else
	{
		printf("FSM state: %d OK  CheckFSMRange\n", testp->st);		
	}
	//!  Set the new transition rule
	SetFSMTransitionRule(new_transition,  testp );	
	//! Use the transition which will change to 66 
	testp->transition( (const void*) &state, testp );
	// confirm or fail and exit
	if ( GetFSMState(  testp )  == 66 )
	{
		printf("FSM state: %d OK  SetFSMTransistionRule\n", testp->st);
		return 0;		
	}
	else
	{
		printf("FSM state: %d FAIL  SetFSMTransistionRule\n", testp->st);			
		return -1;				
	}	
	
 
  return 0;
}
