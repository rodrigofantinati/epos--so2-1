// EPOS-- OStream Implementation

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <display.h>
#include <utility/ostream.h>

__BEGIN_SYS

const char OStream::dec_digits[] = "0123456789";
const char OStream::hex_digits[] = "0123456789abcdef";

void OStream::print(const char * str)
{
    Display display;

    display.puts(str);
}

int OStream::itoa(int v, char * s)
{
    unsigned int i = 0, j;

    if(!v) {
	s[0] = dec_digits[0];
	return 1;
    }

    if(v < 0) {
	v = -v;
	s[i++] = '-';
    }

    for(j = v; j != 0; i++, j /= 10);
    for(j = 0; v != 0; j++, v /= 10)
	s[i - 1 - j] = dec_digits[v % 10];

    return i;
} 

int OStream::utoa(unsigned int v, char * s)
{
    unsigned int i = 0, j;

    if(!v) {
	s[0] = dec_digits[0];
	return 1;
    }

    for(j = v; j != 0; i++, j /= 10);
    for(j = 0; v != 0; j++, v /= 10)
	s[i - 1 - j] = dec_digits[v % 10];

    return i;
}

int OStream::llitoa(long long int v, char * s)
{
    unsigned int i = 0, j;

    if(!v) {
	s[0] = dec_digits[0];
	return 1;
    }

    if(v < 0) {
	v = -v;
	s[i++] = '-';
    }

    for(j = v; j != 0; i++, j /= 10);
    for(j = 0; v != 0; j++, v /= 10)
	s[i - 1 - j] = dec_digits[v % 10];

    return i;
} 

int OStream::llutoa(unsigned long long int v, char * s)
{
    unsigned int i = 0, j;

    if(!v) {
	s[0] = dec_digits[0];
	return 1;
    }

    for(j = v; j != 0; i++, j /= 10);
    for(j = 0; v != 0; j++, v /= 10)
	s[i - 1 - j] = dec_digits[v % 10];

    return i;
}

int OStream::ptoa(const void * p, char * s)
{
    unsigned int j, v = (unsigned int)p;

    s[0] = '0';
    s[1] = 'x';
    for(j = 0; j < sizeof(void *) * 2; j++, v >>= 4)
	s[2 + sizeof(void *) * 2 - 1 - j]
	    = hex_digits[v & 0xf];

    return j + 2;
}    


__END_SYS
