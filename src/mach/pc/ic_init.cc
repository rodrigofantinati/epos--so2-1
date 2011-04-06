// EPOS-- PC Interrupt Controller Initialization

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <mach/pc/ic.h>

__BEGIN_SYS

int PC_IC::init(System_Info * si)
{
    db<PC_IC>(TRC) << "PC_IC::init()\n";

    PC_IC ic;

    ic.remap();
    ic.disable();

    return 0;
}

__END_SYS
