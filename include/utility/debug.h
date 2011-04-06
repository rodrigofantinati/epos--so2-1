// EPOS-- Debug Utility Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __debug_h
#define __debug_h 

#include <utility/ostream.h>

__BEGIN_SYS

class Debug
{
public:
    Debug & operator<<(int i) {
	kerr << i; return *this; 
    }
    Debug & operator<<(short s) {
	return operator<<(static_cast<int>(s)); 
    }
    Debug & operator<<(long l) {
	return operator<<(static_cast<int>(l));
    }
    Debug & operator<<(long long l) {
	kerr << l; return *this;
    }

    Debug & operator<<(unsigned int u) {
	kerr << u; return *this;
    }
    Debug & operator<<(unsigned short s) {
	return operator<<(static_cast<unsigned int>(s));
    }
    Debug & operator<<(unsigned long l) {
	return operator<<(static_cast<unsigned int>(l)); 
    }
    Debug & operator<<(unsigned long long l) {
	kerr << l; return *this;
    }


    Debug & operator<<(const void * p) {
	kerr << p; return *this;
    }

    Debug & operator<<(const char * s) {
	kerr << s; return *this; 
    }
}; 

class Null_Debug
{
public:
    template<class T>
    Null_Debug & operator<<(const T & o) { return *this; }

    template<class T>
    Null_Debug & operator<<(const T * o) { return *this; }
};

template <bool debugged>
class Select_Debug: public Debug {};
template <>
class Select_Debug<false>: public Null_Debug {};

// Error
enum Debug_Error {ERR = 1};

template <typename T>
inline Select_Debug<(Traits<T>::debugged && Traits<Debug>::error)> 
db(Debug_Error l)
{
    return Select_Debug<(Traits<T>::debugged && Traits<Debug>::error)>(); 
}

template <typename T1, typename T2>
inline Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
		     && Traits<Debug>::error)> 
db(Debug_Error l)
{
    return Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
			 && Traits<Debug>::error)>(); 
}

// Warning
enum Debug_Warning {WRN = 2};

template <typename T>
inline Select_Debug<(Traits<T>::debugged && Traits<Debug>::warning)> 
db(Debug_Warning l)
{
    return Select_Debug<(Traits<T>::debugged && Traits<Debug>::warning)>(); 
}

template <typename T1, typename T2>
inline Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
		     && Traits<Debug>::warning)> 
db(Debug_Warning l)
{
    return Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
			 && Traits<Debug>::warning)>(); 
}

// Info
enum Debug_Info {INF = 3};

template <typename T>
inline Select_Debug<(Traits<T>::debugged && Traits<Debug>::info)> 
db(Debug_Info l)
{
    return Select_Debug<(Traits<T>::debugged && Traits<Debug>::info)>(); 
}

template <typename T1, typename T2>
inline Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
		     && Traits<Debug>::info)> 
db(Debug_Info l)
{
    return Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
			 && Traits<Debug>::info)>(); 
}

// Trace
enum Debug_Trace {TRC = 4};

template <typename T>
inline Select_Debug<(Traits<T>::debugged && Traits<Debug>::trace)> 
db(Debug_Trace l)
{
    return Select_Debug<(Traits<T>::debugged && Traits<Debug>::trace)>(); 
}

template <typename T1, typename T2>
inline Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
		     && Traits<Debug>::trace)> 
db(Debug_Trace l)
{
    return Select_Debug<((Traits<T1>::debugged || Traits<T2>::debugged)
			 && Traits<Debug>::trace)>(); 
}

union Debug_Level
{
    Debug_Error err;
    Debug_Warning wrn;
    Debug_Info inf;
    Debug_Trace trc;
};
__END_SYS

#endif

