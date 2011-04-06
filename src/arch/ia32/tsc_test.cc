// EPOS-- IA32_TSC Test Program

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/ostream.h>
#include <tsc.h>

using namespace System;

int main()
{
    OStream cout;

    cout << "IA32_TSC test\n";

    IA32_TSC tsc;

    return 0;
}
