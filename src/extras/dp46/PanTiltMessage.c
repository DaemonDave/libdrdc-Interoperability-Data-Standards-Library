/*
 * Description  : DP PanTilt Message Handling Routines 
 * Author       : Tie Peng
 * Purpose      : 
 * Revision     : $Id: PanTiltMessage.c,v 1.1 2008/12/02 20:45:48 cvsuser Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "PanTilt.h"

/**
 * converts from radians to a pan value in machine units
 * 
 * @param rad 
 * 
 * @return 
 */
long rad2pan(double rad) {
  return (long)(  ( (rad * 180.0 / M_PI) / (185.1428 / 3600.0) ) );
}
/**
 * converts from radians to a tilt value in machine units
 * 
 * @param rad 
 * 
 * @return 
 */
long rad2tilt(double rad) {
  return (long)(  ( (rad * 180.0 / M_PI) / (185.1428 / 3600.0) ) );
}
/**
 * converts from  a pan value in machine units to radians

 * 
 * @param pan 
 * 
 * @return 
 */
double pan2rad(long pan) {
  return ( (double)( pan ) * (185.1428 / 3600.0) ) / 180.0 * M_PI;
}
/**
 * converts from  a tilt value in machine units to radians
 * 
 * 
 * @param tilt 
 * 
 * @return 
 */
double tilt2rad(long tilt) {
  return ( (double) ( tilt ) * (185.1428 / 3600.0) ) / 180.0 * M_PI;
}
/** 
 * Add a charater to a string 
 * 
 * @param s 
 * @param c 
 * 
 * @return 
 */
int addChar(char * s, char c ) { 
  char buffer[2];
  sprintf(buffer,"%c",c);
  strcat(s, buffer);
  return 0;
}
/** 
 * Add a long integer to a string
 * 
 * @param s 
 * @param l 
 * 
 * @return 
 */
int addLong(char * s, long l) { 
  char buffer[80];
  sprintf(buffer,"%ld",l);
  strcat(s, buffer);
  return 0;
}
/** 
 * Return a long integer from a string at specified position
 * 
 * @param s 
 * @param offset 
 * 
 * @return 
 */
long getLong(char * s, int offset) {
  char buffer[40];
  long lvalue;
  int length = strlen(s);
  int i;

  for (i = offset; i< length; i++)
    buffer[i-offset]=s[i];

  buffer[length - offset]= '\0';
  lvalue = atol(buffer);
  return lvalue;
}

/* int handleInput (char *buff, char * message) { */
/*   char thisChar; */
/*   int buffPos = 0; */
/*   int state = WFSTAR; */

/*   strcpy(message, ""); */

/*   while (buffPos < strlen(buff)) { */
/*     thisChar = buff[ buffPos++ ]; */
/*     switch(state) { */
/*     case WFSTAR: */
/*       if (thisChar == '*') { */
/* 	state = WFDELIM; */
/*       } else if (thisChar == '!') { */
/* 	state = WFDELIM; */
/*       } else { */
/* 	//cerr << "ignoring :|" << thisChar << "|" << endl; */
/*       } */
/*       break; */

/*     case WFDELIM: */
/*       if (thisChar == '\n') { */
/* 	state = WFSTAR; */
/* 	//dispatchMessage(); */
/* 	//msg_->resetMessage(); */
/*       } else { */
/* 	addChar(message, thisChar ); */
/* 	//bconchar(message, thisChar); */
/*       } */
/*       break; */
/*     default: */
/*       //throw Miro::Exception("EventHandler::handle_input: unknown state in panTiltEvent."); */
/*       break; */
/*     } */
/*   } */
/*   //printf("Blabla: %s\n", bstr2cstr(message,'\n')); */
/*   //printf("Blabla: %s\n", message); */
/*   return 0; */
/* } */

/** 
 * Process a PanTilt message
 * 
 * @param message 
 * @param panTiltData 
 */
