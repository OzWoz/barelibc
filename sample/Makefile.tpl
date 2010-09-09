#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include ../../Makefile.config

.PHONY: all
all: $(BINDIR)/$(EXECNAME).app

$(BINDIR)/$(EXECNAME).app: $(BINDIR)/crt0.o $(CFILES:%=%.o) $(LIB)
	$(LD) $(LDFLAGS) -o $@ $+

$(CFILES:%=%.o): $$(patsubst %.o,%.c,$$@) $(HFILES:%=%.h)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean $(CFILES:%=%_clean)
clean: $(CFILES:%=%_clean)
	rm -f $(BINDIR)/$(EXECNAME).app
	
$(CFILES:%=%_clean):
	rm -f $(subst _clean,.o,$@)


###
