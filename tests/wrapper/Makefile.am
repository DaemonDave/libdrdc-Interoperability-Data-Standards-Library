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
## Purpose      : wrapper test targets
## Revision     : $Id: Makefile.am,v 1.5 2008/09/17 15:33:30 cvsuser Exp $
##
 
 
# insert tests into this live for make check inclusion
ALLTESTS = wrapper_tests


TESTS = $(ALLTESTS)

check_PROGRAMS = 	$(ALLTESTS)	


wrapper_tests_SOURCES = wrapper_cpp_tests.cc
AM_CPPFLAGS = -I../../src -I../../src/wrapper -I../../src/matrix_ops -I../../src/coordinate -I../../src/quaternion -I../../src/homogeneous  -I../../src/data_conv -I../../src/time_conv  -I../../src/unit_conv -I../common -I../../src/cexcept -I../../src/sglib

LDADD = ../common/libtest.a ../../src/wrapper/libwrapper.la ../../src/matrix_ops/libmatrix_ops.la ../../src/coordinate/libcoordinate.la ../../src/quaternion/libquaternion.la  ../../src/homogeneous/libhomogeneous.la ../../src/time_conv/libtime_conv.la ../../src/unit_conv/libunit_conv.la ../../src/data_conv/libdata_conv.la -lm


if F2CBLAS
LDADD += ../../src/f2c_blas/libf2c_blas.la -lm
else
LDADD += -lblas -lm
endif
