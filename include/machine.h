// EPOS-- Machine Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __machine_h
#define __machine_h

#include <system/config.h>

__BEGIN_SYS

class Machine_Common
{
protected:
    Machine_Common() {}

public:
    typedef void (* Handler)(void);
};

__END_SYS

#include __HEADER_MACH(MACH)

#endif