void handleMessage(char * message, PanTiltData_t *panTiltData) {
  int gotdata;
  int opcode = FIRSTOPCODE;
  char buffer[256];
  int length=0;

  if (strlen(message) == 0) {
    // special case, just a * <delim> packet
    // this happens after A(wait) commands
/*     log(INFO,"got empty packet, interpreted as ack"); */
/*     panTiltData.sync.release(); */
/*     panTiltData.syncCond.broadcast(); */
/*     incStatistics( true ); */
#ifdef DRDC_DEBUG
    printf("Write ACK received.\n");
#endif
    return;
  }
  
  while (opcode<=LASTOPCODE) {
    length = strlen(panTiltMessages[opcode]);
    if ( strlen(message) >= length ) {
      //substr(message, buffer, 0 , strlen(panTiltMessages[opcode]));
      memcpy(buffer, message, length);
      buffer[length]='\0';

      //printf("abc %d %s\n", strlen(message), message);
      //printf("abc %d %s\n", strlen(panTiltMessages[opcode]), panTiltMessages[opcode]);
      //printf("abc %d %s\n", strlen(buffer), buffer);

      if (  !strcmp(buffer, panTiltMessages[opcode]) ) {
	//printf("break opcode = %d\n", opcode);
	break;
      }
    }
    ++opcode;
  }

  //printf("opcode = %d\n", opcode);
  //printf("opcode = %s\n", bstr2cstr(panTiltMessages[opcode], '\n'));



  if (opcode > LASTOPCODE) {
/*     log(ERROR,"ignored unknown or corrupted message :"); */
/*     cerr << "|" << message.getMessage()  << "|"  << endl; */
/*     panTiltData.sync.release(); */
/*     incStatistics( false ); */

    return;
  }

//     cerr << "found match for |" << panTiltMessages[opcode] << "|" << endl;

    // be optimistic
    gotdata = 1;

    // now do something appro.
    switch (opcode) {
    case PANPOSITION: {
      panTiltData->panPosition = getLong(message, length);
    }
    break; 
    case TILTPOSITION: 
      panTiltData->tiltPosition = getLong(message, length);
      break;
    case TARGETPANPOSITION: 
      panTiltData->targetPanPosition = getLong(message, length);
      break;
    case TARGETTILTPOSITION: 
      panTiltData->targetTiltPosition = getLong(message, length);
      break; 
    case MINPANPOSITION: 
      panTiltData->minPanPosition = getLong(message, length);
      break; 
    case MAXPANPOSITION: 
      panTiltData->maxPanPosition = getLong(message, length);
      break; 
    case MINTILTPOSITION: 
      panTiltData->minTiltPosition = getLong(message, length);
      break; 
    case MAXTILTPOSITION: 
      panTiltData->maxTiltPosition = getLong(message, length);
      break; 
    case LIMITBOUNDSENABLED: 
      panTiltData->limitbounds = 1;
      break; 
    case LIMITBOUNDSDISABLED: 
      panTiltData->limitbounds = 0;
      break; 
    case TARGETPANSPEED: 
      panTiltData->targetPanSpeed = getLong(message, length);
      break; 
    case TARGETTILTSPEED: 
      panTiltData->targetTiltSpeed = getLong(message, length);
      break; 
    case PANACCELERATION: 
      panTiltData->panAcceleration = getLong(message, length);
      break; 
    case TILTACCELERATION: 
      panTiltData->tiltAcceleration = getLong(message, length);
      break; 
    case PANBASESPEED: 
      panTiltData->panBaseSpeed = getLong(message, length);
      break; 
    case TILTBASESPEED: 
      panTiltData->tiltBaseSpeed = getLong(message, length);
      break; 
    case MAXPANSPEED: 
      panTiltData->maxPanSpeed = getLong(message, length);
      break; 
    case MINPANSPEED: 
      panTiltData->minPanSpeed = getLong(message, length);
      break; 
    case MAXTILTSPEED: 
      panTiltData->maxTiltSpeed = getLong(message, length);
      break; 
    case MINTILTSPEED: 
      panTiltData->minTiltSpeed = getLong(message, length);
      break; 
    case ECHOINGON:
      panTiltData->echoing = 1;
      break; 
    case ECHOINGOFF: 
      panTiltData->echoing = 0;
      break; 
    case ASCIIVERBOSE: 
      panTiltData->verbose = 1;
      break; 
    case ASCIITERSE: 
      panTiltData->verbose = 0;
      break; 
    case SHOWVERSION: 
      break; 
    case PANHOLDLOW: 
      panTiltData->panHold = 1;
      break; 
    case PANHOLDREGULAR: 
      panTiltData->panHold = 2;
      break; 
    case PANHOLDOFF: 
      panTiltData->panHold = 0;
      break; 
    case TILTHOLDLOW: 
      panTiltData->tiltHold = 1;
      break; 
    case TILTHOLDREGULAR: 
      panTiltData->tiltHold = 2;
      break; 
    case TILTHOLDOFF: 
      panTiltData->tiltHold = 0;
      break; 
    case PANMOVELOW: 
      panTiltData->panMove = 0;
      break; 
    case PANMOVEREGULAR: 
      panTiltData->panMove = 1;
      break; 
    case PANMOVEHIGH: 
      panTiltData->panMove = 2;
      break; 
    case TILTMOVELOW: 
      panTiltData->tiltMove = 0;
      break; 
    case TILTMOVEREGULAR: 
      panTiltData->tiltMove = 1;
      break; 
    case TILTMOVEHIGH: 
      panTiltData->tiltMove = 2;
      break;
    default:
      gotdata = 0;
    }

    return;
}


