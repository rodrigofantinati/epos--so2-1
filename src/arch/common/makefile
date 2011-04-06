# EPOS-- Architecture Common Packages Makefile

include $(EPOS)/makedefs

OBJS := $(subst .cc,.o,$(shell find *.cc))

all:		$(LIBSYS)

$(LIBSYS):	$(LIBSYS)($(OBJS))	

test:		

clean:
		$(CLEAN) *.o
