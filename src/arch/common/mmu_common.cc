// EPOS-- MMU Mediator Common Package Implementation

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <mmu.h>

__BEGIN_SYS

// Class attributes
// bool MMU_Common<10, 10, 12>::Frame_List::_frame_list_lock;

// static bool _access_lock;

// static void enter_critical_region() {
//     while(CPU::tsl(_access_lock));
// }
// static void leave_critical_region() {
//     _access_lock = false;
// }

// /*
//  * This method removes "pages" frames from the _free_frame_list
//  */
// IA32::Phy_Addr MMU_Common<10, 10, 12>::Frame_List::frame_alloc(int n) {
//     db<IA32_MMU>(TRC) << "IA32_MMU::Frame_List::frame_alloc(n=" << n << ")\n";

//     enter_critical_region();

//     Node * aux;
//     aux = search_hole(n);
//     if(!aux) { // If there is no memory
//         leave_critical_region();
//         return (unsigned int)0;
//     }
//     /******** FRAMES FOUND ********/
//     if(aux->size() == static_cast<unsigned int>(n)) { // Memory chunk has exactly the requested size
//         if(aux->prev) aux->prev->next = aux->next;
// 	else {
// 	    head(aux->next);
// 	    aux->next->prev = static_cast<Node *>(0);
// 	}
// 	if(aux->next) aux->next->prev = aux->prev;
// 	else {
// 	    tail(aux->prev);
// 	    aux->prev->next = static_cast<Node *>(0);
// 	}
// 	dec_free_frames(n);
// 	leave_critical_region();
// 	return aux->data();
//     }
//     //Memory chunk doesn't has the requested size, it is bigger, i. e., it must be splited
//     aux->dec_size(n);
//     CPU::Phy_Addr old_data = aux->data();
//     aux->inc_data(sizeof(Page) * n);
//     Node * new_aux = aux + (n * (sizeof(Page)/sizeof(Node)));
//     memcpy(new_aux,aux,sizeof(Node));
//     if(head() == aux) head(new_aux);
//     if(tail() == aux) tail(new_aux);
//     dec_free_frames(n);

//     leave_critical_region();

//     return old_data;
// }

// void MMU_Common<10, 10, 12>::Frame_List::frame_free_ordered(CPU::Phy_Addr addr, int n) {
//     db<IA32_MMU>(TRC) << "IA32_MMU::Frame_List::frame_free_ordered(addr=" << addr << ", n=" << n << ")\n";

//     enter_critical_region();

//     CPU::Phy_Addr sys_addr = addr + 0x80000000;
//     Node * node;
//     Node * aux = search_next(addr);
//     if(!aux) {
//         leave_critical_region();
//         frame_free(addr,n);
// 	return;
//     }

//     // insert before aux
//     node = reinterpret_cast<Node *>(static_cast<unsigned int>(sys_addr));
//     node->prev = aux->prev;
//     node->next = aux;
//     node->data(addr);
//     node->size(n);
//     if(static_cast<void *>(head()) == static_cast<void *>(aux)) head(node);
//     aux->prev = node;
//     try_merge(node);
//     inc_free_frames(n);

//     leave_critical_region();
// }

// void MMU_Common<10, 10, 12>::Frame_List::frame_free(CPU::Phy_Addr addr, int n) {
//     db<IA32_MMU>(TRC) << "IA32_MMU::Frame_List::frame_free(addr=" << addr << ",n=" << n << ")\n";

//     enter_critical_region();

//     CPU::Phy_Addr sys_addr = addr + 0x80000000;

//     Node * node = reinterpret_cast<Node *>(static_cast<unsigned int>(sys_addr));
//     node->size(n);
//     node->data(addr);
//     node->prev = tail();
//     node->next = reinterpret_cast<Node *>(0);
//     (tail())->next = node;
//     tail(node);
//     inc_free_frames(n);

//     leave_critical_region();
// }

// void MMU_Common<10, 10, 12>::Frame_List::try_merge(Node * node) {
//     db<IA32_MMU>(TRC) << "IA32_MMU::Frame_List::try_merge(node=" << node << ")\n";
//     if(node->prev && ((node->prev->data() + (sizeof(Page) * node->prev->size())) >= node->data())) {
//         node->prev->size(((node->data() + (sizeof(Page) * node->size())) - node->prev->data()) / sizeof(Page));
// 	node->prev->next = node->next;
// 	if(tail() == node) tail(node->prev);
// 	if(node->next) {
// 	    node->next->prev = node->prev;
// 	    goto try_next;
// 	}
//     }
//     if(node->next) {
//     try_next:
//         try_merge(node->next);
//     }
// }

// /*
//  * The following method prints the actual _free_frame_list state. This
//  * method only works if the debugged Aspect is WATCHED.
//  */
// /*
// void IA32_MMU::print_free_frame_list(OStream & cout) {
//     cout << "****************FREE FRAME LIST****************\n";
//     cout << "*nbr  data      size      prev      next      *\n";
//     Frame_List::Node * aux = _free_frame_list.head();
//     for(int i = 1; aux; i++, aux = aux->next)
//         cout << "*" << 
// 	  i << "  " << 
// 	  (unsigned int)aux->data() << "  " << 
// 	  aux->size() << "  " << 
// 	  aux->prev << "  " << 
// 	  aux->next << "  *\n";
//     cout << "**********************END**********************\n";
// }
// */

__END_SYS
