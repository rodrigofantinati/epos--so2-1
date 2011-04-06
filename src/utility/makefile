# EPOS-- Utilities Makefile

include $(EPOS)/makedefs

OBJS := $(subst .cc,.o,$(shell find *.cc | grep -v test))
TESTS := $(subst .cc,,$(shell find *.cc | grep test))

all:		$(LIBUTIL)

$(LIBUTIL):	$(LIBUTIL)($(OBJS))	


test:		$(TESTS)

clean:
		$(CLEAN) *.o *_test
