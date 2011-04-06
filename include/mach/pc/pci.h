// EPOS-- PC PCI Mediator

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __pc_pci_h
#define __pc_pci_h

#include <pci.h>

__BEGIN_SYS

class PC_PCI: public PCI_Common
{
private:
    typedef Traits<PC_PCI> _Traits;
//    static const Type_Id _TYPE = Type<PC_PCI>::TYPE;

    static const int MAX_BUS = _Traits::MAX_BUS;
    static const int MAX_DEV_FN = _Traits::MAX_DEV_FN;

    // From Intel 82443BX manual
    // CONFADD is a 32 bit register accessed only when referenced as a Dword.
    // A Byte or Word reference will "pass through" the Configuration Address
    // Register onto the PCI bus as an I/O cycle. The CONFADD register
    // contains the Bus Number, Device Number, Function Number, and Register
    // Number for which a subsequent configuration access is intended.
    // [31]    -> config enable
    // [24:30] -> reserved
    // [11:15] -> device (5 bits)
    // [ 8:10] -> function (3 bits)
    // [ 2: 7] -> register (6 bits)
    // [ 0: 1] -> reserved
    static const int CONFADDR = 0xcf8;

    // CONFDATA is a 32 bit read/write window into configuration space.
    // The portion of configuration space that is referenced by CONFDATA is
    // determined by the contents of CONFADDR.
    static const int CONFDATA = 0xcfc;

public:
    PC_PCI() {}
    ~PC_PCI() {}

    void header(const Locator & l, Header * h);
    Locator scan(const Class_Id & c, int order);
    Locator scan(const Vendor_Id & v, const Device_Id & d, int order);

    static int init(System_Info * si);

private:
    int cmd(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr) {
	return 0x80000000 | (bus << 16) | (dev_fn << 8) | (addr & ~3);
    }

    CPU::Reg8 cfg8(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr) {
	IA32::out32(CONFADDR, cmd(bus, dev_fn, addr));
	return IA32::in8(CONFDATA + (addr & 3));
    }
    CPU::Reg16 cfg16(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr) {
	IA32::out32(CONFADDR, cmd(bus, dev_fn, addr));    
	return IA32::in16(CONFDATA + (addr & 2));
    }
    CPU::Reg32 cfg32(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr) {
	IA32::out32(CONFADDR, cmd(bus, dev_fn, addr));
	return IA32::in32(CONFDATA);
    }
    void cfg8(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr, CPU::Reg8 value) {
	IA32::out32(CONFADDR, cmd(bus, dev_fn, addr));    
	IA32::out8(CONFDATA + (addr & 3), value);
    }
    void cfg16(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr, CPU::Reg16 value) {
	IA32::out32(CONFADDR, cmd(bus,dev_fn,addr));
	IA32::out16(CONFDATA + (addr & 2), value);
    }
    void cfg32(CPU::Reg8 bus, CPU::Reg8 dev_fn, CPU::Reg8 addr, CPU::Reg32 value) {
	IA32::out32(CONFADDR, cmd(bus, dev_fn, addr));
	IA32::out32(CONFDATA, value);
    }

    CPU::Reg16 vendor_id(CPU::Reg8 bus, CPU::Reg8 dev_fn) {
	return cfg16(bus, dev_fn, VENDOR_ID); 
    }
    CPU::Reg16 device_id(CPU::Reg8 bus, CPU::Reg8 dev_fn) {
	return cfg16(bus, dev_fn, DEVICE_ID); 
    }
    CPU::Reg16 class_id(CPU::Reg8 bus, CPU::Reg8 dev_fn) {
	return cfg16(bus, dev_fn, CLASS_ID); 
    }

  private:
    static CPU::Reg32 base_address[Region::N];
};

__END_SYS

#endif
