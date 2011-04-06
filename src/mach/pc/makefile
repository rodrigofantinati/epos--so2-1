# EPOS-- PC Machine Makefile

include $(EPOS)/makedefs

OBJS := $(subst .cc,.o,$(shell find *.cc | grep -v test | grep -v init))
INITS := $(subst .cc,.o,$(shell find *.cc | grep init))
TESTS := $(subst .cc,,$(shell find *.cc | grep test))

all:		$(LIBSYS) $(LIBINIT)

$(LIBSYS):	$(LIBSYS)($(OBJS))	

$(LIBINIT):	$(LIBINIT)($(INITS))

test:		$(TESTS)

clean:
		$(CLEAN) *.o *_test
