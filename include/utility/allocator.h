// EPOS-- Allocator Utility Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __allocator_h
#define	__allocator_h

#include <system/config.h>
#include <utility/list.h>

__BEGIN_SYS

enum {
    INCREMENTAL,
    AOFF_NC,
    AOFF_C,
    BINARY_BUDDY
};

template<int algorithm = INCREMENTAL>
class Allocator {};

__END_SYS

#endif
