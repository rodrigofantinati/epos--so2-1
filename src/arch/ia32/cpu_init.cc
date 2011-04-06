// EPOS IA32 Initialization
//
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

// Author: Guto
// Documentation: $EPOS/doc/cpu			Date: 15 Jun 2003

#include <arch/ia32/cpu.h>

__BEGIN_SYS

// Class initialization
int IA32::init(System_Info * si)
{
    db<IA32>(TRC) << "IA32::init()\n";

    return 0;
}

__END_SYS
