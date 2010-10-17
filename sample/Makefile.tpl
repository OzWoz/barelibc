#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include ../../Makefile.config

.PHONY: all
all: $(BINDIR)/$(EXECNAME)$(APPEXT)

$(BINDIR)/$(EXECNAME)$(APPEXT): $(BINDIR)/blc_crt0.o $(CFILES:%=%.o) $(CPPFILES:%=%.o) $(LIB)
	$(LD) $(LDFLAGS) -o $@ $+

$(CFILES:%=%.o): $$(patsubst %.o,%.c,$$@) $(HFILES:%=%.h)
	$(CC) $(CFLAGS) -c -o $@ $<

$(CPPFILES:%=%.o): $$(patsubst %.o,%.cpp,$$@) $(HFILES:%=%.h)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean $(CFILES:%=%_clean) $(CPPFILES:%=%_clean)
clean: $(CFILES:%=%_clean) $(CPPFILES:%=%_clean)
	rm -f $(BINDIR)/$(EXECNAME)$(APPEXT)
	
$(CFILES:%=%_clean):
	rm -f $(subst _clean,.o,$@)

$(CPPFILES:%=%_clean):
	rm -f $(subst _clean,.o,$@)

###
