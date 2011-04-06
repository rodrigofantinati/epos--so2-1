# EPOS-- Architecture Mediators Makefile

include		$(EPOS)/makedefs

SUBDIRS := $(shell find * -maxdepth 0 -type d \! -name CVS)

all:		$(SUBDIRS)

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

test:
		make MAKE:="$(MAKETEST)" $(SUBDIRS)

clean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS)

FORCE:
