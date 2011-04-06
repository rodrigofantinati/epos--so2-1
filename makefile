# EPOS-- Main Makefile

include $(EPOS)/makedefs

SUBDIRS := tools src app

all:		linux_imports $(SUBDIRS) img

linux_imports:	FORCE
		$(TCPP) $(TCPPFLAGS) -dD -P /usr/include/elf.h | \
			grep -v __ | $(SED) \
			-e s/'typedef int int32_t'/'typedef long int32_t'/g \
			-e s/'typedef unsigned int uint32_t'/'typedef unsigned long uint32_t'/g \
			-e s/'typedef int int_least32_t'/'typedef long int_least32_t'/g \
			-e s/'typedef unsigned int uint_least32_t'/'typedef unsigned long uint_least32_t'/g \
			-e s/'typedef int int_fast16_t'/'typedef long int_fast16_t'/g \
			-e s/'typedef int int_fast32_t'/'typedef long int_fast32_t'/g \
			-e s/'typedef unsigned int uintptr_t'/'typedef unsigned long uintptr_t'/g >! $(INCLUDE)/utility/elf-linux.h
		$(TCPP) $(TCPPFLAGS) -dD -P /usr/include/linux/pci_ids.h | \
			grep -v __ >! $(INCLUDE)/system/pci_ids-linux.h

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

img:		FORCE
		(cd $@ && $(MAKE))

test:		all
		(cd src && $(MAKETEST))

clean:		FORCE
		(cd src && $(MAKECLEAN))
		find $(LIB) -maxdepth 1 -type f -exec $(CLEAN) {} \;

veryclean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS) img
		$(CLEAN) $(INCLUDE)/utility/elf-linux.h
		$(CLEAN) $(INCLUDE)/mediator/pci/pci_ids-linux.h
		find $(LIB) -maxdepth 1 -type f -exec $(CLEAN) {} \;
		find $(BIN) -maxdepth 1 -type f -exec $(CLEAN) {} \;
		find $(IMG) -name "*.app" -exec $(CLEAN) {} \;
		find $(EPOS) -name "*~" -exec $(CLEAN) {} \; 

distclean:	veryclean
		find $(EPOS) -name CVS -type d -print | xargs $(CLEANDIR)

FORCE:
