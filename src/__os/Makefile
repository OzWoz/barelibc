#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

HEADERNAME = __os
BINCOPY = app.ld crt0.o
INCCOPY = __os_inc.h
CLEANFILES = crt0.o __os_inc.h

crt0.o: crt0.asm bmdev.asm
__os_inc.h: bmdev.asm
	awk -f os_inc.awk < $< > $@

include ../Makefile.tpl

###
