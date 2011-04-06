// EPOS-- PC Mediator Initialization

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <mach/pc/pc.h>

__BEGIN_SYS

// void default_handler(void)
// {
//     Display display;
//     display.position(0, 70);
//     display.puts("PANIC");
//     IA32::halt();
// }

int PC::init(System_Info * si)
{
    db<PC>(TRC) << "PC::init()\n";

//     for(int i = 0; i < IA32::IDT_ENTRIES; i++)
// 	int_handler(i, &handler_wrapper<default_handler>);

    return 0;
}

// //========================================================================
// // page_fault                                                           
// //                                                                      
// // Desc: Page fault exception handler (what a handling! :-)).           
// //                                                                      
// // Parm: exception stack and error code pushed by the CPU		
// //------------------------------------------------------------------------
// void page_fault(Reg32 eip, Reg32 cs, Reg32 eflags, Reg32 esp3, Reg32 ss,
// 		Reg32 error)
// {  
//     IA32 cpu;

//     db<Setup>(ERR) << "this thread generated an invalid address and will be terminated!\n";
//     db<Setup>(ERR) << "address=" << (void *)cpu.cr2() << "\n";
//     db<Setup>(ERR) << "context={cs=" << cs 
// 		   << ",ip=" << (void *)eip 
// 		   << ",flg=" << (void *)eflags 
// 		   << ",ss=" << (void *)ss 
// 		   << ",sp=" << (void *)esp3 
// 		   << ",err=" << (void *)error << "}\n";

//     panic();
// }

// //========================================================================
// // gpf                                                                  
// //                                                                      
// // Desc: GPF exception handler (what a handling! :-)).   	        
// //                                                                      
// // Parm: exception stack and error code pushed by the CPU		
// //------------------------------------------------------------------------
// void gpf(Reg32 eip, Reg32 cs, Reg32 eflags, Reg32 esp3, Reg32 ss, Reg32 error)
// {  
//     short ds;
//     ASM("movw %%ds, %0" : "=o" (ds) : );

//     db<Setup>(ERR) << "this thread caused a GPF and will be terminated!\n";
//     db<Setup>(ERR) << "context={cs=" << cs
// 		   << ",ds=" << ds
// 		   << ",ip=" << (void *)eip
// 		   << ",flg=" << (void *)eflags
// 		   << ",ss=" << (void *)ss 
// 		   << ",sp=" << (void *)esp3 
// 		   << ",err=" << (void *)error << "}\n",
    
//     panic();
// }

// //========================================================================
// // fpu                                                                  
// //                                                                      
// // Desc: FPU exception handler.				   	        
// //------------------------------------------------------------------------
// void fpu()
// {  
//     db<Setup>(ERR) << "FPU generated an interrupt!\n";

// //    ASM("clts");

//     panic();
// }

// //========================================================================
// // syscall                                                              
// //                                                                      
// // Desc: FPU exception handler.				   	        
// //------------------------------------------------------------------------
// void syscall()
// {  
//     db<Setup>(ERR) << "System call invoked but no OS kernel loaded (yet)!\n";

//     panic();
// }

// //========================================================================
// // panic
// //
// // Desc: This function is called if something goes wrong during setup,
// //	 including uncaught interrupts.
// //------------------------------------------------------------------------
// void panic()
// {
//   unsigned short *video;

//   // Set a pointer to GCA text frame buffer so we can say something 
//   video = reinterpret_cast<unsigned short *>(
//       Traits<PC_Display>::FRAME_BUFFER_ADDRESS);

//   video [0] = 'P' | 0x1f00;
//   video [1] = 'A' | 0x1f00;
//   video [2] = 'N' | 0x1f00;
//   video [3] = 'I' | 0x1f00;
//   video [4] = 'C' | 0x1f00;
//   video [5] = '!' | 0x1f00;

//   ASM("hlt");
// }


__END_SYS
