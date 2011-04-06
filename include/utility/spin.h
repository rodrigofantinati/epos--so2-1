// EPOS-- Spin Lock Utility Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __spin_h
#define __spin_h

#include <cpu.h>

__BEGIN_SYS

class Spin
{
public:
    Spin(): _lock(false) {}

    void acquire() { while(CPU::tsl(_lock)); }
    void release() { _lock = false; }

private:
    volatile bool _lock;
};

__END_SYS

#endif

