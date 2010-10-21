#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

include ../../Makefile.config

.PHONY: all
all: copyinc $(BINCOPY:%=$(BINDIR)/%) $(CFILES:%=%.o) $(ASMFILES:%=%.o) $(CFILES:%=%_lib) $(ASMFILES:%=%_lib)

.PHONY: copyinc
copyinc: $(if $(HEADERNAME),$(INCDIR)/$(HEADERNAME).h) $(INCCOPY:%=$(INCDIR)/%)

$(INCDIR)/$(HEADERNAME).h: $(HEADERNAME).h
	cp $< $@

$(BINCOPY:%=$(BINDIR)/%): $$(subst $(BINDIR)/,,$$@)
	cp $< $@

$(INCCOPY:%=$(INCDIR)/%): $$(subst $(INCDIR)/,,$$@)
	cp $< $@

$(CFILES:%=%.o): $$(patsubst %.o,%.c,$$@) $(DEPFILES) $$(DEPFILES_$$(patsubst %.o,%,$$@)) $(if $(HEADERNAME),$(INCDIR)/$(HEADERNAME).h)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: $(CFILES:%=%_lib)
$(CFILES:%=%_lib): $$(subst _lib,.o,$$@) 
	$(AR) $(ARFLAGS) $(LIB) $<

$(ASMFILES:%=%.o): $$(patsubst %.o,%.asm,$$@)
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: $(ASMFILES:%=%_lib)
$(ASMFILES:%=%_lib): $$(subst _lib,.o,$$@) 
	$(AR) $(ARFLAGS) $(LIB) $<

.PHONY: clean $(CFILES:%=%_clean) $(BINCOPY:%=$(BINDIR)/%_clean) $(INCCOPY:%=$(INCDIR)/%_clean) $(CLEANFILES:%=%_clean)
clean: $(CFILES:%=%_clean) $(ASMFILES:%=%_clean) $(BINCOPY:%=$(BINDIR)/%_clean) $(INCCOPY:%=$(INCDIR)/%_clean) $(CLEANFILES:%=%_clean)
	$(if $(HEADERNAME),rm -f $(INCDIR)/$(HEADERNAME).h)
	
$(CFILES:%=%_clean):
	rm -f $(subst _clean,.o,$@)

$(ASMFILES:%=%_clean): 
	rm -f $(subst _clean,.o,$@)

$(BINCOPY:%=$(BINDIR)/%_clean):
	rm -f $(subst _clean,,$@)

$(INCCOPY:%=$(INCDIR)/%_clean):
	rm -f $(subst _clean,,$@)

$(CLEANFILES:%=%_clean):
	rm -f $(subst _clean,,$@)
	
###
