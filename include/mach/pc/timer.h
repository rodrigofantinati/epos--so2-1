// EPOS-- PC Timer Mediator Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __pc_timer_h
#define __pc_timer_h

#include <timer.h>
#include <ic.h>

__BEGIN_SYS

class PC_Timer:  public Timer_Common
{
// The i8253 (i82C54) used in PCs has tree counters, but only counter 0 is
// available to the OS
private:
    typedef Traits<PC_Timer> Traits;
    static const Type_Id TYPE = Type<PC_Timer>::TYPE;

public:
    // Clock input 1.193180 MHz (for all 3 channels)
    static const int CLOCK = 1193180;

    // 8253 I/O Ports
    enum {
	CNT_0	= 0x40, // Timekeeper
	CNT_1	= 0x41, // Memory refresh
	CNT_2	= 0x42, // Speaker
	CTL	= 0x43
    };

    // 8253 Control Register Format (8 bits)
    enum {
	SELECT_MASK	= 0xc0, // Select Counter (2 bits)
	SC0		= 0x00, // counter 0
	SC1		= 0x40, // counter 1
	SC2		= 0x80, // counter 2
	RB		= 0xc0, // read-back
	RW_MASK		= 0x30, // Read/Write (2 bits)
	LATCH		= 0x00, // latch counter for reading
	MSB		= 0x10, // read/write MSB only
	LSB		= 0x20, // read/write LSB only
	LMSB		= 0x30,	// read/write LSB then MSB
	MODE_MASK	= 0x0e, // 3 bits
	IOTC		= 0x00, // Interrupt on Terminal Count
	HROS		= 0x02, // Hardware Retriggerable One-Shot
	RG		= 0x04, // Rate generator
	CSSW		= 0x06, // Continuous Symmetrical Square Wave
	STS		= 0x08, // Software Triggered Strobe
	HTS		= 0x0a, // Hardware Triggered Strobe
	COUNT_MODE_MASK	= 0x01, // 1 bit
	BINARY		= 0x00, // Binary count
	BCD		= 0x01, // BCD count
	DEF_CTL_C0	= SC0	| LMSB	| CSSW	| BINARY, // Counter 0 default
	DEF_CTL_C1	= SC1	| MSB	| RG	| BINARY, // Counter 1 default
	DEF_CTL_C2	= SC2	| LMSB	| CSSW	| BINARY  // Counter 2 default
    };

    // 8253 Default Counters as set by the BIOS (16 bits)
    enum {
	DEF_CNT_C0	= 0x0000, // CLOCK/65535 ->     18.2 Hz
	DEF_CNT_C1	= 0x0012, // CLOCK/18    ->  66287.8 Hz
	DEF_CNT_C2	= 0x0533, // CLOCK/1331  ->    896.5 Hz
    };

public:
    PC_Timer(int u = 0) {} // actual initialization is up to init
    ~PC_Timer() {}

    Hertz frequency() { return Timer_Common::frequency(); }
    void frequency(const Hertz & f) {
	unsigned short count = freq2cnt(f);
	// Convert back to avoid precision lost
	Timer_Common::frequency(cnt2freq(count));
	IA32::out8(CTL, DEF_CTL_C0);
	IA32::out8(CNT_0, count & 0xff);
	IA32::out8(CNT_0, count >> 8);
	db<PC_Timer>(INF) << "PC_Timer::resolution(res=" << frequency()
			  << ",cnt=" << count << ")\n";
    }
    
    void enable() { PC_IC::enable(PC_IC::IRQ_TIMER); }
    void disable() { PC_IC::disable(PC_IC::IRQ_TIMER); }

    void reset() {
        // 8253 doesn't feature a reset, but a counter can be reset by writing
        // the corresponding control register
        IA32::out8(CTL, DEF_CTL_C0);
	unsigned short count = IA32::in8(CNT_0) | (IA32::in8(CNT_0) << 8);
        IA32::out8(CNT_0, count & 0xff);
        IA32::out8(CNT_0, count >> 8);
    }

    static int init(System_Info * si);

private:
    static Hertz cnt2freq(unsigned short c) { return CLOCK / c; }
    static unsigned short freq2cnt(const Hertz & f) { return CLOCK / f; }
};

__END_SYS

#endif
