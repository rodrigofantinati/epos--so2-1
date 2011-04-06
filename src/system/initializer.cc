// EPOS-- INITIALIZER

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

// INITIALIZER is responsible for initializing the operating system. It can
// relly on a basic node configuration carried out by SETUP. What INIT
// will actually do depends on the OS configuration for  the specific
// application, but one thing are mandatory: create the first process!

#include <utility/elf.h>
#include <utility/debug.h>
#include <system/kmalloc.h>
#include <system/initializer.h>
#include <machine.h>
#include <address_space.h>
#include <segment.h>
#include <mutex.h>
#include <semaphore.h>
#include <condition.h>
#include <alarm.h>
#include <clock.h>
#include <chronometer.h>
#include <thread.h>

extern "C" { void __epos_library_app_entry(void); }

__BEGIN_SYS

extern System_Info * si;
extern char * _sys_heap;

Initializer::Dispatcher * Initializer::init_table[] = INIT_TABLE;

Initializer::Initializer(System_Info * si)
{
    db<Init>(INF)  << "si(" << (void *)si << ")={msize=" << si->mem_size 
		   << ",free=" << si->mem_free << "}\n";
    

    db<Init>(INF) << "iomm_size = " << (void*)si->iomm_size << "\n";
    for(unsigned int i = 0; i < si->iomm_size; i++)
	db<Init>(INF) << "iomm[" << i
		      << "]={loc=" << (void *)si->iomm[i].locator
		      << ",phy=" << (void *)si->iomm[i].phy_addr
		      << ",log=" <<  (void *)si->iomm[i].log_addr
		      << ",size=" << si->iomm[i].size << "}\n";
        
    // Double check if we have a heap
    sys_heap.free(&_sys_heap, Traits<Machine>::SYSTEM_HEAP_SIZE);
    int * tmp = (int *)kmalloc(sizeof(int));
    if(!tmp) {
	db<Init>(ERR) << "It won't work: we don't have a heap!\n";
	CPU::halt();
    } else
	db<Init>(INF) << "heap=" << (void *)tmp << "\n";
    kfree(tmp);

    if(si->bm.system_off == -1) // EPOS is a library
	si->lmm.app_entry = 
	    reinterpret_cast<unsigned int>(__epos_library_app_entry);

    // Initialize EPOS abstractions 
    db<Init>(INF) << "Initializing EPOS abstractions: \n";
    for(unsigned int i = 0; init_table[i] != __LAST_INIT; i++)
	init_table[i](si);
    db<Init>(INF) << "done! \n";
	
    // Initialize the application's heap
    app_heap.free(
	MMU::alloc(MMU::pages(Traits<Machine>::APPLICATION_HEAP_SIZE)),
	Traits<Machine>::APPLICATION_HEAP_SIZE);

    // Initialize the Thread abstraction, thus creating the first thread
    db<Init>(INF) << "Starting first process ...\n";
    Thread::init(si);

    // This point won't be reached if a member of the Thread family was
    // selected, since the cooresponding initialization will activate the
    // first thread
    reinterpret_cast<Function *>(si->lmm.app_entry)();
}

// Global object initializer
Initializer initializer(si);

__END_SYS
