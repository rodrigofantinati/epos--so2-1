// EPOS-- IC Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __ic_h
#define __ic_h

#include <system/config.h>

__BEGIN_SYS

class IC_Common
{
protected:
    IC_Common() {};

public:
    // Interrupt Mask
    typedef unsigned long Mask;
    enum {ALL = 0xffffffff};
};

__END_SYS

#include __HEADER_MACH(ic)

#endif
