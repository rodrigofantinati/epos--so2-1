// EPOS-- OStream Interface

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <system/config.h>

#ifndef __ostream_h
#define __ostream_h

__BEGIN_SYS

class OStream
{
public:
    OStream & operator<<(char c) {
	char buf[2];
	buf[0] = c;
	buf[1] = '\0';
	print(buf);
	return *this;
    }
    OStream & operator<<(unsigned char c) { return operator<<((char)c); }

    OStream & operator<<(int i) {
	char buf[64];
	buf[itoa(i, buf)] = '\0';
	print(buf);
	return *this;
    }
    OStream & operator<<(short s) { return operator<<((int)s); }
    OStream & operator<<(long l) { return operator<<((int)l); }

    OStream & operator<<(unsigned int u) {
	char buf[64];
	buf[utoa(u, buf)] = '\0';
	print(buf);
	return *this;
    }
    OStream & operator<<(unsigned short s) { return operator<<((unsigned)s); }
    OStream & operator<<(unsigned long l) { return operator<<((unsigned)l); }

    OStream & operator<<(long long int u) {
	char buf[64];
	buf[llitoa(u, buf)] = '\0';
	print(buf);
	return *this;
    }

    OStream & operator<<(unsigned long long int u) {
	char buf[64];
	buf[llutoa(u, buf)] = '\0';
	print(buf);
	return *this;
    }

    OStream & operator<<(const void * p) {
	char buf[64];
	buf[ptoa(p, buf)] = '\0';
	print(buf);
	return *this;
    }

    OStream & operator<<(const char * s) { 
	print(s);
	return *this; 
    }

private:
    void print(const char * s);
    int itoa(int i, char * s);
    int utoa(unsigned int u, char * s);
    int llitoa(long long int i, char * s);
    int llutoa(unsigned long long int u, char * s);
    int ptoa(const void * p, char * s);

private:
    static const char OStream::dec_digits[];
    static const char OStream::hex_digits[];
}; 

extern OStream kout, kerr;

__END_SYS

#endif
