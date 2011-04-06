// EPOS-- PC Display Mediator Initialization

#include <mach/pc/display.h>

__BEGIN_SYS

int PC_Display::init(System_Info * si)
{
    db<PC_Display>(TRC) << "PC_Display::init()\n";

    return 0;
}

int PC_Serial_Display::init(System_Info * si)
{
    db<PC_Display>(TRC) << "PC_Display::init()\n";

    return 0;
}

__END_SYS


