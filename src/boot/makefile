# EPOS-- Boot Makefile

include $(EPOS)/makedefs

all: 		install

#PC
pc_boot:        pc_boot.o
		ld86 -0 -s -T $(BOOT_ADDR) -o $@ $<

pc_boot.o:      pc_boot.s
		as86 -0 -o $@ $<

pc_install:	pc_boot
		$(DD) if=$< of=$<.img ibs=32 skip=1 obs=512

install:        $(MACH)_install
		$(INSTALL) $(MACH)_boot.img $(IMG)/$(MACH)_boot
		$(CLEAN) $(MACH)_boot.img

test:

clean:
		$(CLEAN) *.s *.o $(MACH)_boot *.tmp

