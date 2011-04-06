// EPOS-- Condition Variable Abstraction Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __condition_h
#define __condition_h

#include <common/synchronizer.h>

__BEGIN_SYS

class Condition: public Synchronizer_Common
{
private:
    typedef Traits<Condition> Traits;
    static const Type_Id TYPE = Type<Condition>::TYPE;

public:
    Condition() : _not_condition(true), _broadcast(0), _time_stamp(1) {
	db<Condition>(TRC) << "Condition()\n";
    }
    ~Condition() {
	db<Condition>(TRC) << "~Condition()\n";
    }

    void wait() {
	db<Condition>(TRC) << "Condition::wait()\n";
	int ts = inc(_time_stamp);
	while(tsl(_not_condition) && (ts <= _broadcast))
	    sleep();
    }
    void signal() {
	db<Condition>(TRC) << "Condition::signal()\n";
	_not_condition = false;
	wakeup();
    }
    void broadcast() {
	db<Condition>(TRC) << "Condition::broadcast()\n";
	_broadcast = _time_stamp;
	wakeup_all();
    }

    static int init(System_Info * si);

private:
    volatile bool _not_condition;
    volatile int _broadcast;
    volatile int _time_stamp;
};

__END_SYS

#endif
