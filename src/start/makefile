# EPOS-- Startup Files Makefile

include $(EPOS)/makedefs

FILES := arch_crt1.o arch_crti.s arch_crti.o arch_crtbegin.o arch_crtend.o arch_crtn.o

all: 		$(subst arch, $(ARCH), $(FILES))
		$(INSTALL) $(subst arch, $(ARCH), $(FILES)) $(LIB)

test:

clean:
		$(CLEAN) *_crti.s *.o
