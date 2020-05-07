AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#endif

include Makefile-LIBADD.inc

lib_LTLIBRARIES = librw2chipc.la
include_HEADERS = rw2chipc.h
librw2chipc_la_LIBADD = $(LIBRW2CHIPC_LIBADD)
