// EPOS-- IA32 MMU Mediator Initialization

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <mmu.h>

__BEGIN_SYS

int IA32_MMU::init(System_Info * si)
{
    db<IA32_MMU>(TRC) << "IA32_MMU::init()\n";

    db<IA32_MMU>(INF) << "IA32_MMU:: memory size = " 
		      << si->mem_size << " pages\n";
    db<IA32_MMU>(INF) << "IA32_MMU:: free memory = " 
		      << si->mem_free << " pages\n";
    db<IA32_MMU>(INF) << "IA32_MMU:: application's memory base = " 
		      << (void *) si->pmm.app_lo << "\n";
    db<IA32_MMU>(INF) << "IA32_MMU:: free chunk = {base=" 
		      << (void *) si->pmm.mach2 << ",size="
		      << (void *) si->pmm.mach3 << "}\n";
    db<IA32_MMU>(INF) << "IA32_MMU:: free chunk = {base=" 
		      << (void *) si->pmm.free << ",size="
		      << (void *) si->pmm.free_size << "}\n";
    db<IA32_MMU>(INF) << "IA32_MMU:: physical memory logical address = "
		      << (void *) si->lmm.phy_mem << "\n";

//     db<IA32_MMU>(INF) << "IA32_MMU::free => {h=" << (void *)_free.head()
// 		      << ",t=" << (void *)_free.head()
// 		      << ",s=" << _free.size() 
// 		      << ",t=" << (void *)&_free 
// 		      << ",s=" << sizeof(_free) << "}\n";
    
    // Insert all free memory into the _free list
    List::Element * e, * m1, * m2;
    e = new (phy2log(reinterpret_cast<void *>(si->pmm.mach2)))
	List::Element(reinterpret_cast<Page *>(si->pmm.mach2),
		      si->pmm.mach3);
    _free.insert_merging(e, &m1, &m2);

    e = new (phy2log(reinterpret_cast<void *>(si->pmm.free)))
	List::Element(reinterpret_cast<Page *>(si->pmm.free),
		      si->pmm.free_size);
    _free.insert_merging(e, &m1, &m2);

    db<IA32_MMU>(INF) << "Free Frames => " << _free.grouped_size() << "\n";

    return 0;
}

__END_SYS

