// EPOS-- IA32_TSC Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __ia32_tsc_h
#define __ia32_tsc_h

#include <tsc.h>

__BEGIN_SYS

class IA32_TSC: public TSC_Common
{
private:
    typedef Traits<IA32_TSC> Traits;
    static const Type_Id TYPE = Type<IA32_TSC>::TYPE;

public:
    IA32_TSC() {}
    ~IA32_TSC() {}

    static Hertz frequency() { return __SYS(Traits)<IA32>::CLOCK; }
    static Time_Stamp time_stamp() {
	Time_Stamp ts;
	ASMV("rdtsc" : "=A" (ts) : ); // must be volatile!
	return ts;
    }

    static int init(System_Info * si);
};

__END_SYS

#endif
