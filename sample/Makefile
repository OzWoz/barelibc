#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

DIRLIST = hellostd string assert alloc sleep stdarg smp pf int3 atomic $(wildcard cchartab)

###################################

include ../Makefile.config

.PHONY: all $(DIRLIST)
all: $(DIRLIST)

$(DIRLIST):
	make -C $@ all

.PHONY: clean $(DIRLIST:%=%_clean)
clean: $(DIRLIST:%=%_clean)

$(DIRLIST:%=%_clean):
	make -C $(subst _clean,,$@) clean
	

###
