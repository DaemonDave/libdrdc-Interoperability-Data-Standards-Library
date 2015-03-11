ALLTESTS = test_cexcept test_cexcept1

TESTS = $(ALLTESTS)

check_PROGRAMS = 	$(ALLTESTS)	

# test_cexcept  behaviour 
noinst_PROGRAMS = test_cexcept  test_cexcept1

#cexcept: example1.c 2.0.0 (2001-Jul-12-Thu)
# Adam M. Costello <amc@cs.berkeley.edu>
#
# This test file tests single-threaded try / catch and uses a global exception context
test_cexcept_SOURCES = example1.c 
test_cexcept_CFLAGS = -I @abs_top_srcdir@/src/cexcept																					
test_cexcept_LDFLAGS = -static $(all_libraries) 
test_cexcept_LDADD = 

# cexcept: example2.c 2.0.0 (2001-Mar-21-Wed)
#	Adam M. Costello <amc@cs.berkeley.edu>
#
# An example application that demonstrates how to use version 2.0.* of the
# cexcept.h interface to provide polymorphic exceptions, while avoiding
# the use of global variables.  It also illustrates the use of dynamically
# nested Try blocks.
test_cexcept1_SOURCES = example2.c 	
test_cexcept1_CFLAGS = -I @abs_top_srcdir@/src/cexcept 																						
test_cexcept1_LDFLAGS = -static $(all_libraries) 
test_cexcept1_LDADD = 

