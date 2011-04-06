// EPOS-- TSC Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __tsc_h
#define __tsc_h

#include <system/config.h>

__BEGIN_SYS

class TSC_Common
{
protected:
    TSC_Common() {}

public:
    typedef unsigned long Hertz;
    typedef unsigned long long Time_Stamp;
};

__END_SYS

#include __HEADER_ARCH(tsc)

#endif
