#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include ../Makefile.config

DIRLIST = hellostd string assert alloc sleep stdarg smp pf int3 atomic prime hashtable $(wildcard cchartab)


.PHONY: all $(DIRLIST)
all: $(DIRLIST)

$(DIRLIST):
	make -C $@ all

.PHONY: clean $(DIRLIST:%=%_clean)
clean: $(DIRLIST:%=%_clean)

$(DIRLIST:%=%_clean):
	make -C $(subst _clean,,$@) clean
	
.PHONY: distclean $(DIRLIST:%=%_distclean)
distclean: $(DIRLIST:%=%_distclean)

$(DIRLIST:%=%_distclean):
	make -C $(subst _distclean,,$@) distclean

###
