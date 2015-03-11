/*
 * Description  : DP PanTilt Driver Implementation 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: PanTiltImp.c,v 1.1 2008/12/02 20:45:48 cvsuser Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <time.h> 
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "PanTilt.h"

/**
 * @mainpage DP PanTilt RTEMS/Linux Driver
 *
 * The DirectPerception(DP) PanTilt Unit (PTU) RTEMS/Linux Driver was ported from Miro(Miro-031106) C++ source code. The driver was tested under Cygwin, Fedora Linux 6 and RTEMS 4.7.1.
 * 
 */



/**
 * @addtogroup serial Serial Operation Routines
 */
/** @{ */


/**
 * Read raw data from serial port
 *
 * Read a message from the device. *nbytesTransfered is the number of
 * 8 bit bytes read from the device. readRaw will return as soon as it has
 * input. Thus the caller may receive partial messages.
 *
 * @param tty
 * @param data
 * @param maxchars
 * @param nbytesTransfered
 * @param gotEom
 *
 * @return 
 */
serialStatus readRaw(TTYController_t *tty, char *data, size_t maxchars, size_t *nbytesTransfered, int *gotEom) {
  int thisRead;
  int nRead = 0;
  int timerStarted = 0;
  serialStatus status = serialSuccess;

  assert(tty);

  if (tty->fd < 0) {
    return serialError;
  }

  if (maxchars <= 0) {
    return serialError;
  }

#ifdef SIG_INFO_WORKAROUND
  globalTimeoutFlag = 0;
#else
  tty->timeoutFlag = 0;
#endif

  if (gotEom) *gotEom = 0;


  for (;;) {


    if (!timerStarted && (tty->readTimeout > 0)) {
      serialTimerSet(&tty->timer, tty->readTimeout);
      timerStarted = 1;
    }
    thisRead = read(tty->fd, data, maxchars);

    if (thisRead > 0) {
      nRead = thisRead;
      tty->nRead += thisRead;
      break;
    } else {
      if ((thisRead < 0) && (errno != EWOULDBLOCK)
	  && (errno != EINTR)
	  && (errno != EAGAIN)) {

	closeConnection(tty);
	status = serialError;
	break;
      }
      if (tty->readTimeout == 0)
#ifdef SIG_INFO_WORKAROUND
	globalTimeoutFlag = 1;
#else
	tty->timeoutFlag = 1;
#endif
    }

#ifdef SIG_INFO_WORKAROUND
    if (globalTimeoutFlag)
#else
    if (tty->timeoutFlag)
#endif
      break;

  } // for
  if (timerStarted) serialTimerCancel(&tty->timer);

#ifdef SIG_INFO_WORKAROUND
  if (globalTimeoutFlag && (status == serialSuccess))
#else
  if (tty->timeoutFlag && (status == serialSuccess))
#endif
    status = serialTimeout;
  *nbytesTransfered = nRead;

  /* If there is room add a null byte */
  if (nRead < maxchars)
    data[nRead] = 0;
  else if (gotEom)
    *gotEom = SERIAL_EOM_CNT;

  return status;
}


/** 
 * Write to a serial port
 *
 * Send a message to the device. *nbytesTransfered is the number of
 *  8.bit bytes sent to the device. 
 *
 * @param tty 
 * @param data 
 * @param numchars 
 * @param nbytesTransfered 
 * 
 * @return 
 */
