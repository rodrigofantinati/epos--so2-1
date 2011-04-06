// EPOS-- PC Mediator Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __pc_h
#define __pc_h

#include <machine.h>
#include <arch/ia32/cpu.h>
#include <arch/ia32/mmu.h>
#include <arch/ia32/tsc.h>
#include "memory_map.h"
#include "pci.h"
#include "ic.h"
#include "timer.h"
#include "rtc.h"
#include "display.h"
#include "uart.h"

__BEGIN_SYS

class PC: public Machine_Common
{
private:
    typedef Traits<PC> Traits;
    static const Type_Id TYPE = Type<PC>::TYPE;

    static const int SYSCALL_INT = Traits::SYSCALL_INT;

public:
    // Interrupts
    enum {
   	INT_BASE        = Traits::INT_BASE,
        INT_TIMER       = INT_BASE + 0,
        INT_KEYBOARD    = INT_BASE + 1
    };        

public:
    PC() {}
    ~PC() {}
  
    static Handler int_handler(int i) {
	IA32::IDT_Entry * idt = (IA32::IDT_Entry *)Memory_Map<PC>::INT_VEC;
	if(i < IA32::IDT_ENTRIES)
	    return (Handler)idt[i].offset();
    }
    static void int_handler(int i, Handler h) {
	IA32::IDT_Entry * idt = (IA32::IDT_Entry *)Memory_Map<PC>::INT_VEC;
	if(i < IA32::IDT_ENTRIES)
	    idt[i] = IA32::IDT_Entry(IA32::GDT_SYS_CODE,
				     (IA32::Reg32)h,
				     IA32::SEG_IDT_ENTRY);
    }
    template <Handler h> static void handler_wrapper(){
	ASM("	cli				\n"
	    "	pushl	%eax			\n"
	    "	pushl	%ecx			\n"
	    "	pushl	%edx			\n"
	    "	pushl	%ebx			\n"
	    "	pushl	%esi			\n"
	    "	pushl	%edi			\n"
	    "	movb  $0x20, %al		\n"
	    "	outb  %al, $0x20		\n");
//	db<PC>(TRC) << "\n\nINT\n\n";
	ASM("	call  *%0			\n"
	    "	popl  %%edi			\n"
	    "	popl  %%esi			\n"
	    "	popl  %%ebx			\n"
	    "	popl  %%edx			\n"
	    "	popl  %%ecx			\n"
	    "	popl  %%eax			\n"
	    "	leave			# this may change with GCC \n"
	    "	sti				\n"
	    "	iret				\n" : : "r"(h));
    }

    static int init(System_Info * si);

public:
    IA32 cpu;
    IA32_MMU mmu;
    IA32_TSC tsc;
    PC_IC ic;
    PC_PCI pci;
    PC_Display display;
};

typedef PC Machine;

__END_SYS

#endif
