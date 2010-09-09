#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include Makefile.config

DIRLIST = src sample

sample: src

.PHONY: all $(DIRLIST)
all: $(DIRLIST)

$(DIRLIST):
	make -C $@ all

.PHONY: clean $(DIRLIST:%=%_clean)
clean: $(DIRLIST:%=%_clean)

$(DIRLIST:%=%_clean):
	make -C $(subst _clean,,$@) clean

.PHONY: store
store: clean
	tar czf store/barelibc_`date +%F_%H-%M`.tar.gz --exclude=store --exclude=cchartab ../barelibc 
	
###