serialStatus writeRaw(TTYController_t *tty, const char *data, size_t numchars,size_t *nbytesTransfered) {
  int thisWrite;
  int nleft = numchars;
  int timerStarted = 0;
  serialStatus status = serialSuccess;

  assert(tty);

  if (tty->fd < 0) {
    return serialError;
  }
  if (numchars == 0) {
    *nbytesTransfered = 0;
    return serialSuccess;
  }

#ifdef SIG_INFO_WORKAROUND
  globalTimeoutFlag = 0;
#else
  tty->timeoutFlag = 0;
#endif

  nleft = numchars;

  if (tty->writeTimeout > 0) {
      serialTimerSet(&tty->timer, tty->writeTimeout);
      timerStarted = 1;
  }

  for (;;) {
    thisWrite = write(tty->fd, (char *)data, nleft);
    if (thisWrite > 0) {
      tty->nWritten += thisWrite;
      nleft -= thisWrite;
      if (nleft == 0)
	break;
      data += thisWrite;
    }
#ifdef SIG_INFO_WORKAROUND
    if (globalTimeoutFlag || (tty->writeTimeout == 0)) {
#else
    if (tty->timeoutFlag || (tty->writeTimeout == 0)) {
#endif
      status = serialTimeout;
      break;
    }
    if ((thisWrite < 0) && (errno != EWOULDBLOCK)
	&& (errno != EINTR)
	&& (errno != EAGAIN)) {

      closeConnection(tty);
      status = serialError;
      break;
    }
  }

  if (timerStarted) serialTimerCancel(&tty->timer);
  *nbytesTransfered = numchars - nleft;

  return status;
}



/** 
 * Connect a serial port
 * 
 * @param tty 
 * 
 * @return 
 */
serialStatus connectIt(TTYController_t *tty) {
  serialStatus status;

  /*
   * Sanity check
   */
  assert(tty);

  if (tty->fd >= 0) {
    return serialError;
  }

  if ((tty->fd = open(tty->serialDeviceName, O_RDWR | O_NOCTTY | O_NONBLOCK , 0)) < 0) {
    return serialError;
  }

  status = termiosInit(tty);
  if(status!=serialSuccess) {
    close(tty->fd);
    tty->fd = -1;
    return serialError;
  }

  return serialSuccess;
}

/** 
 * Close a serial port
 * 
 * @param tty 
 * 
 * @return 
 */
serialStatus closeConnection(TTYController_t *tty) {
  assert(tty);

  if (tty->fd >= 0) {
    close(tty->fd);
    tty->fd = -1;
  }

  return serialSuccess;
}

/** 
 * Initialize a termios device
 * 
 * @param tty 
 * 
 * @return 
 */
serialStatus termiosInit(TTYController_t *tty) {

  if(tcgetattr(tty->fd,&tty->termios) < 0 ) {
    return serialError;
  }
  
  if (cfsetispeed(&tty->termios, BAUDRATE) < 0) {
    return serialError;
  }
  if (cfsetospeed(&tty->termios, BAUDRATE) < 0) {
    return serialError;
  }

/*   tty->termios.c_cflag |=  (CLOCAL | CREAD);  */
/*   tty->termios.c_iflag = IGNBRK | IGNPAR; */
/*   tty->termios.c_oflag &= ~OPOST; */
/*   tty->termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); */
/*   tty->termios.c_cc[VMIN] = 2; */
/*   tty->termios.c_cc[VTIME] = 5; */


  tty->termios.c_cflag |= CS8 | CLOCAL | CREAD;
  tty->termios.c_cflag &= ~(PARENB | CRTSCTS);
  tty->termios.c_iflag = IGNPAR | ICRNL;
  tty->termios.c_iflag = 0;
  tty->termios.c_oflag = 0;
  tty->termios.c_lflag = 0;
  tty->termios.c_oflag = (ONLCR);

  tty->termios.c_cc[VINTR] = 0;	/* Ctrl-c */
  tty->termios.c_cc[VQUIT] = 0;	/* Ctrl-\ */
  tty->termios.c_cc[VERASE] = 0;	/* del */
  tty->termios.c_cc[VKILL] = 0;	/* @ */
  tty->termios.c_cc[VEOF] = 4;	/* Ctrl-d */
  tty->termios.c_cc[VTIME] = 10;	/* inter-character timer unused */
  tty->termios.c_cc[VMIN] = 0;	/* blocking read until 1 character arrives */
  tty->termios.c_cc[VSTART] = 0;	/* Ctrl-q */
  tty->termios.c_cc[VSTOP] = 0;	/* Ctrl-s */
  tty->termios.c_cc[VSUSP] = 0;	/* Ctrl-z */
  tty->termios.c_cc[VEOL] = 0;	/* '\0' */
  tty->termios.c_cc[VREPRINT] = 0;	/* Ctrl-r */
  tty->termios.c_cc[VDISCARD] = 0;	/* Ctrl-u */
  tty->termios.c_cc[VWERASE] = 0;	/* Ctrl-w */
  tty->termios.c_cc[VLNEXT] = 0;	/* Ctrl-v */
  tty->termios.c_cc[VEOL2] = 0;	/* '\0' */

  tcflush (tty->fd, TCIFLUSH);
  if (tcsetattr(tty->fd, TCSANOW, &tty->termios) < 0) {
    return serialError;
  }
  return serialSuccess;
}


/** 
 * Send, receive and process PanTilt messages
 * 
 * @param panTiltID 
 * @param cmd 
 * 
 * @return 
 */
serialStatus panTiltCMD(PanTiltID_t *panTiltID, char * cmd) {
  TTYController_t *tty = panTiltID->tty;
  PanTiltData_t   *panTiltData = panTiltID->panTiltData;
  int num = 0;
  int stop = 0;
  size_t size;
  int i, reason;
  char readdata[80];
  int state = WFSTAR;
  char thisChar;
  int msgSize = strlen(cmd);
  serialStatus status = serialSuccess;

  num = 0;  
  while ( stop == 0) {
    if (writeRaw(tty, cmd, msgSize, &size) != serialSuccess) {
#ifdef DRDC_DEBUG
      perror("Failed writting to serial!");
#endif
      return serialError;
    }
    num += size;
    if (num >= msgSize) stop = 1;
  }

  num = 0;
  stop = 0;
  strcpy(tty->message, "");
  while ( stop == 0) {

    if (readRaw(tty, readdata, 80, &size, &reason) != serialSuccess) {
#ifdef DRDC_DEBUG
      perror("Failed reading from serial!");
#endif
      stop = 1;
      status = serialError;
    }

    for(i=0; i < size; i++) {

      thisChar = readdata[i];

      if (thisChar == 0x0d) {
	stop = 1;
	if (state == WFSTAR) status = serialError;
	break;
      }

      switch(state) {

      case WFSTAR:
	if (thisChar == '*') {
	  state = WFDELIM;
	} else if (thisChar == '!') {
	  state = WFDELIM;
	}
	break;

      case WFDELIM:
	addChar(tty->message, thisChar);
	break;

      default:
	//Fixme -- throw exception
	break;
      }

      num += 1;
      if (num > 256) {
	stop = 1;
	status = serialError;
      }

    } //for end 
  } //while end

#ifdef DRDC_DEBUG
  printf("Message: %s\n", tty->message);
#endif
  handleMessage(tty->message, panTiltData);

  return status;
}

/** @} */

/**
 * @addtogroup timer Serial Timer Routines
 */
/** @{ */


/** 
 * Serial timer signal handler
 * 
 * @param sig 
 * @param sigInfo 
 * @param context 
 */
void serialTimerSignalHandler(int sig,  siginfo_t  *sigInfo, void *context) { 
  TTYController_t *tty;
  union sigval signalValue;  
  signalValue = sigInfo->si_value;
  tty = signalValue.sival_ptr;
#ifdef SIG_INFO_WORKAROUND
  globalTimeoutFlag = 1;
#else
  tty -> timeoutFlag = 1;
#endif
  #ifdef DRDC_DEBUG
  printf("Operation timed out!\n");
  #endif
  //exit(0);
} 

/** 
 * Create serial timer handler
 * 
 * @param timerid 
 * @param tty 
 * 
 * @return 
 */
int serialTimerCreate(timer_t *timerid, TTYController_t *tty) {
  struct sigaction sigact; 
  struct sigevent sigev; 
  int    status;

  sigact.sa_handler = (void *) serialTimerSignalHandler; 

  status = sigemptyset(&sigact.sa_mask); 
  assert( !status );

  sigact.sa_flags = SA_SIGINFO; 

  if (sigaction(tty->signalNumber, &sigact, NULL)  == -1) { 
    return 1;
  } 

  sigev.sigev_notify = SIGEV_SIGNAL; 
  sigev.sigev_signo = tty->signalNumber; 
  sigev.sigev_value.sival_ptr = (void *)tty;
  
  if (timer_create(CLOCK_REALTIME, &sigev, timerid)  == -1) { 
    return 1;
  } 

  return 0;
}

/** 
 * Set serial timer
 * 
 * @param timerid 
 * @param delay 
 * 
 * @return 
 */
int serialTimerSet(timer_t *timerid, double delay) {
  struct itimerspec value;

  value.it_value.tv_sec=(long)delay;
  value.it_value.tv_nsec=(long)((delay-(long)delay)*1000000000);
  value.it_interval.tv_sec=0;
  value.it_interval.tv_nsec=0;

  if (timer_settime(*timerid, 0, &value, NULL) == -1) { 
    return 1;
  }

  return 0;
}

/** 
 * Cancel serial timer
 * 
 * @param timerid 
 * 
 * @return 
 */
int serialTimerCancel(timer_t *timerid) {
  struct itimerspec value = { {0, 0}, {0, 0} } ;
  if (timer_settime(*timerid, 0, &value, NULL) == -1) { 
    return 1;
  }
  return 0;
}

/** 
 * Delete serial timer
 * 
 * @param timerid 
 * 
 * @return 
 */
int serialTimerDelete(timer_t *timerid) {
  if (timer_delete(*timerid) == -1) { 
    return 1; 
  } 
  return 0;
}

/** @} */


/**
 * @addtogroup User_API User APIs
 */
/** @{ */


/** 
 * Create PanTilt handler
 * 
 * @param serialName Serial port name.
 * @param readTimeout Read timeout value in second.
 * @param writeTimeout Write timeout value in second.
 * @param signalNumber Signal number. e.g. SIGUSR1.
 *
 * @return It returns PanTilt ID if succesful. Otherwise, it returns NULL if
 * errors occur.
 */
PanTiltID_t *createPanTilt(char *serialName, double readTimeout, double writeTimeout, int signalNumber) {

  PanTiltID_t *panTiltID = NULL;
  TTYController_t *tty;
  PanTiltData_t *panTiltData;
  timer_t timerid;

  panTiltID = (PanTiltID_t *) calloc(1, sizeof(PanTiltID_t));
  if (panTiltID == NULL) return NULL;
  panTiltID->tty = (TTYController_t *) calloc(1, sizeof(TTYController_t));
  if (panTiltID->tty == NULL) {
    free(panTiltID);
    return NULL;
  }
  panTiltID->panTiltData = (PanTiltData_t *) calloc(1, sizeof(PanTiltData_t));
  if (panTiltID->panTiltData == NULL) {
    free(panTiltID->tty);
    free(panTiltID);
    return NULL;
  }

  tty = panTiltID->tty;
  panTiltData = panTiltID->panTiltData;  

  tty->fd = -1;
  strcpy(tty->serialDeviceName, serialName);
  tty->readTimeout = readTimeout;
  tty->writeTimeout = writeTimeout;
  tty->signalNumber = signalNumber;

  if (serialTimerCreate(&timerid, tty)) {
#ifdef DRDC_DEBUG
    perror("Failed creating serial timer!");
#endif
    destroyPanTilt(panTiltID);
  }

  tty->timer = timerid;
  tty->timeoutFlag = 0;

  if (connectIt(tty) == serialError) {
#ifdef DRDC_DEBUG
    perror("Failed connect to serial!");
#endif
    destroyPanTilt(panTiltID);
    return NULL;
  }

  return panTiltID;
}
/** 
 * Destroy PanTilt Handler
 * 
 * @param panTiltID 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int destroyPanTilt(PanTiltID_t *panTiltID) {
  TTYController_t *tty = panTiltID->tty;
 
  if (closeConnection(tty) != serialSuccess) {
#ifdef DRDC_DEBUG
    perror("Failed closing serial!");
#else
    return 1;
#endif
  }
  
  serialTimerDelete(&tty->timer);

  free(panTiltID->tty);
  free(panTiltID->panTiltData);
  free(panTiltID);

  return 0;
}

/** 
 * Return pan position
 * 
 * @param panTiltID 
 * @param panValue 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int getPan(PanTiltID_t *panTiltID, double *panValue) {
  PanTiltData_t   *panTiltData = panTiltID->panTiltData;
  int status;

  status = panTiltCMD(panTiltID, "PP ");
  *panValue = pan2rad( panTiltData->panPosition );

  return status;
}
/** 
 * Return tilt position
 * 
 * @param panTiltID 
 * @param tiltValue 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int getTilt(PanTiltID_t *panTiltID, double *tiltValue) {
  PanTiltData_t   *panTiltData = panTiltID->panTiltData;
  int status;

  status = panTiltCMD(panTiltID, "TP ");
  *tiltValue =  tilt2rad( panTiltData->tiltPosition );
  return status;
}
/** 
 * Set pan position
 * 
 * @param panTiltID 
 * @param panValue 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setPan(PanTiltID_t *panTiltID, double panValue) {
  char cmd[20] = "PP";
  int status;

  addLong(cmd, rad2pan( panValue ));
  addChar(cmd, ' ');

  status = panTiltCMD(panTiltID, cmd);
  return status;
}

/** 
 * Set tilt position
 * 
 * @param panTiltID 
 * @param tiltValue 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setTilt(PanTiltID_t *panTiltID, double tiltValue) {
  char cmd[20] = "TP";
  int status;

  addLong(cmd, rad2tilt( tiltValue ));
  addChar(cmd, ' ');

  status = panTiltCMD(panTiltID, cmd);
  return status;
}


/** 
 * Set pan and tilt position
 * 
 * @param panTiltID 
 * @param dest 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setPosition(PanTiltID_t *panTiltID, const PanTiltPositionIDL_t *dest) {
  return (setPan(panTiltID, dest->panvalue) + setTilt(panTiltID, dest->tiltvalue));
}

/** 
 * Return pan and tilt position
 * 
 * @param panTiltID 
 * @param result 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */ 
int getPosition(PanTiltID_t *panTiltID, PanTiltPositionIDL_t *result) {
  double panvalue, tiltvalue;
  int status;

  status = getPan(panTiltID, &panvalue) + getTilt(panTiltID, &tiltvalue);
  result->panvalue = panvalue;
  result->tiltvalue = tiltvalue;

  return status;
}

  
/** 
 * Await pan and tilt postion command completion
 * 
 * @param panTiltID 
 * @param dest 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setWaitPosition(PanTiltID_t *panTiltID, const PanTiltPositionIDL_t *dest) {
   char cmd[20];

   if (setPan(panTiltID, dest->panvalue)) return 1;
   if (setTilt(panTiltID, dest->tiltvalue)) return 1;

   strcpy(cmd, "A ");
   return panTiltCMD(panTiltID, cmd);
 }

/** 
 * Return speed and acceleration settings
 * 
 * @param panTiltID 
 * @param result 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int getSpdAcc(PanTiltID_t *panTiltID,  PanTiltSpdAccIDL_t *result) {
   PanTiltData_t   *panTiltData = panTiltID->panTiltData;
   //TTYController_t *tty = panTiltID->tty;
   char cmd[20];

   strcpy(cmd, "PS ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TS ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PB ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PL ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PU ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TB ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TL ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TU ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PA ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TA ");
   if (panTiltCMD(panTiltID, cmd)) return 1;

   result->targetpanspeed = pan2rad( panTiltData->targetPanSpeed );
   result->targettiltspeed = tilt2rad( panTiltData->targetTiltSpeed );

   result->panbasespeed = pan2rad( panTiltData->panBaseSpeed );
   result->panminspeed = pan2rad( panTiltData->minPanSpeed );
   result->panmaxspeed = pan2rad( panTiltData->maxPanSpeed );
   
   result->tiltbasespeed = tilt2rad( panTiltData->tiltBaseSpeed );
   result->tiltminspeed = tilt2rad( panTiltData->minTiltSpeed );
   result->tiltmaxspeed = tilt2rad( panTiltData->maxTiltSpeed );
   
   result->panacc = pan2rad( panTiltData->panAcceleration );
   result->tiltacc = tilt2rad( panTiltData->tiltAcceleration );

   return 0;
 }

/** 
 * Set speed and acceleration
 * 
 * @param panTiltID 
 * @param dest 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setSpdAcc(PanTiltID_t *panTiltID, const PanTiltSpdAccIDL_t *dest ) {
  //TTYController_t *tty = panTiltID->tty;
   char cmd[20];
   
   strcpy(cmd, "PS" );
   addLong(cmd, rad2pan( dest->targetpanspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TS" );
   addLong(cmd, rad2tilt( dest->targettiltspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

 
   strcpy(cmd, "PB" );
   addLong(cmd, rad2pan( dest->panbasespeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PL" );
   addLong(cmd, rad2pan( dest->panminspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PU" );
   addLong(cmd, rad2pan( dest->panmaxspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TB" );
   addLong(cmd, rad2tilt( dest->tiltbasespeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TL" );
   addLong(cmd, rad2tilt( dest->tiltminspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TU" );
   addLong(cmd, rad2tilt( dest->tiltmaxspeed ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PA" );
   addLong(cmd, rad2pan( dest->panacc ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TA" );
   addLong(cmd, rad2tilt( dest->tiltacc ) );
   addChar(cmd, ' ');
   if (panTiltCMD(panTiltID, cmd)) return 1;

    return 0;
 }
  

/** 
 * Query limit position
 *
 * Queries return the axis position bounds determined upon unit reset
 * 
 * @param panTiltID 
 * @param result 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int getLimits(PanTiltID_t *panTiltID, PanTiltLimitsIDL_t *result) {
   PanTiltData_t   *panTiltData = panTiltID->panTiltData;
   //TTYController_t *tty = panTiltID->tty;
   char cmd[20];

   strcpy(cmd, "PN " );
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "PX " );
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TN " );
   if (panTiltCMD(panTiltID, cmd)) return 1;

   strcpy(cmd, "TX " );
   if (panTiltCMD(panTiltID, cmd)) return 1;

   result->minpanposition = pan2rad( panTiltData->minPanPosition );
   result->maxpanposition = pan2rad( panTiltData->maxPanPosition );
   result->mintiltposition = tilt2rad( panTiltData->minTiltPosition );
   result->maxtiltposition = tilt2rad( panTiltData->maxTiltPosition );

   return 0;
 }
/** 
 * Set stationary power and in-motion power settings
 *
 * Set the current level applied to axis motors when in-transit or not in-tranistion.
 * 
 * @param panTiltID 
 * @param dest 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur.
 */
int setPowers(PanTiltID_t *panTiltID, PanTiltPowersIDL_t *dest) {
  //TTYController_t *tty = panTiltID->tty;
   char cmd[20];

   strcpy(cmd, "PH" );
   if (dest->panhold == 0)
     addChar(cmd, 'O' );
   else if (dest->panhold == 1)
     addChar(cmd, 'L' );
   else
     addChar(cmd, 'R' );

   if (panTiltCMD(panTiltID, cmd)) return 1;


   strcpy(cmd, "TH" );
   if (dest->tilthold == 0)
     addChar(cmd, 'O' );
   else if (dest->tilthold == 1)
     addChar(cmd, 'L' );
   else
     addChar(cmd, 'R' );
   if (panTiltCMD(panTiltID, cmd)) return 1;


   strcpy(cmd, "PM" );
   if (dest->panmove == 0)
     addChar(cmd, 'L' );
   else if (dest->panmove == 1)
     addChar(cmd, 'R' );
   else
     addChar(cmd, 'H' );
   if (panTiltCMD(panTiltID, cmd)) return 1;


   strcpy(cmd, "TM" );
   if (dest->tiltmove == 0)
     addChar(cmd, 'L' );
   else if (dest->tiltmove == 1)
     addChar(cmd, 'R' );
   else
     addChar(cmd, 'H' );
   if (panTiltCMD(panTiltID, cmd)) return 1;
    
   return 0;

 }

/** 
 * Return stationary power and in-motion power settings
 * 
 * Rteurn the current level applied to axis motors when in-transit or not in-tranistion.
 *
 * @param panTiltID 
 * @param result 
 * 
 * @return It returns zero if succesful. Otherwise, it returns one if
 * errors occur. 
 */
int getPowers(PanTiltID_t *panTiltID, PanTiltPowersIDL_t *result) {
  PanTiltData_t   *panTiltData = panTiltID->panTiltData;
  //TTYController_t *tty = panTiltID->tty;
  char cmd[20];

  strcpy(cmd, "PH " );
  if (panTiltCMD(panTiltID, cmd)) return 1;
  

  strcpy(cmd, "TH " );
  if (panTiltCMD(panTiltID, cmd)) return 1;
  

  strcpy(cmd, "PM " );
  if (panTiltCMD(panTiltID, cmd)) return 1;
  

  strcpy(cmd, "TM " );
  if (panTiltCMD(panTiltID, cmd)) return 1;
  

  result->panhold = panTiltData->panHold;
  result->tilthold = panTiltData->tiltHold;
  result->panmove = panTiltData->panMove;
  result->tiltmove = panTiltData->tiltMove;

  return 0;
}

/** @} */

