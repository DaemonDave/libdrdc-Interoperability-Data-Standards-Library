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


/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      : to describe the time conventions
 * Revision     : $Id: time_conv.h,v 1.7 2008/09/17 15:33:30 cvsuser Exp $
 */


#ifndef TIME_CONV_H
#define TIME_CONV_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif

#include <time.h>
#include <sys/time.h> 


/**
 * JAUS Timestamp and Datestamp Structure
 * /typedef 
 */
typedef struct 
{
        uint32_t timeStamp;
        uint16_t dateStamp;
        uint16_t millisec;
        uint16_t second;
        uint16_t minute;
        uint16_t hour;
        uint16_t day;
        uint16_t month;
        uint16_t year;
        
} JausTime_t;


#define JAUS_TIME_STAMP_SIZE_BYTES              JAUS_UNSIGNED_INTEGER_SIZE_BYTES // size
#define JAUS_DATE_STAMP_SIZE_BYTES              JAUS_UNSIGNED_SHORT_SIZE_BYTES // size

// Bit Shift Defines
#define JAUS_TIME_STAMP_MILLISEC_SHIFT 					0
#define JAUS_TIME_STAMP_SECOND_SHIFT    				10
#define JAUS_TIME_STAMP_MINUTE_SHIFT   					16
#define JAUS_TIME_STAMP_HOUR_SHIFT              22
#define JAUS_TIME_STAMP_DAY_SHIFT               27
#define JAUS_DATE_STAMP_DAY_SHIFT               0
#define JAUS_DATE_STAMP_MONTH_SHIFT     				5
#define JAUS_DATE_STAMP_YEAR_SHIFT              9

// Bit Mask Defines
#define JAUS_TIME_STAMP_MILLISEC_MASK   				0x1FF   // 9 bits
#define JAUS_TIME_STAMP_SECOND_MASK     				0x3F    // 6 bits
#define JAUS_TIME_STAMP_MINUTE_MASK     				0x3F    // 6 bits
#define JAUS_TIME_STAMP_HOUR_MASK               0x1F    // 5 bits
#define JAUS_TIME_STAMP_DAY_MASK                0x1F    // 5 bits
#define JAUS_DATE_STAMP_DAY_MASK                0x1F    // 5 bits
#define JAUS_DATE_STAMP_MONTH_MASK              0x0F    // 4 bits
#define JAUS_DATE_STAMP_YEAR_MASK               0x7F    // 7 bits


/*!
	\brief
	
	Time Conversion contains functions to convert various time representations.
	
	- JAUS to/from UTC
	- JAUS to/from GPS
	- UTC to/from GPS

The standard time scale representation adopted is UTC- Coordinated
Universal Time. UTC is equivalent to mean solar time at the prime meridian
(0 longitude), formerly expressed as UT1 or Greenwich Mean Time (GMT).
UT1 is also known as world time, Z time, and Zulu time. UTC is defined by
the CCIR Recommendation 460-4 and is maintained by various military and
governmental organizations. UTC is chosen because it more accurately
portrays the day/night conditions locally. This will manifest itself when
attempting to correlate visual imagery at dawn and dusk.


\see UTC in wikipedia  http://en.wikipedia.org/wiki/UTC


\todo  complete documentation and make UTC leap second table clear

*/



/**
 * @addtogroup time Time Convention API 
 */
/** @{ */


/**
 * Convert UTC time to GPS time
 * 
 * @param[in] 	leapSec  Leap second adjustment. 
 * @param[in] 	utcTime  UTC time.
 * 
 * @return[out]  returns GPS time.
 
 The relationship between GPS and UTC time is governed by the equation:
          \f$   GPS = UTC + L \f$                  
where L is the number of leap seconds added since 1981-07-01. Currently,
GPS time is 13 seconds ahead of UTC as of 2005-01-01. The GPS time will
vary relative to UTC as more leap seconds are added onto UTC. According to
International Earth Rotation Service (IERS), no positive leap second will be
introduced at the end of June 2005 so this difference of 13 seconds will hold
until December 31 2005. After this point, the time difference for GPS
readings will need to be adjusted as IERS adjusts UTC. Since GPS time is
universal and not subject to the latencies of Network Time Protocol (NTP)
using UTC, it can be used to correct errant onboard clocks.

 
 */
struct timeval timeUtcToGps(const short leapSec, const struct timeval *utcTime);

/** 
 * Convert GPS time to UTC time
 * 
 * @param leapSec Input. Leap second adjustment.
 * @param gpsTime Input. GPS time.
 * 
 * @return It returns UTC time.
 
 The relationship between GPS and UTC time is governed by the equation:
          \f$   UTC = GPS - L \f$                  
where L is the number of leap seconds added since 1981-07-01. Currently,
GPS time is 13 seconds ahead of UTC as of 2005-01-01. The GPS time will
vary relative to UTC as more leap seconds are added onto UTC. According to
International Earth Rotation Service (IERS), no positive leap second will be
introduced at the end of June 2005 so this difference of 13 seconds will hold
until December 31 2005. After this point, the time difference for GPS
readings will need to be adjusted as IERS adjusts UTC. Since GPS time is
universal and not subject to the latencies of Network Time Protocol (NTP)
using UTC, it can be used to correct errant onboard clocks. 
 
 
 */
struct timeval timeGpsToUtc(const short leapSec, const struct timeval *gpsTime);


/** 
 * Convert Time to Jaus Timestamp and Datestamp  
 * 
 * @param timeVal Input. Unix time value.
 * @param time Output. Jaus time structure.
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausTimeConvert(const struct timeval *timeVal, JausTime_t *time);

/** 
 * Pack Jaus Timestamp 
 * 
 * @param time Input/Output. Jaus time structure.
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausTimeStampPack(JausTime_t *time);

/** 
 * Pack Jaus Datestamp
 * 
 * @param time Input/Output. Jaus time structure.
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausDateStampPack(JausTime_t *time);

/** 
 * Convert Jaus Time Structure to String
 * 
 * @param time time Input. Jaus time structure.
 * @param buffer Output. String of Timestamp and datestamp.
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausTimeToString(JausTime_t *time, char *buffer);

/** 
 * Unpack Jaus Timestamp
 * 
 * @param time Input/Output. Jaus time structure.
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausTimeStampUnpack(JausTime_t *time);


/** 
 * Unpack Jaus Datestamp
 * 
 * @param time Input/Output. Jaus time structure. 
 * 
 * @return It returns zero if successful. Otherwise, it returns one.
 */
int jausDateStampUnpack(JausTime_t *time);



/** @} */
#endif
