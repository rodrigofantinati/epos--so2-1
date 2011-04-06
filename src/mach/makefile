# EPOS-- Machine Mediators Makefile

include		$(EPOS)/makedefs

SUBDIRS := common $(shell find * -maxdepth 0 -type d \! -name common \! -name CVS)

all:		$(SUBDIRS)

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

test:
		make MAKE:="$(MAKETEST)" $(SUBDIRS)

clean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS)

FORCE:
