// EPOS-- IA32 Test Program

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/ostream.h>
#include <cpu.h>

__USING_SYS

int main()
{
    OStream cout;
    cout << "IA32 test\n";

    IA32 cpu;

    {
	volatile bool lock = false;
	if(cpu.tsl(lock))
	    cout << "tsl(): doesn't function properly!\n";
	else
	    if(cpu.tsl(lock))
		cout << "tsl(): ok\n";
	    else
		cout << "tsl(): doesn't function properly!\n";
    }
    {
	volatile int number = 100;
	volatile int tmp;
	if((tmp = cpu.finc(number)) != 100)
	    cout << "finc(): doesn't function properly (n=" << tmp
		 << ", should be 100)!\n";
	else
	    if((tmp = cpu.finc(number)) != 101)
		cout << "finc(): doesn't function properly (n=" << tmp 
		     << ", should be 101)!\n";
	    else
		cout << "finc(): ok\n";
    }
    {
	volatile int number = 100;
	volatile int tmp;
	if((tmp = cpu.fdec(number)) != 100)
	    cout << "fdec(): doesn't function properly (n=" << tmp
		 << ", should be 100)!\n";
	else
	    if((tmp = cpu.fdec(number)) != 99)
		cout << "fdec(): doesn't function properly (n=" << tmp 
		     << ", should be 99)!\n";
	    else
		cout << "fdec(): ok\n";
    }


    cout << "IA32 test finished\n";
    return 0;
}
