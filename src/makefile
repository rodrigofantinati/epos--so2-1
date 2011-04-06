# EPOS-- Source Makefile

include	$(EPOS)/makedefs

SUBDIRS := utility start arch mach abstraction boot setup system
INSSUBDIRS := start boot setup system

all:		$(SUBDIRS)

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

test:
		make MAKE:="$(MAKETEST)" $(SUBDIRS)

clean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS)

FORCE:
