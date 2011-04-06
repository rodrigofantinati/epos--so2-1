// EPOS-- RTC Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __rtc_h
#define __rtc_h

#include <system/config.h>

__BEGIN_SYS

class RTC_Common
{
protected:
    RTC_Common() {}

public:
    // The time (as defined by God Chronos)
    typedef unsigned long Microseconds;
    typedef unsigned long Seconds;

protected:
    static Seconds date2offset(unsigned int epoch_days,
			       unsigned int Y, unsigned int M, 
			       unsigned int D, unsigned int h,
			       unsigned int m, unsigned int s);
    static void offset2date(Seconds t,  unsigned int epoch_days,
			    unsigned int * Y, unsigned int * M,
			    unsigned int * D, unsigned int * h,
			    unsigned int * m, unsigned int * s);
};

__END_SYS

#include __HEADER_MACH(rtc)

#endif
