/*
 * Description  : DP PanTilt Driver Header File 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: PanTilt.h,v 1.1 2008/12/02 20:45:48 cvsuser Exp $
 */

#ifndef PANTILT_H
#define PANTILT_H


#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <time.h> 
#include "termios.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

//#define M_PI 3.1415926

#define BUFFSIZE 256

enum { PANPOSITION, TILTPOSITION,
       TARGETPANPOSITION, TARGETTILTPOSITION,
       MINPANPOSITION, MAXPANPOSITION,
       MINTILTPOSITION, MAXTILTPOSITION,
       LIMITBOUNDSENABLED, LIMITBOUNDSDISABLED,
       TARGETPANSPEED, TARGETTILTSPEED,
       PANACCELERATION, TILTACCELERATION,
       PANBASESPEED, TILTBASESPEED,
       MAXPANSPEED, MINPANSPEED,
       MAXTILTSPEED, MINTILTSPEED,
       ECHOINGON, ECHOINGOFF, ASCIIVERBOSE, ASCIITERSE,
       SHOWVERSION,
       PANHOLDLOW, PANHOLDREGULAR, PANHOLDOFF,
       TILTHOLDLOW, TILTHOLDREGULAR, TILTHOLDOFF,
       PANMOVELOW, PANMOVEREGULAR, PANMOVEHIGH,
       TILTMOVELOW, TILTMOVEREGULAR, TILTMOVEHIGH, 
};

enum { WFSTAR, WFDELIM };

#define FIRSTOPCODE PANPOSITION
#define LASTOPCODE TILTMOVEHIGH

#define SERIAL_EOM_CNT 0x0001
#define BAUDRATE B9600


/**
 * strings in an array
 */
static char * panTiltMessages[] = { 
  " Current Pan position is ", " Current Tilt position is ",  
  " Target Pan position is ", " Target Tilt position is ",
  " Minimum Pan position is ", " Maximum Pan position is ",
  " Minimum Tilt position is ", " Maximum Tilt position is ",
  " Limit bounds are ENABLED (soft limits enabled)", " Limit bounds are DISABLED (hard limits only: use care)",
  " Target Pan speed is ", " Target Tilt speed is ",
  " Pan acceleration is ", " Tilt acceleration is ",
  " Base Pan speed is ", " Base Tilt speed is ",
  " Maximum Pan speed is ", " Minimum Pan speed is ",
  " Maximum Tilt speed is ", " Minimum Tilt speed is ",
  " Echoing ON", " Echoing OFF",
  " ASCII verbose mode", " ASCII terse mode",
  " Pan-Tilt Controller v1.09.0b, (C)1996 Directed Perception, Inc., All Rights Reserved",
  " Pan in LOW hold power mode", " Pan in REGULAR hold power mode", " Pan in OFF hold power mode",
  " Tilt in LOW hold power mode", " Tilt in REGULAR hold power mode", " Tilt in OFF hold power mode",
  " Pan in LOW move power mode", " Pan in REGULAR move power mode", " Pan in HIGH move power mode",
  " Tilt in LOW move power mode", " Tilt in REGULAR move power mode", " Tilt in HIGH move power mode"
};

typedef struct PanTiltData {
    int  failed;
    long panPosition;
    long tiltPosition;
    long targetPanPosition;
    long targetTiltPosition;
    long minPanPosition;
    long maxPanPosition;
    long minTiltPosition;
    long maxTiltPosition;
    int  limitbounds;
    long targetPanSpeed;
    long targetTiltSpeed;
    long panAcceleration;
    long tiltAcceleration;
    long panBaseSpeed;
    long tiltBaseSpeed;
    long maxPanSpeed;
    long minPanSpeed;
    long maxTiltSpeed;
    long minTiltSpeed;       
    int  echoing;
    int  verbose;       
    int  panHold;       
    int  tiltHold;       
    int  panMove;       
    int  tiltMove;
} PanTiltData_t;

typedef enum {
  serialSuccess=0,serialTimeout,serialOverflow,serialError
} serialStatus;


typedef struct {
  char               serialDeviceName[40];
  int                fd;
  unsigned long      nRead;
  unsigned long      nWritten;
  struct termios     termios;
  double             readTimeout;
  double             writeTimeout;
  int                signalNumber;
  timer_t            timer;
  volatile int       timeoutFlag;
  char               message[BUFFSIZE];
} TTYController_t;


typedef struct {
  TTYController_t    *tty;
  PanTiltData_t      *panTiltData;
} PanTiltID_t;


/* typedef struct { */
/*   timer_t            timer; */
/*   volatile int       timeoutFlag; */
/* } SerialTimer_t; */


extern double pan2rad(long pan);
 
extern double tilt2rad(long tilt);

