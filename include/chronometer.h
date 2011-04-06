// EPOS-- Chronometer Abstraction Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __chronometer_h
#define __chronometer_h

#include <system/config.h>
#include <tsc.h>
#include <rtc.h>

__BEGIN_SYS

class Chronometer
{
private:
    typedef Traits<Chronometer> Traits;
    static const Type_Id TYPE = Type<Chronometer>::TYPE;

    typedef TSC::Hertz Hertz;
    typedef TSC::Time_Stamp Time_Stamp;
    typedef RTC::Microseconds Microseconds;

public:
//    Chronometer(const Id & id) {}
//    Chronometer(const Chronometer & obj) {}
    Chronometer() : _start(0), _stop(0) {}
    ~Chronometer() {}

//    const Id & id();
//    bool valid();
    
    Hertz frequency() { return tsc.frequency(); }

    void reset() { _start = 0; _stop = 0; }
    void start() { if(_start == 0) _start = tsc.time_stamp(); }
    void lap()   { if(_start != 0) _stop = tsc.time_stamp(); }
    void stop()  { lap(); }

    Time_Stamp ticks() {
	if(_start == 0)
	    return 0;
	if(_stop == 0)
	    return tsc.time_stamp() - _start;
	return _stop - _start;
    }
    Microseconds read() { return ticks() * 1000000 / frequency(); }

    static int init(System_Info *si);

private:
    TSC tsc;
    Time_Stamp _start;
    Time_Stamp _stop;
};

__END_SYS

#endif
