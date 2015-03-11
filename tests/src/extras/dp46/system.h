/*
 * Description  : DP PanTilt Driver RTEMS Header File
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: system.h,v 1.1 2008/12/02 20:45:48 cvsuser Exp $
 */

#ifndef __POSIX_TEST_MACROS_h
#define __POSIX_TEST_MACROS_h

#include <bsp.h>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <rtems.h>
#include "tty_drv.h"

void *POSIX_Init(
  void *argument
);



#define CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE
rtems_driver_address_table Device_drivers[] = {
  CONSOLE_DRIVER_TABLE_ENTRY,
  CLOCK_DRIVER_TABLE_ENTRY,
  TTY1_DRIVER_TABLE_ENTRY,
  TTY2_DRIVER_TABLE_ENTRY,
  {NULL, NULL, NULL, NULL, NULL, NULL}
};


/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER


//#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_TASKS 2

//#define CONFIGURE_INIT

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 8

#define CONFIGURE_MAXIMUM_DEVICES       50
#define CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE

#define CONFIGURE_MAXIMUM_POSIX_THREADS        4
#define CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS 5


#define CONFIGURE_MAXIMUM_POSIX_TIMERS              4
#define CONFIGURE_MAXIMUM_TIMERS                    4
#define CONFIGURE_MAXIMUM_POSIX_MUTEXES             2
#define CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES 2


/* #define CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS 5 */


#define CONFIGURE_POSIX_INIT_THREAD_TABLE
#define CONFIGURE_POSIX_INIT_THREAD_STACK_SIZE \
        (RTEMS_MINIMUM_STACK_SIZE * 4)

#include <rtems/confdefs.h>

#endif
