// EPOS-- Heap Utility Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __heap_h
#define __heap_h

#include <utility/debug.h>
#include <utility/string.h>
#include <utility/list.h>

__BEGIN_SYS

class Heap:  public Grouping_List<char>
{
public:
    Heap() {}
    Heap(void * addr, unsigned int bytes) { free(addr, bytes); }

    void * alloc(unsigned int bytes) {
	char * addr = 0;
	if(bytes) {
	    Element * e = search_decrementing(bytes);
	    if(e)
		addr = e->object() + e->size();
	    
	    db<System>(TRC) << "Heap::alloc(this=" << this
			    << ",bytes=" << bytes 
			    << ") => " << (void *)addr << "\n";
	}
	return addr;
    }
    void * calloc(unsigned int bytes) {
	void * addr = alloc(bytes);
	memset(addr, bytes, 0);
	return addr;	
    }
    void * realloc(void * ptr, unsigned int bytes);

    void free(void * ptr) {
	free(ptr, 4);
    }
    void free(void * ptr, unsigned int bytes) {
        db<System>(TRC) << "Heap::free(this=" << this
			<< ",ptr=" << ptr
			<< ",bytes=" << bytes << ")\n";

	if(ptr && (bytes >= sizeof(Element))) {
	    Element * e = new (ptr)
		Element(reinterpret_cast<char *>(ptr), bytes);
	    Element * m1, * m2;	    
	    insert_merging(e, &m1, &m2);
	}
    }
};

__END_SYS

#endif
