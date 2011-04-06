// EPOSi-- Queue Utility Declarations

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

// Queue is a traditional queue, with insertions at the tail
// and removals either from the head or from specific objects 

// Ordered_Queue is an ordered queue, i.e. objects are inserted
// in-order based on the integral value of "element.rank". Note that "rank"
// implies an order, but does not necessarily need to be "the absolute order"
// in the queue; it could, for instance, be a priority information or a 
// time-out specification. Insertions must first tag "element" with "rank".
// Removals are just like in the traditional queue. Elements of both Queues
// may be exchanged.
// Example: insert(B,7);insert(C,9);insert(A,4)
// +---+		+---+	+---+	+---+
// |obj|		| A |-->| B |-->| C |
// + - +       head -->	+ - +	+ - +	+ - + <-- tail
// |ord|		| 4 |<--| 7 |<--| 9 |
// +---+ 		+---+	+---+	+---+

// Relative Queue is an ordered queue, i.e. objects are inserted
// in-order based on the integral value of "element.rank" just like above.
// But differently from that, a Relative Queue handles "rank" as relative 
// offsets. This is very useful for alarm queues. Elements of Relative Queue
// cannot be exchanged with elements of the other queues described earlier.
// Example: insert(B,7);insert(C,9);insert(A,4)
// +---+		+---+	+---+	+---+
// |obj|		| A |-->| B |-->| C |
// + - +       head -->	+ - +	+ - +	+ - + <-- tail
// |ord|		| 4 |<--| 3 |<--| 2 |
// +---+ 		+---+	+---+	+---+

// Scheduling Queue is an ordered queue whose ordering criterion is externally
// definable and for which selecting methods are defined (e.g. choose). This
// utility is most useful for schedulers, such as CPU or I/O.

#ifndef __queue_h
#define	__queue_h

#include "list.h"
#include "spin.h"

__BEGIN_SYS

// Wrapper for non-atomic queues  
template <typename List, bool atomic>
class Queue_Wrapper: private List
{
public:
    typedef typename List::Object_Type Object_Type;
    typedef typename List::Element Element;

public:
    using List::empty;
    using List::size;
    using List::head;
    using List::tail;
    using List::insert;
    using List::remove;
    using List::search;
};


// Wrapper for atomic queues  
template <typename List>
class Queue_Wrapper<List, true>: private List
{
public:
    typedef typename List::Object_Type Object_Type;
    typedef typename List::Element Element;

public:
    bool empty() {
	_lock.acquire(); 
	bool tmp = List::empty();
	_lock.release();
	return tmp;
    }
    unsigned int size() {
	_lock.acquire(); 
	unsigned int tmp = List::size();
	_lock.release();
	return tmp;
    }

    Element * head() { 
	_lock.acquire(); 
	Element * tmp = List::head();
	_lock.release();
	return tmp;
    }
    Element * tail() { 
	_lock.acquire(); 
	Element * tmp = List::tail();
	_lock.release();
	return tmp;
    }

    void insert(Element * e) { 
	_lock.acquire(); 
	List::insert(e);
	_lock.release();
    }

    Element * remove() { 
	_lock.acquire(); 
	Element * tmp = List::remove();
	_lock.release();
	return tmp;
    }
    Element * remove(const Object_Type * obj) {
	_lock.acquire(); 
	Element * tmp = List::remove(obj); 
	_lock.release();
	return tmp;
    }

    Element * search(const Object_Type * obj) {
	_lock.acquire(); 
	Element * tmp = List::search(obj);
	_lock.release();
	return tmp;
    }

private:
    Spin _lock;
};


// Queue
template <typename T,
	  bool atomic = false,
	  typename El = List_Elements::Doubly_Linked<T> >
class Queue: public Queue_Wrapper<List<T, El>, atomic> {};


// Ordered Queue
template <typename T, 
	  typename R = List_Element_Rank, 
	  bool atomic = false,
	  typename El = List_Elements::Doubly_Linked_Ordered<T, R> >
class Ordered_Queue: public Queue_Wrapper<Ordered_List<T, R, El>, atomic> {};


// Relatively-Ordered Queue
template <typename T, 
	  typename R = List_Element_Rank, 
	  bool atomic = false,
	  typename El = List_Elements::Doubly_Linked_Ordered<T, R> >
class Relative_Queue: public Queue_Wrapper<Relative_List<T, R, El>, atomic> {};


// Scheduling Queue (non-atomic)
template <class T,
	  typename R = List_Element_Rank,  
	  bool atomic = false,
	  typename El  = List_Elements::Doubly_Linked_Ordered<T, R> >
class Scheduling_Queue: private Scheduling_List<T, R, El>
{
private:
    typedef Scheduling_List<T, R, El> Base;

public:
    typedef typename Base::Object_Type Object_Type;
    typedef typename Base::Element Element;

public:
    using Base::empty;
    using Base::size;
    using Base::head;
    using Base::tail;
    using Base::chosen;
    using Base::insert;
    using Base::remove;
    using Base::choose;
    using Base::choose_another;
};

// Scheduling Queue (atomic)
template <class T, typename R, typename El>
class Scheduling_Queue<T, R, true, El>: private Scheduling_List<T, R, El>
{
private:
    typedef Scheduling_List<T, R, El> Base;

public:
    typedef typename Base::Object_Type Object_Type;
    typedef typename Base::Element Element;

public:
    bool empty() {
	_lock.acquire(); 
	bool tmp = Base::empty();
	_lock.release();
	return tmp;
    }
    unsigned int size() {
	_lock.acquire(); 
	unsigned int tmp = Base::size();
	_lock.release();
	return tmp;
    }

    Element * head() { 
	_lock.acquire(); 
	Element * tmp = Base::head();
	_lock.release();
	return tmp;
    }
    Element * tail() { 
	_lock.acquire(); 
	Element * tmp = Base::tail();
	_lock.release();
	return tmp;
    }

    Element * volatile & chosen() { 
	_lock.acquire(); 
	Element * volatile & tmp = Base::chosen();
	_lock.release();
	return tmp;
    }

    void insert(Element * e) { 
	_lock.acquire(); 
	Base::insert(e);
	_lock.release();
    }

    Element * remove(Element * e) {
	_lock.acquire(); 
	Element * tmp = Base::remove(e); 
	_lock.release();
	return tmp;
    }
    Element * remove(const Object_Type * obj) {
	_lock.acquire(); 
	Element * tmp = Base::remove(obj); 
	_lock.release();
	return tmp;
    }

    Element * choose() { 
	_lock.acquire(); 
	Element * tmp = Base::choose();
	_lock.release();
	return tmp;
    }
    Element * choose_another() { 
	_lock.acquire(); 
	Element * tmp = Base::choose_another();
	_lock.release();
	return tmp;
    }
    Element * choose(Element * e) {
	_lock.acquire(); 
	Element * tmp = Base::choose(e);
	_lock.release();
	return tmp;
    }
    Element * choose(const Object_Type * obj) {
	_lock.acquire(); 
	Element * tmp = Base::choose(obj);
	_lock.release();
	return tmp;
    }

private:
    Spin _lock;
};

__END_SYS
 
#endif

