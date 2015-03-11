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

// Some functions are copied and modified from OpenJaus.ls


/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: time_conv.c,v 1.2 2008/08/12 16:02:35 cvsuser Exp $
 */


#include <stdio.h>
#include <time.h>
#include <sys/time.h> 
#include "time_conv.h"

struct timeval timeUtcToGps(const short leapSec, const struct timeval *utcTime) {
  struct timeval gpsTime;
  gpsTime.tv_sec  = utcTime->tv_sec - 315964800 + leapSec - 19;
  gpsTime.tv_usec = utcTime->tv_usec;
  return gpsTime;
}


struct timeval timeGpsToUtc(const short leapSec, const struct timeval *gpsTime) {
  struct timeval utcTime;
  utcTime.tv_sec  = gpsTime->tv_sec - leapSec + 19 + 315964800;
  utcTime.tv_usec = gpsTime->tv_usec;
  return utcTime;
}


int jausTimeConvert(const struct timeval *timeVal, JausTime_t *time) {
  static struct tm *gmTime;
  //static struct timeval timeVal;
        
  // Get SystemTime
  //gettimeofday(&timeVal, NULL);
  gmTime = gmtime(&timeVal->tv_sec);

  // Populate members
  time->millisec =        (unsigned short) (timeVal->tv_usec / 1.0e3);
  time->second =          (unsigned short) gmTime->tm_sec;
  time->minute =          (unsigned short) gmTime->tm_min;
  time->hour =            (unsigned short) gmTime->tm_hour;
  time->day =             (unsigned short) gmTime->tm_mday;
  time->month =           (unsigned short) gmTime->tm_mon;
  time->year =            (unsigned short) gmTime->tm_year + 1900;

  // Pack TimeStamp & DateStamp
  jausTimeStampPack(time);
  jausDateStampPack(time);

  return 1;
}


// Private Functions
int jausTimeStampPack(JausTime_t *time) {
  time->timeStamp = 0;
  time->timeStamp |= (time->millisec & JAUS_TIME_STAMP_MILLISEC_MASK) << JAUS_TIME_STAMP_MILLISEC_SHIFT;
  time->timeStamp |= (time->second & JAUS_TIME_STAMP_SECOND_MASK) << JAUS_TIME_STAMP_SECOND_SHIFT;
  time->timeStamp |= (time->minute & JAUS_TIME_STAMP_MINUTE_MASK) << JAUS_TIME_STAMP_MINUTE_SHIFT;
  time->timeStamp |= (time->hour & JAUS_TIME_STAMP_HOUR_MASK) << JAUS_TIME_STAMP_HOUR_SHIFT;
  time->timeStamp |= (time->day & JAUS_TIME_STAMP_DAY_MASK) << JAUS_TIME_STAMP_DAY_SHIFT;

  return 1;
}

int jausDateStampPack(JausTime_t *time) {
  time->dateStamp = 0;
  time->dateStamp |= (time->day & JAUS_DATE_STAMP_DAY_MASK) << JAUS_DATE_STAMP_DAY_SHIFT;
  time->dateStamp |= (time->month & JAUS_DATE_STAMP_MONTH_MASK) << JAUS_DATE_STAMP_MONTH_SHIFT;
  time->dateStamp |= (time->year & JAUS_DATE_STAMP_YEAR_MASK) << JAUS_DATE_STAMP_YEAR_SHIFT;
        
  return 1;
}

int jausTimeToString(JausTime_t *time, char *buffer) {
  const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

  if(time) {               
    sprintf(buffer, "%s %02d, %04d  %02d:%02d:%02d.%d\n", months[time->month], time->day, time->year, time->hour, time->minute, time->second, time->millisec);
    return 1;
  } else
    return 0;
}

int jausTimeStampUnpack(JausTime_t *time) {
                
  // UnPack Members from TimeStamp
  time->millisec = (time->timeStamp >> JAUS_TIME_STAMP_MILLISEC_SHIFT) & JAUS_TIME_STAMP_MILLISEC_MASK;
  time->second = (time->timeStamp >> JAUS_TIME_STAMP_SECOND_SHIFT) & JAUS_TIME_STAMP_SECOND_MASK;
  time->minute = (time->timeStamp >> JAUS_TIME_STAMP_MINUTE_SHIFT) & JAUS_TIME_STAMP_MINUTE_MASK;
  time->hour = (time->timeStamp >> JAUS_TIME_STAMP_HOUR_SHIFT) & JAUS_TIME_STAMP_HOUR_MASK;
  time->day = (time->timeStamp >> JAUS_TIME_STAMP_DAY_SHIFT) & JAUS_TIME_STAMP_DAY_MASK;
  
  return 0;
}

int jausDateStampUnpack(JausTime_t *time) {
  
  // Pack Members from DateStamp
  time->day = (time->dateStamp >> JAUS_DATE_STAMP_DAY_SHIFT) & JAUS_DATE_STAMP_DAY_MASK;
  time->month = (time->dateStamp >> JAUS_DATE_STAMP_MONTH_SHIFT) & JAUS_DATE_STAMP_MONTH_MASK;
  time->year = (time->dateStamp >> JAUS_DATE_STAMP_YEAR_SHIFT) & JAUS_DATE_STAMP_YEAR_MASK;
  
  return 0;
}







