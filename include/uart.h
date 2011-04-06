// EPOS-- UART Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __uart_h
#define __uart_h

#include <system/config.h>

__BEGIN_SYS

class UART_Common
{
protected:
    UART_Common() {}

public:
    enum Baud_Rate {
      B1200 = 1200,
      B2400 = 2400,
      B4800 = 4800,
      B9600 = 9600,
      B19200 = 19200,
      B28800 = 28800,
      B33600 = 33600,
      B57600 = 57600,
      B115200 = 115200
    };
    enum Data_Bits {
      D5 = 5,
      D6 = 6,
      D7 = 7,
      D8 = 8
    };
    enum Parity {
      NO_PARITY = 0,
      EVEN_PARITY = 1,
      ODD_PARITY = 2
    };
    enum Stop_Bits {
      ONE_STOP_BIT = 1,
      ONE_HALF_STOP_BITS = 2,
      TWO_STPO_BITS = 3
    };
};

__END_SYS

#include __HEADER_MACH(uart)

#endif
