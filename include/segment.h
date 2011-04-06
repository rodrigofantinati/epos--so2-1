// EPOS-- Memory Segment Abstraction Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __segment_h
#define __segment_h

#include <system/config.h>
#include <mmu.h>

__BEGIN_SYS

class Segment
{
private:
    typedef Traits<Segment> Traits;
    static const Type_Id TYPE = Type<Segment>::TYPE;

    typedef MMU::Chunk Chunk;
    typedef MMU::Flags Flags;
    typedef CPU::Phy_Addr Phy_Addr;

public:
    Segment(unsigned int bytes, Flags flags = Flags::APP)
	: _chunk(bytes, flags)
    {
	    db<Segment>(TRC) << "Segment(bytes=" << bytes 
			 << ",flags=" << flags << ")\n";
    }
    Segment(Phy_Addr phy_addr, unsigned int bytes, Flags flags = Flags::APP)
	: _chunk(phy_addr, bytes, flags | Flags::IO)
    // The MMU::IO flag signalizes the MMU that the attached memory shall
    // not be released when the chunk is deleted
    {
	db<Segment>(TRC) << "Segment(bytes=" << bytes 
			 << ",phy_addr=" << phy_addr
			 << ",flags=" << flags << ")\n";
    }
    ~Segment() {
	db<Segment>(TRC) << "~Segment()\n";
    }

    unsigned int size() const { return _chunk.size(); }
    Phy_Addr phy_address() const { return _chunk.phy_address(); }

    int resize(int amount) { return _chunk.resize(amount); }

    const Chunk & chunk() const { return _chunk; }

    static int init(System_Info * si);

private:
    Chunk _chunk;
};

__END_SYS

#endif

//    Segment(const Id & id) {}
//    Segment(const Segment & obj) {}
//    Segment(Chunk & chunk)
//	: _chunk(chunk) {
//        db<Segment>(TRC) << "Segment(chunk=" << &chunk << ")\n";
//    }
//    const Id & id();
//    bool valid();

