# EPOSCC Makefile

include	$(EPOS)/makedefs

all:		install

install:	eposcc
		chmod a+x $^
		$(INSTALL) $^ $(BIN)

eposcc:		eposcc.in eposcc.conf
		$(CLEAN) $@
		sed -e '/##CONF##/ r eposcc.conf' -e '/##CONF##/ d' $< > $@ 

clean		:
		$(CLEAN) eposcc
