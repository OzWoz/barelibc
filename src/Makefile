#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include ../Makefile.config

DIRLIST = assert complex ctype errno fenv \
float __init inttypes iso646 limits locale math \
setjmp signal smp stdarg stdbool stddef \
stdint stdio stdlib string tgmath time wchar wctype \
__os_$(__OS)

.PHONY: all $(DIRLIST) copyinc $(DIRLIST:%=%_copyinc)

all: copyinc $(DIRLIST)

copyinc: $(DIRLIST:%=%_copyinc)

$(DIRLIST): copyinc
	make -C $@ all

$(DIRLIST:%=%_copyinc):
	make -C $(subst _copyinc,,$@) copyinc

.PHONY: clean $(DIRLIST:%=%_clean)
clean: $(DIRLIST:%=%_clean)
	rm -f __init/$(LIB)

$(DIRLIST:%=%_clean):
	make -C $(subst _clean,,$@) clean
	

###