extern long rad2pan(double rad);

extern long rad2tilt(double rad);

extern int addChar(char * s, char c);

extern int addLong(char * s, long l);

extern long getLong(char * s, int offset);

extern void handleMessage(char * message, PanTiltData_t *panTiltData);

extern serialStatus readRaw(TTYController_t *tty, char *data, size_t maxchars, size_t *nbytesTransfered,int *gotEom);

extern serialStatus writeRaw(TTYController_t *tty, const char *data, size_t numchars,size_t *nbytesTransfered);
extern serialStatus closeConnection(TTYController_t *tty);
extern serialStatus termiosInit(TTYController_t *tty);

extern serialStatus connectIt(TTYController_t *tty);

extern int serialTimerCreate(timer_t *timerid, TTYController_t *tty);
extern int serialTimerSet(timer_t *timerid, double delay);
extern int serialTimerCancel(timer_t *timerid);
extern int serialTimerDelete(timer_t *timerid);

extern void serialSignalHandler(int sig,  siginfo_t  *sigInfo, void *context);

extern serialStatus panTiltCMD(PanTiltID_t *panTiltID, char * cmd);

extern int getPan(PanTiltID_t *PanTiltID, double *panValue);
extern int getTilt(PanTiltID_t *PanTiltID, double *tiltValue);
extern int setPan(PanTiltID_t *PanTiltID, double panValue);
extern int setTilt(PanTiltID_t *PanTiltID, double tiltValue);

PanTiltID_t * createPanTilt(char *serialName,double readTimeout, double writeTimeout, int signalNumber);
int destroyPanTilt(PanTiltID_t *panTiltID);

typedef struct {
    //! Target pan speed value in rad/s.
    double     targetpanspeed;
    //! Target tilt speed value in rad/s.
    double     targettiltspeed;
    //! Base pan speed value in rad/s.
    double     panbasespeed;
    //! Minimum pan speed value in rad/s.
    double     panminspeed;
    //! Maximum pan speed value in rad/s.
    double     panmaxspeed;
    //! Base tilt speed value in rad/s.
    double     tiltbasespeed;
    //! Minimum tilt speed value in rad/s.
    double     tiltminspeed;
    //! Maximum tilt speed value in rad/s.
    double     tiltmaxspeed;
    //! Pan acc value in rad/s^2.
    double     panacc;
    //! Tilt acc value in rad/s^2.
    double     tiltacc;
} PanTiltSpdAccIDL_t;


//! Struct representing a pantilt position.
typedef struct {
    //! Pan value in rad.
    double     panvalue;
    //! Tilt value in rad.
    double     tiltvalue;
} PanTiltPositionIDL_t;


//! Struct representing a pantilt limits  configuration.
typedef struct {
  //! Minimal pan position.
  double minpanposition;
  //! Maximal pan position.
  double maxpanposition;
  //! Minimal tilt position.
  double mintiltposition;
  //! Maximal tilt position.
  double maxtiltposition;
} PanTiltLimitsIDL_t;

//! Struct representing a pantilt hold and move power configuration.
typedef struct {
  //! Hold power pan.
  /**
   * Possible values are 0, 1, 2, corresponding to
   * off, low, regular.
   */
  long panhold;
  
  //! Hold power tilt.
  /**
   * Possible values are 0, 1, 2, corresponding to
   * off, low, regular.
   */
  long tilthold;
  
  //! Move power pan.
  /**
   * Possible values are 0, 1, 2, corresponding to
   * off, low, regular.
   */
  long panmove;
  
  //! Move power.
  /**
   * Possible values are 0, 1, 2, corresponding to
   * off, low, regular.
   */
  long tiltmove;

}  PanTiltPowersIDL_t;

int setPosition(PanTiltID_t *panTiltID, const PanTiltPositionIDL_t *dest);

int getPosition(PanTiltID_t *panTiltID, PanTiltPositionIDL_t *result);

int setWaitPosition(PanTiltID_t *panTiltID, const PanTiltPositionIDL_t *dest);

int getSpdAcc(PanTiltID_t *panTiltID,  PanTiltSpdAccIDL_t *result);

int setSpdAcc(PanTiltID_t *panTiltID, const PanTiltSpdAccIDL_t *dest );

int getLimits(PanTiltID_t *panTiltID, PanTiltLimitsIDL_t *result);

int setPowers(PanTiltID_t *panTiltID, PanTiltPowersIDL_t *dest);

int getPowers(PanTiltID_t *panTiltID, PanTiltPowersIDL_t *result);

#define DRDC_DEBUG
//#define SIG_INFO_WORKAROUND


#ifdef SIG_INFO_WORKAROUND
static int globalTimeoutFlag = 0;
#endif

#endif
