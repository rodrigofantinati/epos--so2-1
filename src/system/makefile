# EPOS-- System Makefile

include $(EPOS)/makedefs

all:		install

$(MACH)_system_kernel: initializer.o system.o $(LIBSYS)
		$(LD) $(LDFLAGS) -L$(CCLIB) \
		-n -Ttext $(SYS_CODE_ADDR) -Tdata $(SYS_DATA_ADDR) \
		-e $(SYS_CODE_ADDR) -o $(MACH)_system $< -l$(LSYS) \
		-l$(LUTIL) -lc -lgcc

$(MACH)_system_builtin: initializer.o system.o $(LIBSYS)
		$(LD) $(LDFLAGS) -L$(CCLIB) -n  \
		--section-start $(MACH_CODE_NAME)=$(SYS_CODE_ADDR) \
		--section-start $(MACH_DATA_NAME)=$(SYS_DATA_ADDR) \
		--entry=_init -o $(MACH)_system \
		$(EPOS)/lib/$(ARCH)_crti.o \
		$(EPOS)/lib/$(ARCH)_crtbegin.o \
		initializer.o system.o \
		$(EPOS)/lib/$(ARCH)_crtend.o \
		$(EPOS)/lib/$(ARCH)_crtn.o \
		-l$(LINIT) -l$(LSYS) -l$(LUTIL) -lgcc -lc -lgcc		

$(MACH)_system_library: initializer.o system.o $(LIBSYS)
		$(TOUCH) $(MACH)_system


$(MACH)_install_kernel: $(MACH)_system_kernel
		$(STRIP) -o $(MACH)_system.img $(MACH)_system

$(MACH)_install_builtin: $(MACH)_system_builtin
		$(STRIP) -o $(MACH)_system.img $(MACH)_system

$(MACH)_install_library: $(MACH)_system_library
		$(TOUCH) $(MACH)_system.img


install:        $(MACH)_install_$(MODE)
		$(INSTALL) $(MACH)_system.img $(IMG)/$(MACH)_system
		$(CLEAN) $(MACH)_system.img
test:

clean:
		$(CLEAN) *.o $(MACH)_system

FORCE:
