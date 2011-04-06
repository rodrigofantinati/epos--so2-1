// EPOS-- System-level Dynamic Memory Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __kmalloc_h
#define __kmalloc_h

#include <utility/heap.h>

__BEGIN_SYS

extern Heap sys_heap;

inline void * kmalloc(unsigned int bytes) { 
    return sys_heap.alloc(bytes);
}
inline void * kcalloc(unsigned int n, unsigned int bytes) {
    return sys_heap.calloc(n * bytes); 
}
inline void * krealloc(void * ptr, unsigned int bytes) {
    return sys_heap.realloc(ptr, bytes);
}
inline void kfree(void * ptr) {
    sys_heap.free(ptr); 
}

__END_SYS

#endif

