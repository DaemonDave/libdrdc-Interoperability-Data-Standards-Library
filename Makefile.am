SUBDIRS= src

DIST_SUBDIRS= src
if TESTS
  SUBDIRS+= tests
  DIST_SUBDIRS+= tests
else

endif


# target makes doxygen outputs, after updating config format file
dox:
	doxygen -u doxygen/libdrdc.cfg
	doxygen doxygen/libdrdc.cfg


#AM_CFLAGS
#AM_LDFLAGS
