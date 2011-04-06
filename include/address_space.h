// EPOS-- Address_Space Abstraction Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __address_space_h
#define __address_space_h

#include <system/config.h>
#include <mmu.h>
#include <segment.h>

__BEGIN_SYS

class Address_Space
{
private:
    typedef Traits<Address_Space> Traits;
    static const Type_Id TYPE = Type<Address_Space>::TYPE;

    typedef CPU::Phy_Addr Phy_Addr;
    typedef CPU::Log_Addr Log_Addr;
    typedef MMU::Directory Directory;

public:
    Address_Space() {
	db<Address_Space>(TRC) << "Address_Space(_dir=" << &_dir << ")\n";
    }
    ~Address_Space() {
	db<Address_Space>(TRC) << "~Address_Space(_dir=" << &_dir << ")\n";
    }


    Log_Addr attach(Segment & seg, Log_Addr addr = 0U) {
	db<Address_Space>(TRC) << "Address_Space::attach(seg=" << &seg
			       << ",addr=" << addr << ")\n";

	return _dir.attach(seg.chunk(), addr);
    }
    void detach(Segment & seg) {
	db<Address_Space>(TRC) << "Address_Space::detach(seg=" << &seg 
			       << ")\n";

	_dir.detach(seg.chunk());
    }

    Phy_Addr physical(Log_Addr address) { 
	return _dir.physical(address);
    }

    static int init(System_Info * si);

private:
    Directory _dir;
};

__END_SYS

#endif

//    Segment(const Id & id) {}
//    Segment(const Segment & obj) {}
//    static Address_Space * current() { return _current; }
