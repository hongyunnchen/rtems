rtems_tests_PROGRAMS = speventsystem01
speventsystem01_SOURCES = init.c

dist_rtems_tests_DATA = speventsystem01.scn speventsystem01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(speventsystem01_OBJECTS)
LINK_LIBS = $(speventsystem01_LDLIBS)

speventsystem01$(EXEEXT): $(speventsystem01_OBJECTS) $(speventsystem01_DEPENDENCIES)
	@rm -f speventsystem01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
