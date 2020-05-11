include ../ezfork/src/Makefile-LIBADD.inc
include ../restart/src/Makefile-LIBADD.inc

LIBSFORK_LIBADD = -lezfork $(LIBEZFORK_LIBADD) -lrestart $(LIBRESTART_LIBADD)
