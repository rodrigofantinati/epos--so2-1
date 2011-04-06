# EPOS-- Application Makefile

include $(EPOS)/makedefs

all:		install

$(APPLICATION):	$(APPLICATION).o $(LIB)/*
		$(ALD) $(ALDFLAGS) -o $@ $<	

$(APPLICATION).o: $(APPLICATION).cc 
		$(ACC) $(ACCFLAGS) -o $@ $<

install: 	$(APPLICATION)
		$(STRIP) -o $(APPLICATION).tmp $<
		$(INSTALL) $(APPLICATION).tmp $(IMG)/$(APPLICATION)
		$(CLEAN) $(APPLICATION).tmp

clean:
		$(CLEAN) *.o $(APPLICATION)
