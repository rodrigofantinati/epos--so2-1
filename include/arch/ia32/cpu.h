// EPOS-- IA32 Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __ia32_h
#define __ia32_h

#include <cpu.h>
#include <utility/debug.h>

__BEGIN_SYS

class IA32: public CPU_Common
{
private:
    typedef Traits<IA32> _Traits;
    static const Type_Id _TYPE = Type<IA32>::TYPE;

public:
    // I/O ports
    typedef Reg16 IO_Port;
    typedef Reg16 IO_Irq;

    // CPU Flags
    typedef Reg32 Flags;
    enum {
	FLAG_CF		= 0x00000001,
	FLAG_PF		= 0x00000004,
	FLAG_AF		= 0x00000010,
	FLAG_ZF		= 0x00000040,
	FLAG_SF		= 0x00000080,
	FLAG_TF		= 0x00000100,
	FLAG_IF		= 0x00000200,
	FLAG_DF		= 0x00000400,
	FLAG_OF		= 0x00000800,
	FLAG_IOPL1	= 0x00001000,
	FLAG_IOPL2	= 0x00002000,
	FLAG_NT		= 0x00004000,
	FLAG_RF		= 0x00010000,
	FLAG_VM		= 0x00020000,
	FLAG_AC		= 0x00040000,
	FLAG_VIF	= 0x00080000,
	FLAG_VIP	= 0x00100000,
	FLAG_ID		= 0x00200000,
	FLAG_DEFAULTS   = FLAG_IF,
	// Mask to clear flags (by ANDing)
	FLAG_CLEAR      = ~(FLAG_TF | FLAG_IOPL1 | FLAG_IOPL2 | FLAG_NT |
			    FLAG_RF | FLAG_VM | FLAG_AC)
    };

    // Exceptions
    enum Exceptions {
	EXC_DIV0	= 0x00,
	EXC_DEBUG	= 0x01,
	EXC_NMI		= 0x02,
	EXC_BP		= 0x03,
	EXC_OVFLOW	= 0x04,
	EXC_BOUND	= 0x05,
	EXC_INVOP	= 0x06,
	EXC_NODEV	= 0x07,
	EXC_DOUBLE	= 0x08,
	EXC_FPU_OR	= 0x09,
	EXC_INVTSS	= 0x0a,
	EXC_NOTPRE	= 0x0b,
	EXC_STACK	= 0x0c,
	EXC_GPF		= 0x0d,
	EXC_PF		= 0x0e,
	EXC_RESERV	= 0x0f,
	EXC_FPU		= 0x10,
	EXC_ALIGN	= 0x11,
	EXC_BUS		= 0x12,
	EXC_LAST	= 0x1f
    };

    // CR0 Flags
    enum {
	CR0_PE		= 0x00000001,
	CR0_MP		= 0x00000002,
	CR0_EM		= 0x00000004,
	CR0_TS		= 0x00000008,
	CR0_ET		= 0x00000010,
	CR0_NE		= 0x00000020,
	CR0_WP		= 0x00010000,
	CR0_AM		= 0x00040000,
	CR0_NW		= 0x20000000,
	CR0_CD		= 0x40000000,
	CR0_PG		= 0x80000000,
	// Mask to clear flags (by ANDing)
	CR0_CLEAR       = (CR0_PE | CR0_EM | CR0_TS | CR0_NE | CR0_AM |
			   CR0_NW | CR0_CD), 
	// Mask to set flags (by ORing)
	CR0_SET         = (CR0_PE | CR0_MP | CR0_ET | CR0_PG) 
    };

    // Segment Flags
    enum {
	SEG_ACC		= 0x01,
	SEG_RW		= 0x02,
	SEG_CONF	= 0x04,
	SEG_CODE	= 0x08,
	SEG_NOSYS 	= 0x10,
	SEG_DPL1	= 0x20,
	SEG_DPL2	= 0x40,
	SEG_PRE		= 0x80,
	SEG_TSS		= 0x09,
	SEG_INT		= 0x0e,
	SEG_TRAP	= 0x0f,
	SEG_32		= 0x40,
	SEG_4K		= 0x80,
	SEG_FLT_CODE    = (SEG_PRE  | SEG_NOSYS	| SEG_CODE | SEG_ACC),
	SEG_FLT_DATA    = (SEG_PRE  | SEG_NOSYS	| SEG_RW   | SEG_ACC),
	SEG_APP_CODE    = (SEG_PRE  | SEG_NOSYS | SEG_DPL2 | SEG_DPL1 |
			   SEG_CODE | SEG_ACC),     // P, DPL=3, S, C, W, A
	SEG_APP_DATA    = (SEG_PRE  | SEG_NOSYS	| SEG_DPL2 | SEG_DPL1 |
			   SEG_RW   | SEG_ACC),    // P, DPL=3, S, W, A
	SEG_SYS_CODE    = (SEG_PRE  | SEG_NOSYS	| SEG_CODE | SEG_ACC),
	SEG_SYS_DATA    = (SEG_PRE  | SEG_NOSYS	| SEG_RW   | SEG_ACC),
	SEG_IDT_ENTRY   = (SEG_PRE  | SEG_INT   | SEG_DPL1 | SEG_DPL2)
    };

    // DPL/RPL for application (user) and system (supervisor) modes 
    enum {
	PL_APP = 3, // GDT, RPL=3
	PL_SYS = 0  // GDT, RPL=0
    };

    // GDT Layout 
    enum GDT_Layout {
	GDT_NULL      = 0,
	GDT_FLT_CODE  = 1,
	GDT_FLT_DATA  = 2,
	GDT_APP_CODE  = 3,
	GDT_APP_DATA  = 4,
	GDT_APP_STACK =	5,	// not used for now
	GDT_SYS_CODE  =	6,
	GDT_SYS_DATA  =	7,
	GDT_SYS_STACK =	8,	// not used for now   
	GDT_LAST      = 8
    };

    // GDT Selectors
    enum {
	SEL_FLT_CODE  = (GDT_FLT_CODE << 3)  | PL_SYS,
	SEL_FLT_DATA  = (GDT_FLT_DATA << 3)  | PL_SYS,
	SEL_APP_CODE  = (GDT_APP_CODE << 3)  | PL_APP,
	SEL_APP_DATA  = (GDT_APP_DATA << 3)  | PL_APP,
	SEL_APP_STACK = (GDT_APP_STACK << 3) | PL_APP,
	SEL_SYS_CODE  = (GDT_SYS_CODE << 3)  | PL_SYS,
	SEL_SYS_DATA  = (GDT_SYS_DATA << 3)  | PL_SYS,
	SEL_SYS_STACK = (GDT_SYS_STACK << 3) | PL_SYS
    };

    // GDT Entry
    class GDT_Entry {
    public:
	GDT_Entry() {}
	GDT_Entry(Reg32 b, Reg32 l, Reg8 f)
	    : limit_15_00((Reg16)l),
	      base_15_00((Reg16)b),
	      base_23_16((Reg8)(b >> 16)),
	      p_dpl_s_type(f),
	      g_d_0_a_limit_19_16(((f & SEG_NOSYS)?SEG_4K | SEG_32 : 0) |
				  ((Reg8)(l >> 16))),
	      base_31_24((Reg8)(b >> 24)) {}

	friend Debug & operator << (Debug & db, const GDT_Entry & g) {
	    db << "{bas=" << (void *)((g.base_31_24 << 24) | 
				      (g.base_23_16 << 16) |
				      g.base_15_00) 
	       << ",lim=" << (void *)(((g.g_d_0_a_limit_19_16 & 0xf) << 16) |
				      g.limit_15_00)
	       << ",p=" << (g.p_dpl_s_type >> 7) 
	       << ",dpl=" << ((g.p_dpl_s_type >> 5) & 0x3)
	       << ",s=" << ((g.p_dpl_s_type >> 4) & 0x1)
	       << ",typ=" << (g.p_dpl_s_type & 0xf)
	       << ",g=" << (g.g_d_0_a_limit_19_16 >> 7) 
	       << ",d=" << ((g.g_d_0_a_limit_19_16 >> 6) & 0x1)
	       << ",a=" << ((g.g_d_0_a_limit_19_16 >> 4) & 0x1) << "}";
	    return db;
	}

    private:
	Reg16 limit_15_00;
	Reg16 base_15_00;
	Reg8  base_23_16;
	Reg8  p_dpl_s_type;
	Reg8  g_d_0_a_limit_19_16;
	Reg8  base_31_24;
    };

    // IDT Entry
    class IDT_Entry {
    public:
	IDT_Entry() {}
	IDT_Entry(Reg16 s, Reg32 o, Reg16 f)
	    : offset_15_00((Reg16)o),
	      selector(s << 3),
	      zero(0),
	      p_dpl_0_d_1_1_0(f),
	      offset_31_16((Reg16)(o >> 16)) {}

	Reg32 offset() const { return (offset_31_16 << 16) | offset_15_00; }

	friend Debug & operator << (Debug & db, const IDT_Entry & i) {
	    db << "{sel=" << (i.selector >> 3) 
	       << ",off=" << (void *)i.offset()
	       << ",p=" << (i.p_dpl_0_d_1_1_0 >> 7) 
	       << ",dpl=" << ((i.p_dpl_0_d_1_1_0 >> 5) & 0x3)
	       << ",d=" << ((i.p_dpl_0_d_1_1_0 >> 4) & 0x1) << "}";
	    return db;
	}

    private:
	Reg16 offset_15_00;
	Reg16 selector;
	Reg8  zero;
	Reg8  p_dpl_0_d_1_1_0;
	Reg16 offset_31_16;
    };
    static const int IDT_ENTRIES = 256;

    // TSS no longer used, since software context switch is faster
    // it's left here for reference
    struct TSS {
	Reg16 back_link;
	Reg16 zero1;
	Reg32 esp0;
	Reg16 ss0;
	Reg16 zero2;
	Reg32 esp1;
	Reg16 ss1;
	Reg16 zero3;
	Reg32 esp2;
	Reg16 ss2;
	Reg16 zero4;
	Reg32 pdbr;
	Reg32 eip;
	Reg32 eflags;
	Reg32 eax;
	Reg32 ecx;
	Reg32 edx;
	Reg32 ebx;
	Reg32 esp;
	Reg32 ebp;
	Reg32 esi;
	Reg32 edi;
	Reg16 es;
	Reg16 zero5;
	Reg16 cs;
	Reg16 zero6;
	Reg16 ss;
	Reg16 zero7;
	Reg16 ds;
	Reg16 zero8;
	Reg16 fs;
	Reg16 zero9;
	Reg16 gs;
	Reg16 zero10;
	Reg16 ldt;
	Reg16 zero11;
	Reg16 zero12;
	Reg16 io_bmp;
    };

    // CPU Context
    class Context {
    public:
	Context(Log_Addr entry)
	    : _edi(6), _esi(5), _ebp(7), _esp((Reg32)this), _ebx(2), _edx(4), 
	      _ecx(3), _eax(1), _eflags(FLAG_DEFAULTS), _eip(entry) {}
	Context(Reg32 eflags, Reg32 eax, Reg32 ebx, Reg32 ecx, Reg32 edx, 
		Reg32 esi, Reg32 edi, Reg32 ebp, Reg32 esp, Reg32 eip)
	    : _edi(edi), _esi(esi), _ebp(ebp), _esp(esp), _ebx(ebx), 
	      _edx(edx), _ecx(ecx), _eax(eax), _eflags(eflags), _eip(eip) {}

	void save() volatile;
	void load() const volatile;

	friend Debug & operator << (Debug & db, const Context & c) {
	    db << "{eflags=" << (void *)c._eflags
	       << ",eax=" << c._eax
	       << ",ebx=" << c._ebx
	       << ",ecx=" << c._ecx
	       << ",edx=" << c._edx
	       << ",esi=" << c._esi
	       << ",edi=" << c._edi
	       << ",ebp=" << (void *)c._ebp
	       << ",esp=" << (void *)c._esp
	       << ",eip=" << (void *)c._eip
	       << ",cs=" << cs()
	       << ",ds=" << ds()
	       << ",es=" << es()
	       << ",fs=" << fs()
	       << ",gs=" << gs()
	       << ",ss=" << ss()
	       << ",pdp=" << (void *)pdp()
	       << "}" ;
	    return db;
	}

    private:
	Reg32 _edi;
	Reg32 _esi;
	Reg32 _ebp;
	Reg32 _esp;
	Reg32 _ebx;
	Reg32 _edx;
	Reg32 _ecx;
	Reg32 _eax;
	Reg32 _eflags;
	Reg32 _eip;
    };

public:
    IA32() {}
    ~IA32() {}

    static Hertz clock() { return _Traits::CLOCK; }

    static void int_enable() { ASMV("sti"); }
    static void int_disable() { ASMV("cli"); }
    static void halt() { ASMV("hlt"); }

    static void switch_context(Context * volatile * o, Context * volatile n);

    static Flags flags() { return eflags(); }
    static void flags(Flags flags) { eflags(flags); }

    static Reg32 sp() { return esp(); }
    static void sp(Reg32 sp) { esp(sp); }

    static Reg32 fr() { return eax(); }
    static void fr(Reg32 sp) { eax(sp); }

    static Reg32 pdp() { return cr3() ; }
    static void pdp(Reg32 pdp) { cr3(pdp); }

    static Log_Addr ip() { return eip(); }

    static bool tsl(volatile bool & lock) {
	register bool old = 1;
	ASMV("xchg %0, %2" : "=a"(old) : "a"(old), "m"(lock)); return old;
    }
    static int finc(volatile int & number) {
	register int old = 1;
	ASMV("lock\n"
	     "xadd %0, %2" : "=a"(old) : "a"(old), "m"(number)); return old;
    }
    static int fdec(volatile int & number) {
	register int old = -1;
	ASMV("lock\n"
	     "xadd %0, %2" : "=a"(old) : "a"(old), "m"(number)); return old;
    }

    static Reg32 htonl(Reg32 v)	{
	ASMV("bswap %0" : "=r" (v) : "0" (v), "r" (v)); return v;
    }
    static Reg16 htons(Reg16 v)	{
	return htons_lsb(v);
    }
    static Reg32 ntohl(Reg32 v)	{
	return htonl(v);
    }
    static Reg16 ntohs(Reg16 v)	{
	return htons(v);
    }

    static Flags eflags() {
	Reg32 value; ASMV("pushfl");
	ASMV("popl %0" : "=r"(value) :); return value;
    }
    static void eflags(Flags value) {
	 ASMV("pushl %0" : : "r"(value)); ASMV("popfl");
    }

    static Reg32 esp() {
	Reg32 value; ASMV("movl %%esp,%0" : "=r"(value) :); return value;
    }
    static void esp(Reg32 value) {
 	ASMV("movl %0,%%esp" : : "r"(value));
    }

    static Reg32 eax() {
	Reg32 value; ASMV("movl %%eax,%0" : "=r"(value) :); return value;
    }
    static void eax(Reg32 value) {
 	ASMV("movl %0,%%eax" : : "r"(value));
    }

    static Log_Addr eip() {
	Log_Addr value;
	ASMV("	call	1f			\n"
	     "1:	movl	(%%esp), %0	\n"
	     "	addl	$4, %%esp" : "=r"(value) : );
	return value;
    }

    static Reg32 cr0() {
	Reg32 value; ASMV("movl %%cr0,%0" : "=r"(value) :); return value;
    }
    static void cr0(Reg32 value) {
	ASMV("movl %0,%%cr0" : : "r"(value));
    }

    static Reg32 cr2()	{
	Reg32 value; ASMV("movl %%cr2,%0" : "=r"(value) :); return value;
    }

    static Reg32 cr3() {
	Reg32 value; ASMV("movl %%cr3,%0" : "=r"(value) :); return value;
    }
    static void cr3(Reg32 value) {
	ASMV("movl %0,%%cr3" : : "r"(value));
    }

    static void gdtr(Reg16 * limit, Reg32 * base) {
	char aux[6];
	ASMV("sgdt %0" : "=m"(aux[0]) :);
	*limit = *((Reg16 *)&aux[0]);
	*base = *((Reg32 *)&aux[2]);
    }
    static void gdtr(Reg16 limit, Reg32 base) {
	char aux[6];
	*((Reg16 *)&aux[0]) = limit;
	*((Reg32 *)&aux[2]) = base;
	ASMV("lgdt %0" : : "m" (aux[0]));
    }
 
    static void idtr(Reg16 * limit, Reg32 * base) {
	char aux[6];
	ASMV("sidt %0" : "=m"(aux[0]) :);
	*limit = *((Reg16 *)&aux[0]);
	*base = *((Reg32 *)&aux[2]);
    }
    static void idtr(Reg16 limit, Reg32 base) {
	char aux[6];
	*((Reg16 *)&aux[0]) = limit;
	*((Reg32 *)&aux[2]) = base;
	ASMV("lidt %0" : : "m" (aux[0]));
    }

    static Reg16 cs() {
	Reg16 value; ASMV("mov %%cs,%0" : "=r"(value) :); return value;
    }
    static Reg16 ds() {
	Reg16 value; ASMV("mov %%ds,%0" : "=r"(value) :); return value;
    }
    static Reg16 es() {
	Reg16 value; ASMV("mov %%es,%0" : "=r"(value) :); return value;
    }
    static Reg16 ss() {
	Reg16 value; ASMV("mov %%ss,%0" : "=r"(value) :); return value;
    }
    static Reg16 fs() {
	Reg16 value; ASMV("mov %%fs,%0" : "=r"(value) :); return value;
    }
    static Reg16 gs() {
	Reg16 value; ASMV("mov %%gs,%0" : "=r"(value) :); return value;
    }

    static Reg64 time_stamp() {
	Reg64 ts; ASMV("rdtsc" : "=A" (ts) : ); return ts;
    }

    static void init_fpu() {
	ASM("fninit");
    }

    static Reg8 in8(IO_Port port) {
	Reg8 value;
	ASMV("inb %1,%0" : "=a"(value) : "d"(port));
	return value;
    }
    static Reg16 in16(IO_Port port) {
	Reg16 value;
	ASMV("inw %1,%0" : "=a"(value) : "d"(port));
	return value;
    }
    static Reg32 in32(IO_Port port) {
	Reg32 value;
	ASMV("inl %1,%0" : "=a"(value) : "d"(port));
	return value;
    }
    static void out8(IO_Port port, Reg8 value) {
	ASMV("outb %1,%0" : : "d"(port), "a"(value));
    }
    static void out16(IO_Port port, Reg16 value)	{
	ASMV("outw %1,%0" : : "d"(port), "a"(value));
    }
    static void out32(IO_Port port, Reg32 value)	{
	ASMV("outl %1,%0" : : "d"(port), "a"(value));
    }

    static void switch_tss(Reg32 tss_selector) {
	struct {
	    Reg32 offset;
	    Reg32 selector;
	} address;

	address.offset   = 0;
	address.selector = tss_selector;

	ASM("ljmp *%0" : "=o" (address));
    }

    static int init(System_Info *si);
};

typedef IA32 CPU;

__END_SYS

#endif
