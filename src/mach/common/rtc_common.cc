// EPOS-- RTC Mediator Common Package Implementation

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <rtc.h>

__BEGIN_SYS

RTC_Common::Seconds RTC_Common::date2offset(unsigned int epoch_days, 
    unsigned int Y, unsigned int M, unsigned int D,
    unsigned int h, unsigned int m, unsigned int s)
{
    M -= 2;
    if(M < 0) { // 1..12 -> 11,12,1..10 
	M += 12;     // puts Feb last since it may have leap day
	Y -= 1;
    }
    return ((((unsigned long)(Y/4 - Y/100 + Y/400 + 367 * M/12 + D) 
	      + Y * 365 - epoch_days) * 24 + h) * 60 + m) * 60 + s;
}

void RTC_Common::offset2date(
    RTC_Common::Seconds t, unsigned int epoch_days,
    unsigned int * Y, unsigned int * M, unsigned int * D,
    unsigned int * h, unsigned int * m, unsigned int * s)
{
    static int days_per_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    *s = t % 60;
    t /= 60;
    *m = t % 60;
    t /= 60;
    *h = t % 24;
    t /= 24;
    t += epoch_days;
    for(*Y = 1; t - 365 > 0; *Y++, t -= 365)
	if(((*Y % 4 == 0) && (*Y % 100 != 0)) || (*Y % 400 == 0))
	    t--;
    days_per_month[1] = 28;
    if(((*Y % 4 == 0) && (*Y % 100 != 0)) || (*Y % 400 == 0))
	days_per_month[1] = 29;
    for(*M = 1; t - days_per_month[*M] > 0; *M++, t -= days_per_month[*M]);
    *D = t;
}

__END_SYS
