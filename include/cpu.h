// EPOS-- CPU Mediator Common Package

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __cpu_h
#define __cpu_h

#include <system/config.h>

__BEGIN_SYS

class CPU_Common
{
protected:
    CPU_Common() {}

public:
    typedef unsigned char Reg8;
    typedef unsigned short Reg16;
    typedef unsigned long Reg32;
    typedef unsigned long long Reg64;

    class Log_Addr {
    public:
	Log_Addr() {}
	Log_Addr(const Log_Addr & a) : _addr(a._addr) {}
	Log_Addr(unsigned int a) : _addr(a) {}
 	template <typename T>
	Log_Addr(T * a) : _addr(reinterpret_cast<unsigned int>(a)) {}

 	operator unsigned int() const { return _addr; }
 	template <typename T>
	operator T *() const { return reinterpret_cast<T *>(_addr); }

 	template <typename T>
	bool operator==(T a) const { return (_addr == (unsigned int)a); }
 	template <typename T>
	bool operator< (T a) const { return (_addr < (unsigned int)a); }
 	template <typename T>
	bool operator> (T a) const { return (_addr > (unsigned int)a); }
 	template <typename T>
	bool operator>=(T a) const { return (_addr >= (unsigned int)a); }
 	template <typename T>
	bool operator<=(T a) const { return (_addr <= (unsigned int)a); }

 	template <typename T>
	Log_Addr operator-(T a) const { return _addr - (unsigned int)a; }
 	template <typename T>
	Log_Addr operator+(T a) const { return _addr + (unsigned int)a; }
 	template <typename T>
 	Log_Addr & operator+=(T a) { _addr += a; return *this; }
 	template <typename T>
 	Log_Addr & operator-=(T a) { _addr -= a; return *this; }
 	template <typename T>
	Log_Addr & operator&=(T a) { _addr &= a; return *this; }

	friend Debug & operator << (Debug & db, Log_Addr a)
	    { db << (void *)a._addr; return db; }

    private:
	unsigned int _addr;
    };
    typedef Log_Addr Phy_Addr;

    typedef unsigned long Hertz;

    class Context;

public:
    static void halt() { for(;;); }

    static bool tsl(volatile bool & lock) {
	bool old = lock;
	lock = 1;
	return old;
    }
    static int finc(volatile int & number) {
	int old = number;
	number++;
	return old;
    }
    static int fdec(volatile int & number) {
	int old = number;
	number--;
	return old;
    }

protected:
    static Reg32 htonl_lsb(Reg32 v) {
	return (((v << 24) & 0xff000000) | ((v <<  8) & 0x00ff0000) |
		((v >>  8) & 0x0000ff00) | ((v >> 24) & 0x000000ff));
    }
    static Reg16 htons_lsb(Reg16 v)	{
	return ((v << 8) & 0xFF00) | ((v >> 8) & 0x00FF);
    }
    static Reg32 ntohl_lsb(Reg32 v) {
	return htonl_lsb(v);
    }
    static Reg16 ntohs_lsb(Reg16 v) {
	return htons_lsb(v);
    }

    static Reg32 htonl_msb(Reg32 v) {
	return v;
    }
    static Reg16 htons_msb(Reg16 v) {
	return v;
    }
    static Reg32 ntohl_msb(Reg32 v) {
	return v;
    }
    static Reg16 ntohs_msb(Reg16 v) {
	return v;
    }
};

__END_SYS

#include __HEADER_ARCH(cpu)

#endif
