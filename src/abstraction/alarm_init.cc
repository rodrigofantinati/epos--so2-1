// EPOS-- Alarm Abstraction Initialization

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <alarm.h>
#include <machine.h>

__BEGIN_SYS

int Alarm::init(System_Info * si)
{
    db<Alarm>(TRC) << "Alarm::init()\n";

    CPU::int_disable();

    Machine::int_handler(Machine::INT_TIMER,
			 &Machine::handler_wrapper<timer_handler>);

    _timer.frequency(FREQUENCY);
    _timer.enable();

    CPU::int_enable();
    return 0;
}

__END_SYS
