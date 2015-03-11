#lib_LIBRARIES = libwrapper.a
#libwrapper_a_SOURCES =  wrapper_ooc.c  wrapper.h
#if CPPWRAPPER
#libwrapper_a_SOURCES = wrapper_ooc.c wrapper_cpp.cc wrapper.h
#else
#libwrapper_a_SOURCES = wrapper.c wrapper.h
#endif
#AM_CFLAGS = -std=c99 -pedantic -g -O2

noinst_LTLIBRARIES = libwrapper.la
libwrapper_la_SOURCES = wrapper_ooc.c wrapper_cpp.cc wrapper.h
AM_CPPFLAGS = -I../  -I../coordinate  -I../homogeneous  -I../quaternion  -I../matrix_ops -I../cexcept

include_HEADERS = wrapper.h

