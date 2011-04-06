# EPOS-- Setup Makefile

include $(EPOS)/makedefs

all:		install

pc_setup:	$(MACH)_setup.o 
		$(LD) $(LDFLAGS) -L$(CCLIB) -N \
		--section-start $(MACH_CODE_NAME)=$(SETUP_ADDR) -o $@ $^\
		-l$(LINIT) -l$(LUTIL) -l$(LSYS) -lgcc -lc -lgcc

pc_install:	pc_setup
		$(STRIP) -o $<.img $<


install:        $(MACH)_install
		$(INSTALL) $(MACH)_setup.img $(IMG)/$(MACH)_setup
		$(CLEAN) $(MACH)_setup.img

test:

print:
		$(PRINT) $(INCLUDE)/system/memory_map.h \
		$(MACH)_setup.cc

clean:
		$(CLEAN) *.o $(MACH)_setup
		
