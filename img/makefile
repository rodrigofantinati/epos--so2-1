# EPOS-- Image Makefile
#
# Image layout (see command epos-mkbi):
# - boot  : skip 32 bytes header;
# - setup : skip ELF header
#           seek 512 bytes (boot)
# - kernel: seek 512 + 8K bytes (boot + setup)
# - loader: seek 512 + 8K + 32K + 16K (boot + setup + kernel + init)

include	../makedefs

all:		epos.img

epos.img:	FORCE
		$(MKBI) $@ $(APPLICATION)

install:	all

clean		:
		$(CLEAN) *_boot *_setup *_system $(APPLICATION) *.img *.o

FORCE:
