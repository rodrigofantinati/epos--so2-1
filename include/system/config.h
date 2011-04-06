// EPOS-- Configuration Engine
//
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.


#ifndef __config_h
#define __config_h

//============================================================================
// DEFINITIONS
//============================================================================
#define __SYS_NS		System
#define __BEGIN_SYS		namespace __SYS_NS {
#define __END_SYS		}
#define __USING_SYS		using namespace __SYS_NS;
#define __SYS(X)		::__SYS_NS::X

#define ASM                     __asm__
#define ASMV                    __asm__ __volatile__

//============================================================================
// CONFIGURATION
//============================================================================
#ifndef MACH
#define MACH                    pc
#ifndef ARCH
#define ARCH                    ia32
#endif
#endif

#define __HEADER_ARCH(X)        <arch/ARCH/X.h>
#define __HEADER_MACH(X)        <mach/MACH/X.h>

//============================================================================
// THINGS EVERBODY NEEDS
//============================================================================
//__BEGIN_SYS
//inline void * operator new(unsigned int s, void * a) { return a; }
//__END_SYS

#include <system/types.h>
#include <traits.h>
#include <system/info.h>
#include <utility/ostream.h>
#include <utility/debug.h>
#include <cpu.h>

#endif


