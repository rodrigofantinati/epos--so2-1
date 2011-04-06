// EPOS-- Memory Allocation Utility Test Program

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/ostream.h>
#include <utility/string.h>
#include <utility/malloc.h>

__USING_SYS;

int main()
{
    OStream cout;

    cout << "Memory allocation test\n";
    char * cp = new char('A');
    cout << "new char('A')\t\t=> {p=" << (void *)cp << ",v=" << *cp << "}\n";
    int * ip = new int(1);
    cout << "new int(1)\t\t=> {p=" << (void *)ip << ",v=" << *ip << "}\n";
    long int * lp = new long int(1);
    cout << "new long int(1)\t\t=> {p=" << (void *)lp << ",v=" << *lp << "}\n";
    char * sp = new char[1024];
    strcpy(sp, "string");
    cout << "new char[1024]\t\t=> {p=" << (void *)sp << ",v=" << sp << "}\n";

    cout << "deleting everything!\n"; 
    delete cp;
    delete ip;
    delete lp;
    delete sp;

    cout << "and doing it all again!\n"; 
    cp = new char('A');
    cout << "new char('A')\t\t=> {p=" << (void *)cp << ",v=" << *cp << "}\n";
    ip = new int(1);
    cout << "new int(1)\t\t=> {p=" << (void *)ip << ",v=" << *ip << "}\n";
    lp = new long int(1);
    cout << "new long int(1)\t\t=> {p=" << (void *)lp << ",v=" << *lp << "}\n";
    sp = new char[1024];
    strcpy(sp, "string");
    cout << "new char[1024]\t\t=> {p=" << (void *)sp << ",v=" << sp << "}\n";

    
    return 0;
}
