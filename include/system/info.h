// EPOS-- Run-Time System Information

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#ifndef __info_h
#define __info_h

#include <system/config.h>

__BEGIN_SYS

class System_Info
{
public:
    typedef unsigned int Log_Addr;
    typedef unsigned int Phy_Addr;

    // The information we have at boot time (built up by MKBI)
    struct Boot_Map
    {
	Phy_Addr mem_base;         // Memory base 
	unsigned int mem_size;     // Memory size (in bytes)
	int cpu_type;              // Processor type 
	int cpu_clock;             // Processor clock frequency in Hz 
	int n_threads;             // Max number of threads 
	int n_tasks;               // Max number of tasks 
	unsigned short host_id;    // The local host id (-1 => RARP) 
	unsigned short n_nodes;    // Number of nodes in SAN 
	int img_size;              // Boot image size in bytes 
	int setup_off;             // SETUP offset in the boot image 
	int system_off;            // OS offset in the boot image 
	int loader_off;            // LOADER 	offset in the boot image 
	int app_off;               // APPs offset in the boot image 
    };

    // Physical Memory Map (built up by SETUP)
    struct Physical_Memory_Map
    {
	Phy_Addr app_lo;        // Application memory's lowest address
	Phy_Addr app_hi;        // Application memory's highest address
	Phy_Addr int_vec;       // Interrupt Vector
	Phy_Addr sys_pt;        // System Page Table
	Phy_Addr sys_pd;        // System Page Directory
	Phy_Addr sys_info;      // System Info
	Phy_Addr phy_mem_pts;   // Page tables to map the whole physical memory
	Phy_Addr io_mem_pts;    // Page tables to map the IO address space 
	Phy_Addr sys_code;      // OS Code Segment
	Phy_Addr sys_data;      // OS Data Segment
	Phy_Addr sys_stack;     // OS Stack Segment
	Phy_Addr free;          // Free memory base
	unsigned int free_size; // Free memory size (in frames)
	Phy_Addr mach1;         // Machine specific entries
	Phy_Addr mach2;
	Phy_Addr mach3;
	Phy_Addr free1_base;    // First free memory chunk base address
	Phy_Addr free1_top;     // First free memory chunk top address
	Phy_Addr free2_base;    // Second free memory chunk base address
	Phy_Addr free2_top;     // Second free memory chunk top address

    };

    // Logical Memory Map (built up by MKBI and SETUP)
    struct Logical_Memory_Map
    {
	Log_Addr base;        // Lowest valid logical address
	Log_Addr top;         // Highest valid logical address
	Log_Addr app_lo;      // Application memory lowest address
	Log_Addr app_entry;   // First application's entry point
	Log_Addr app_code;    // First application's code base address
	Log_Addr app_data;    // First application's data base address
	Log_Addr app_hi;      // Application memory highest address
	Log_Addr phy_mem;     // Whole physical memory (contiguous)
	Log_Addr io_mem;      // IO address space 
	Log_Addr int_vec;     // Interrupt Vector
	Log_Addr sys_pt;      // System Page Table
	Log_Addr sys_pd;      // System Page Directory
	Log_Addr sys_info;    // System Info
	Log_Addr sys_code;    // OS Code Segment
	Log_Addr sys_data;    // OS Data Segment
	Log_Addr sys_stack;   // OS Stack Segment
	Log_Addr mach1;       // Machine specific entries
	Log_Addr mach2;
	Log_Addr mach3;
    };

    // I/O Device mapping information
    struct IO_Memory_Map
    {
	int locator;
	Phy_Addr phy_addr;
	Log_Addr log_addr;
	unsigned int size;
    };
    
public:
    unsigned int mem_size;   // Memory size (in pages)
    unsigned int mem_free;   // Free memory (in pages)
    unsigned int iomm_size;
    Boot_Map bm;
    Physical_Memory_Map pmm;
    Logical_Memory_Map lmm;
    IO_Memory_Map iomm[];
};

template <class Machine>
struct Memory_Map {};

__END_SYS

#include __HEADER_MACH(memory_map)

#endif
