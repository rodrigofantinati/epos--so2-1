# Mkebi Makefile

include	$(EPOS)/makedefs

all		: install

epos-mkbi	: epos-mkbi.cc
		$(TCXX) $(TCXXFLAGS) $<
		$(TLD) $(TLDFLAGS) -o $@ epos-mkbi.o

install		: epos-mkbi
		$(INSTALL) $^ $(BIN)

clean		:
		$(CLEAN) *.o epos-mkbi
