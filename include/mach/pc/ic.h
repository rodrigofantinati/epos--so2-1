// EPOS-- PC Interrupt Controller Mediator Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __pc_ic_h
#define __pc_ic_h

#include <ic.h>

__BEGIN_SYS

class PC_IC: public IC_Common
{
private:
    typedef Traits<PC_IC> Traits;
    static const Type_Id TYPE = Type<PC_IC>::TYPE;

    static const unsigned char INT_BASE = __SYS(Traits)<PC>::INT_BASE;

    // 8259A I/O Ports
    enum {
	MASTER_CMD	= 0x20,
	MASTER_IMR	= 0x21,
	SLAVE_CMD	= 0xa0,
	SLAVE_IMR	= 0xa1
    };

    // 8259A Commands
    enum {
	SELECT_IRR	= 0x0a,
	SELECT_ISR	= 0x0b,
	ICW1		= 0x11, // flank, cascaded, more ICWs
	ICW4		= 0x01,
	EOI		= 0x20
    };

public:
    // IRQs
    enum {
	IRQ0		= 0x1,
	IRQ1		= 0x2,
	IRQ2		= 0x4,
	IRQ3		= 0x8,
	IRQ4		= 0x10,
	IRQ5		= 0x20,
	IRQ6		= 0x40,
	IRQ7		= 0x80,
	IRQ8		= 0x100,
	IRQ9		= 0x200,
	IRQ10		= 0x400,
	IRQ11		= 0x800,
	IRQ12		= 0x1000,
	IRQ13		= 0x2000,
	IRQ14		= 0x4000,
	IRQ15		= 0x8000,
	IRQ_TIMER	= IRQ0,
	IRQ_KEYBOARD	= IRQ1
    };

public:
    PC_IC() {}
    ~PC_IC() {}

    static void remap(unsigned char base = INT_BASE) {
	// Configure Master PIC
	IA32::out8(MASTER_CMD, ICW1);
	IA32::out8(MASTER_IMR, base); // ICW2 is the base
	IA32::out8(MASTER_IMR, 0x04); // ICW3 = IRQ2 cascaded
	IA32::out8(MASTER_IMR, ICW4);

	// Configure Slave PIC
	IA32::out8(SLAVE_CMD, ICW1);	
	IA32::out8(SLAVE_IMR, base + 8); // ICW2 is the base	
	IA32::out8(SLAVE_IMR, 0x02);     // ICW3 = cascaded from IRQ1	
	IA32::out8(SLAVE_IMR, ICW4);  
    }
    static void enable(const Mask & mask = ALL) {
	IA32::out8(MASTER_IMR, IA32::in8(MASTER_IMR) & ~(unsigned char)mask);
	IA32::out8(SLAVE_IMR, IA32::in8(SLAVE_IMR) 
		   & ~(unsigned char)(mask >> 8));
    }
    static void disable(const Mask & mask = ALL) {
	IA32 cpu;
	IA32::out8(MASTER_IMR, IA32::in8(MASTER_IMR) | (unsigned char)mask);
	IA32::out8(SLAVE_IMR, IA32::in8(SLAVE_IMR) 
		   | (unsigned char)(mask >> 8));
    }
    static Mask pending() { // 8259A IRR
	IA32::out8(MASTER_CMD, SELECT_IRR);
	IA32::out8(SLAVE_CMD, SELECT_IRR);
	return IA32::in8(MASTER_CMD) | (IA32::in8(SLAVE_CMD) << 8);
    }
    static Mask servicing() { // 8259A ISR
	IA32::out8(MASTER_CMD, SELECT_ISR);
	IA32::out8(SLAVE_CMD, SELECT_ISR);
	return IA32::in8(MASTER_CMD) | (IA32::in8(SLAVE_CMD) << 8);
    }
    static Mask disabled() { // 8259A IMR
	return IA32::in8(MASTER_IMR) | (IA32::in8(SLAVE_IMR) << 8);
    }
    static Mask enabled() {
	return ~disabled();
    }
    static void eoi() {
	IA32::out8(MASTER_CMD, EOI); // always send EOI to master
	if((servicing() & 0x0004) != 0) // was it an slave PIC interrupt?
	    IA32::out8(SLAVE_CMD, EOI);
    }

    static int init(System_Info *si);
};

__END_SYS

#endif
