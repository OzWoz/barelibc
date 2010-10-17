#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

HEADERNAME = __os
CFILES = baremetal
BINCOPY = blc_crt0.o
CLEANFILES = blc_crt0.o

blc_crt0.o: blc_crt0.c copyinc
	$(CC) $(CFLAGS) -c -o $@ $<

include ../Makefile.tpl

###
