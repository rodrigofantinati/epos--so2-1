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


#RCX
rcx_boot:	rcx_boot.o
		$(LD) $(LDFLAGS) -L$(CCLIB) -N -Ttext $(BOOT_ADDR) -e $(BOOT_ADDR) \
		-o $@ $< -l$(LUTIL) -l$(LSYS) -l$(LINIT) -lc -lgcc

rcx_install:	rcx_boot
		$(OBJCPY) -O binary $< $<.img


#KHOMP
khomp_boot:	khomp_boot.o
		$(LD) $(LDFLAGS) -L$(CCLIB) -N -Ttext $(BOOT_ADDR) -e _start \
		-o $@ $< -l$(LUTIL) -l$(LSYS) -l$(LINIT) -lc -lgcc  

khomp_install:	khomp_boot
		$(OBJCPY) -O binary $< $<.img


#AT90S
at90s_boot: FORCE
		$(TOUCH) $(MACH)_boot

at90s_install:  $(MACH)_boot
		$(TOUCH) $(MACH)_boot.img


#AT86RF
at86rf_boot: FORCE
		$(TOUCH) $(MACH)_boot

at86rf_install:	$(MACH)_boot
		$(TOUCH) $(MACH)_boot.img


install:        $(MACH)_install
		$(INSTALL) $(MACH)_boot.img $(IMG)/$(MACH)_boot
		$(CLEAN) $(MACH)_boot.img

test:

clean:
		$(CLEAN) *.s *.o $(MACH)_boot *.tmp

FORCE:
