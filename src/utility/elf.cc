// EPOS-- ELF Utility Implementation

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/elf.h>
#include <utility/string.h>

__BEGIN_SYS

int ELF::load_segment(int i, void * addr)
{
    if((i > segments()) || (segment_type(i) != PT_LOAD))
		return -1;
    
    void * src = ((char *) this) + seg(i)->p_offset;
    void * dst = (addr)? addr : segment_address(i);
        
    memcpy(dst, src, seg(i)->p_filesz);
    memset((char *)dst + seg(i)->p_filesz, 0,
	   seg(i)->p_memsz - seg(i)->p_filesz);
    
    return seg(i)->p_memsz;
}

__END_SYS

