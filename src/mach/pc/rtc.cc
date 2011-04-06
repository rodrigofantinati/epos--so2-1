// EPOS-- PC RTC Mediator

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <mach/pc/rtc.h>

__BEGIN_SYS

PC_RTC::Seconds PC_RTC::read()
{
    unsigned int Y, M, D, h, m, s;

    do { // Get time BINARY (not BCD) components
	s = reg(SECONDS);
	m = reg(MINUTES);
	h = reg(HOURS);
	D = reg(DAY);
	M = reg(MONTH);
	Y = reg(YEAR);
    } while(s != reg(SECONDS)); // RTC update in between? read again!
    if ((Y += 1900) < _Traits::EPOCH_YEAR)
	Y += 100;

    return date2offset(_Traits::EPOCH_DAYS, Y, M, D, h, m, s);
}

void PC_RTC::write(const PC_RTC::Seconds & time)
{
    db<PC_RTC>(TRC) << "PC_RTC::write(time= " << time << ")\n";

    unsigned int Y, M, D, h, m, s;

    offset2date(time, _Traits::EPOCH_DAYS, &Y, &M, &D, &h, &m, &s);

    reg(YEAR, Y);
    reg(MONTH, M);
    reg(DAY, D);
    reg(HOURS, h);
    reg(MINUTES, m);
    reg(SECONDS, s);
}

__END_SYS
