//#define RTEMS_DRIVER
#ifdef RTEMS_DRIVER
#define CONFIGURE_INIT
#include "system.h"
#endif

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

#ifdef RTEMS_DRIVER
void *POSIX_Init(void *argument)
//rtems_task Init(rtems_task_argument argument)
#else
int main()
#endif

{
  double panDemoPosn = 2.14;
  double tiltDemoPosn = 1.14;
  double diff;

  double readTimeout = 1.0;
  double writeTimeout = 1.0;
  int signalNumber = SIGUSR1;
  double panValue, tiltValue;
  PanTiltLimitsIDL_t limitsResult;
  PanTiltPowersIDL_t powersResult;
  PanTiltPositionIDL_t positionResult;
  PanTiltSpdAccIDL_t spdAccResult;

  printf("PanTilt Demo ... \n\n");

#ifdef RTEMS_DRIVER
  PanTiltID_t *panTiltID = createPanTilt("/dev/ttyS1", readTimeout, writeTimeout, signalNumber);
#else
  PanTiltID_t *panTiltID = createPanTilt("/dev/ttyS0", readTimeout, writeTimeout, signalNumber);
#endif
  
  if (panTiltID == NULL) {
    exit(1);
  }

  if (getPosition(panTiltID, &positionResult)) {
    destroyPanTilt(panTiltID);
    exit(1);
  }
  printf("Position: %f %f\n",  positionResult.panvalue, positionResult.tiltvalue);

  diff = fabs(positionResult.panvalue - panDemoPosn);
  printf("Pan diff = %f\n", diff);
  if (diff > 0.015)
    setPan(panTiltID, panDemoPosn);
  else 
    setPan(panTiltID, -panDemoPosn);


/*   diff = fabs(positionResult.tiltvalue - tiltDemoPosn); */
/*   printf("Pan diff = %f\n", diff); */
/*   if (diff > 0.015) */
/*     setTilt(panTiltID, tiltDemoPosn); */
/*   else  */
/*     setTilt(panTiltID, -tiltDemoPosn); */

  getPan(panTiltID, &panValue);
  getTilt(panTiltID, &tiltValue);

  printf("tilt = %f\n", tiltValue);
  printf("Pan = %f\n", panValue);

  getLimits(panTiltID, &limitsResult);
  printf("Limits: %f %f %f %f\n",  limitsResult.minpanposition, limitsResult.maxpanposition, limitsResult.mintiltposition, limitsResult.maxtiltposition);

  getPowers(panTiltID, &powersResult);
  printf("Powers: %ld %ld %ld %ld\n",  powersResult.panhold, powersResult.tilthold, powersResult.panmove, powersResult.tiltmove);

  if (getSpdAcc(panTiltID,  &spdAccResult)) {
    printf("Error!");
  }
  printf("spdAccResult.targetpanspeed: %f\n", spdAccResult.targetpanspeed);
  printf("spdAccResult.targettiltspeed: %f\n", spdAccResult.targettiltspeed);
  
  printf("spdAccResult.panbasespeed: %f\n", spdAccResult.panbasespeed);
  printf("spdAccResult.panminspeed: %f\n", spdAccResult.panminspeed);
  printf("spdAccResult.panmaxspeed: %f\n", spdAccResult.panmaxspeed);

  printf("spdAccResult.tiltbasespeed: %f\n", spdAccResult.tiltbasespeed);
  printf("spdAccResult.tiltminspeed: %f\n", spdAccResult.tiltminspeed);
  printf("spdAccResult.tiltmaxspeed: %f\n", spdAccResult.tiltmaxspeed);

  printf("spdAccResult.panacc: %f\n", spdAccResult.panacc);
  printf("spdAccResult.tiltacc: %f\n", spdAccResult.tiltacc);

  destroyPanTilt(panTiltID);

  exit(0);
  
}




