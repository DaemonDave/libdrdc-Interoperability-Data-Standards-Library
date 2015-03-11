## librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

## HER MAJESTY THE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
## OF NATIONAL DEFENCE, CANADA, 2007

## Developed by:  Erickson, D. (DRDC Suffield)

## This library is free software;.  You can redistribute it and/or modify
## it under the terms and conditions of the GNU Lesser General Public
## License as published by the Free Software Foundation; either

## Version 2.1 of the License, or (at your option) any later version.

## This library is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
## Lesser General Public License for more details.

## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
## USA

## Licence is located in license.txt in libdrdc source root


##
## Description  : libdrdc - Makefile.am
## Author       : Tie Peng
## Purpose      : main library file
## Revision     : $Id: Makefile.am,v 1.12 2008/12/02 20:49:08 cvsuser Exp $
##

SUBDIRS = cexcept coordinate matrix_ops homogeneous quaternion time_conv unit_conv data_conv wrapper 
#sglib
include_HEADERS = libdrdc.h

# additional subdirectories
if F2CBLAS
SUBDIRS += f2c_blas
endif

if EXTRAS
SUBDIRS += extras
endif

# main library adding up convenience sub-libs
lib_LTLIBRARIES = libdrdc.la
libdrdc_la_SOURCES =

libdrdc_la_LIBADD = coordinate/libcoordinate.la \
			matrix_ops/libmatrix_ops.la \
			unit_conv/libunit_conv.la \
			homogeneous/libhomogeneous.la \
			quaternion/libquaternion.la \
			time_conv/libtime_conv.la \
			wrapper/libwrapper.la \
			cexcept/libexcept.la \
			data_conv/libdata_conv.la
			 
			
#			sglib/libsglib.la
								
									
										
# Version info; seems to be broken on autotools part, gets the numbers backward in library final build
libdrdc_la_LDFLAGS = -version-info @MAJORVERSION@:@MINORVERSION@:@REVISION@

## conditional library elements
if F2CBLAS
libdrdc_la_LIBADD  += f2c_blas/libf2c_blas.la
libdrdc_la_LDFLAGS += 
endif

if EXTRAS
libdrdc_la_LIBADD  += extras/libextra.la
libdrdc_la_LIBADD  += extras/dp46/libdp46.la
libdrdc_la_LDFLAGS += 
endif

AM_CPPFLAGS = -I../ -I. 

