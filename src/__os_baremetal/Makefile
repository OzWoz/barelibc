#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

HEADERNAME = __os
BINCOPY = app.ld blc_crt0.o
INCCOPY = __os_inc.h
CLEANFILES = __os_inc.h blc_crt0.o

__os_inc.h: bmdev.asm os_inc.awk
	awk -f os_inc.awk < $< > $@

blc_crt0.o: blc_crt0.c copyinc
	$(CC) $(CFLAGS) -c -o $@ $<

include ../Makefile.tpl

###
