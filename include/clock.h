// EPOS-- Clock Abstraction Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __timepiece_h
#define __timepiece_h

#include <system/config.h>
#include <rtc.h>

__BEGIN_SYS

class Clock
{
private:
    typedef Traits<Clock> Traits;
    static const Type_Id TYPE = Type<Clock>::TYPE;

    typedef RTC::Microseconds Microseconds;
    typedef RTC::Seconds Seconds;

public:
//    Clock(const Id & id) {}
//    Clock(const Clock & obj) {}
    Clock() {}
    ~Clock() {}

//    const Id & id();
//    bool valid();

    Microseconds resolution() { return 1000000; }

    Seconds now() { RTC rtc; return rtc.read(); }

    static int init(System_Info * si);
};

__END_SYS

#endif
