// EPOS-- Initializer Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __initializer_h
#define __initializer_h

#include <system/config.h>

// Threads are handled latter (they can activate the sched.)
#define __LAST_INIT (Initializer::Dispatcher *)-1
#define INIT_TABLE {\
    &CPU::init, \
    &TSC::init, \
    &MMU::init, \
    &Machine::init, \
    &PCI::init, \
    &IC::init, \
    &Timer::init, \
    &RTC::init, \
    &Display::init, \
    &Address_Space::init, \
    &Segment::init, \
    &Mutex::init, \
    &Semaphore::init, \
    &Condition::init, \
    &Alarm::init, \
    &Clock::init, \
    &Chronometer::init, \
    __LAST_INIT \
} 

__BEGIN_SYS

class Initializer
{
private:
    typedef int (Dispatcher) (System_Info * );
    typedef void (Function)(void);

public:
    Initializer(System_Info * si);

private:
    static Dispatcher * init_table[];
};

__END_SYS

#endif
