# EPOS-- Tools Makefile

include	$(EPOS)/makedefs

SUBDIRS := $(shell find * -maxdepth 0 -type d \! -name CVS)

all:		$(SUBDIRS)

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

clean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS)

FORCE:
