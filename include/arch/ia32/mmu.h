// EPOS-- IA32 MMU Mediator Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __ia32_mmu_h
#define __ia32_mmu_h

#include <cpu.h>
#include <mmu.h>
#include <utility/string.h>
#include <utility/list.h>
#include __HEADER_MACH(memory_map)

__BEGIN_SYS

class IA32_MMU: public MMU_Common<10, 10, 12>
{
private:
    typedef Traits<IA32_MMU> Traits;
    static const Type_Id _TYPE = Type<IA32_MMU>::TYPE;

    typedef Grouping_List<Frame> List;

    static const unsigned int PHY_MEM = Memory_Map<Machine>::PHY_MEM;
    static const unsigned int SYS_PT  = Memory_Map<Machine>::PHY_MEM;

public:
    // Page Flags
    class IA32_Flags
    {
    public:
	enum {
	    PRE  = 0x001, // Presence (0=not-present, 1=present)
	    RW   = 0x002, // Write (0=read-only, 1=read-write)
	    USR  = 0x004, // Access Control (0=supervisor, 1=user)
	    PWT  = 0x008, // Cache Mode (0=write-back, 1=write-through)
	    PCD  = 0x010, // Cache Disable (0=cacheable, 1=non-cacheable)
	    ACC  = 0x020, // Accessed (0=not-accessed, 1=accessed
	    DRT  = 0x040, // Dirty (only for PTEs, 0=clean, 1=dirty)
	    PS   = 0x080, // Page Size (for PDEs, 0=4KBytes, 1=4MBytes)
	    GLB  = 0X100, // Global Page (0=local, 1=global)
	    EX   = 0x200, // User Def. (0=non-executeable, 1=executeable)
	    CT   = 0x400, // User Def. (0=non-contiguous, 1=contiguous)
	    IO   = 0x800, // User Def. (0=memory, 1=I/O)
	    SYS = (PRE | RW  | ACC),
	    APP = (PRE | RW  | ACC | USR),
	    PCI = (SYS | PCD | IO)
	};

    public:
	IA32_Flags() {}
	IA32_Flags(const IA32_Flags & f) : _flags(f._flags) {}
	IA32_Flags(unsigned int f) : _flags(f) {}
	IA32_Flags(Flags f) : _flags(PRE |
				     (f & Flags::RW)  ? RW  : 0 |
				     (f & Flags::USR) ? USR : 0 |
				     (f & Flags::CWT) ? PWT : 0 |
				     (f & Flags::CD)  ? PCD : 0 |
				     (f & Flags::CT)  ? CT  : 0 |
				     (f & Flags::IO)  ? PCI : 0 ) {}

	operator unsigned int() const { return _flags; }

	friend Debug & operator << (Debug & db, IA32_Flags f)
	    { db << (void *)f._flags; return db; }

    private:
	unsigned int _flags;
    };

    // Page_Table
    class Page_Table 
    {
    public:
	Page_Table() {}
	
	PT_Entry & operator[](unsigned int i) { return _entry[i]; }
	
	void map(int from, int to, IA32_Flags flags) {
	    for( ; from <= to; from++)
		_entry[from] = alloc() | flags;
	}
	void map_contiguous(int from, int to, IA32_Flags flags) {
	    remap(alloc(to - from + 1), from, to, flags);
	}
	void remap(Phy_Addr addr, int from, int to, IA32_Flags flags) {
	    addr = align_page(addr);
	    for( ; from <= to; from++) {
		_entry[from] = addr | flags;
		addr+= sizeof(Page);
	    }
	}
	void unmap(int from, int to) {
	    for( ; from <= to; from++) {
		free(_entry[from]);
		_entry[from] = 0;
	    }
	}
	
    private:
	PT_Entry _entry[PT_ENTRIES];
    };

    // Chunk (for Segment)
    class Chunk
    {
    public:
        Chunk() {}
        Chunk(unsigned int bytes, Flags flags)
	    : _from(0), _to(pages(bytes)), _pts(page_tables(_to - _from)),
	      _flags(IA32_Flags(flags)), _pt(calloc(_pts))
	{
	    if(flags & IA32_Flags::CT)
		_pt->map_contiguous(_from, _to, _flags);
	    else 
		_pt->map(_from, _to, _flags);
	}
	Chunk(Phy_Addr phy_addr, unsigned int bytes, Flags flags)
	    : _from(0), _to(pages(bytes)), _pts(page_tables(_to - _from)),
	      _flags(IA32_Flags(flags)), _pt(calloc(_pts))
        {
	    _pt->remap(phy_addr, _from, _to, flags);
	}
	~Chunk() {
	    if(!(_flags & IA32_Flags::IO))
		if(_flags & IA32_Flags::CT)
		    free((*_pt)[_from], _to - _from);
		else
		    for(unsigned int i = _from; i < _to; i++)
			free((*_pt)[i]);
	    free(_pt, _pts);
	}

	unsigned int pts() const { return _pts; }
	IA32_Flags flags() const { return _flags; }
	Page_Table * pt() const { return _pt; }
	unsigned int size() const { return (_to - _from) * sizeof(Page); }
	Phy_Addr phy_address() const {
	    return (_flags & IA32_Flags::CT) ? (*_pt)[_from] : Phy_Addr(false);
	}

	int resize(unsigned int amount) {
	    if(_flags & IA32_Flags::CT)
		return 0;

	    unsigned int pgs = pages(amount);
	    if((_pts * PT_ENTRIES - _to - 1) < pgs)
		return 0;

	    _pt->map(_to + 1, _to + 1 + pgs, _flags);
	    _to += pgs;

	    return pgs * sizeof(Page);
	}

    private:
	unsigned int _from;
	unsigned int _to;
	unsigned int _pts;
	IA32_Flags _flags;
	Page_Table * _pt;
    };

    // Page Directory
    typedef Page_Table Page_Directory;

    // Directory (for Address_Space)
    class Directory 
    {
    public:
	Directory() : _pd(calloc(1)) {}
	Directory(Page_Directory * pd) : _pd(pd) {}
	~Directory() { free(_pd); }
	
	Log_Addr attach(const Chunk & chunk) {
	    for(unsigned int i = 0; i < PD_ENTRIES; i++)
		if(attach(i, chunk.pt(), chunk.pts(), chunk.flags()))
		    return i << DIRECTORY_SHIFT;
	    return false;
	}
	Log_Addr attach(const Chunk & chunk, Log_Addr addr) {
	    unsigned int from = directory(addr);
	    if(!attach(from, chunk.pt(), chunk.pts(), chunk.flags()))
		return Log_Addr(false);

	    return from << DIRECTORY_SHIFT;
	}
 	void detach(const Chunk & chunk) {
 	    for(unsigned int i = 0; i < PD_ENTRIES; i++)
		if(indexes((*_pd)[i]) == indexes(chunk.pt())) {
		    detach(i, chunk.pt(), chunk.pts());
		    return;
		}
	    db<IA32_MMU>(WRN) << "IA32_MMU::Directory::detach(pt=" 
			      << chunk.pt() << ") failed!\n";
 	}
 	void detach(const Chunk & chunk, Log_Addr addr) {
	    unsigned int from = directory(addr);
	    if(indexes((*_pd)[from]) != indexes(chunk.pt())) {
		db<IA32_MMU>(WRN) << "IA32_MMU::Directory::detach(pt=" 
				  << chunk.pt() << ",addr="
				  << addr << ") failed!\n";
		return;
	    }
	    detach(from, chunk.pt(), chunk.pts());
 	}

	Phy_Addr physical(Log_Addr addr) {
	    Page_Table * pt = (Page_Table *)(void *)(*_pd)[directory(addr)];
	    return (*pt)[page(addr)] | offset(addr);
	}

    private:
	bool attach(unsigned int from, const Page_Table * pt,
		    unsigned int n, IA32_Flags flags) {
	    for(unsigned int i = from; i < from + n; i++)
		if((*_pd)[i])
		    return false;
	    for(unsigned int i = from; i < from + n; i++)
		(*_pd)[i] = Phy_Addr(pt + (i * PT_ENTRIES)) | flags;

	    return true;
	}
	void detach(unsigned int from, const Page_Table * pt, unsigned int n) {
	    for(unsigned int i = from; i < from + n; i++)
		(*_pd)[i] = 0;
	}

    private:
	Page_Directory * _pd;
    };

public:
    IA32_MMU() {}
    ~IA32_MMU() {}

    static void flush_tlb() {
        db<IA32_MMU>(TRC) << "IA32_MMU::flush_tlb()\n";

	ASMV("movl %cr3,%eax");
	ASMV("movl %eax,%cr3");
    }
    static void flush_tlb(Log_Addr addr) {
        db<IA32_MMU>(TRC) << "IA32_MMU::flush_tlb(" << addr << ")\n";
	ASMV("invlpg %0" : : "m"(addr));
    }

    static Phy_Addr alloc(unsigned int frames = 1) {
		Phy_Addr phy(false);
		if(frames) {
			List::Element * e = _free.search_decrementing(frames);
			if(e)
				phy = e->object() + e->size();
			else
				db<IA32_MMU>(WRN) << "IA32_MMU::alloc() failed!\n";
		}
	    db<IA32_MMU>(TRC) << "IA32_MMU::alloc(frames=" << frames << ") => " << (void *)phy << "\n";
		return phy;
    }
    static Phy_Addr calloc(unsigned int frames = 1) {
	Phy_Addr phy = alloc(frames);
	memset(phy2log(phy), sizeof(Frame) * frames, 0);
	return phy;	
    }
    static void free(Phy_Addr frame, int n = 1) {
        db<IA32_MMU>(TRC) << "IA32_MMU::free(frame=" << (void *)frame 
			  << ",n=" << n << ")\n";

	if(frame && n) {
	    List::Element * e = new (phy2log(frame)) List::Element(frame, n);
	    List::Element * m1, * m2;
	    _free.insert_merging(e, &m1, &m2);
	}
    }

    static Page_Directory * volatile current() {
	return reinterpret_cast<Page_Directory * volatile>(CPU::pdp());
    }

    static Phy_Addr physical(Log_Addr addr) {
	Page_Directory * pd = current();
	Page_Table * pt = (*pd)[directory(addr)];
	return (*pt)[page(addr)] | offset(addr);
    }

    static int init(System_Info * si);

private:
    static Log_Addr phy2log(Phy_Addr log) { return log | PHY_MEM; }

private:
    static List _free;
};

typedef IA32_MMU MMU;

__END_SYS

#endif
