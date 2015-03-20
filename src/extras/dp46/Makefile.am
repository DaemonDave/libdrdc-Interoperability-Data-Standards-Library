# @file Makefile.src.am
#
# $Id: Makefile.am,v 1.1 2008/12/02 20:45:48 cvsuser Exp $

bin_PROGRAMS = test
test_SOURCES = test.c 
test_LDADD = libdp46.la

noinst_LTLIBRARIES = libdp46.la

libdp46_la_SOURCES = 	PanTiltMessage.c PanTiltImp.c
libdp46_la_INCLUDES =  	PanTilt.h  system.h  tty_drv.h

AM_CPPFLAGS = -I.

LDADD = -lm

#include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
#include $(RTEMS_CUSTOM)
#include $(RTEMS_ROOT)/make/directory.cfg
