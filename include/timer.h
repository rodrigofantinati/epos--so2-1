// EPOS-- Timer Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __timer_h
#define __timer_h

#include <system/config.h>
#include <tsc.h>

__BEGIN_SYS

class Timer_Common
{
protected:
    Timer_Common() {}

public:
    typedef TSC::Hertz Tick;

protected:
    typedef TSC::Hertz Hertz;

protected:
    const Hertz & frequency() { return _frequency; }
    void frequency(const Hertz & f) { _frequency = f; }

private:
    static Hertz _frequency;
};

__END_SYS

#include __HEADER_MACH(timer)

#endif
