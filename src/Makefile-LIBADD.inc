include ../SFork/src/Makefile-LIBADD.inc
include ../ezfork/src/Makefile-LIBADD.inc
include ../restart/src/Makefile-LIBADD.inc

LIBRW2CHIPC_LIBADD = -lsfork $(LIBSFORK_LIBADD) -lezfork $(LIBEZFORK_LIBADD) -lrestart $(LIBRESTART_LIBADD)
