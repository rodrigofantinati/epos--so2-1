// EPOS-- List Utility Test Program

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/ostream.h>
#include <utility/list.h>

__USING_SYS;

struct Integer1 {
    Integer1(int _i) : i(_i), e(this) {}
    
    int i;
    List<Integer1>::Element e;
};

struct Integer2 {
    Integer2(int _i) : i(_i), e(this) {}
    
    int i;
    Ordered_List<Integer2>::Element e;
};

struct Integer3 {
    Integer3(int _i) : i(_i), e(this) {}
    
    int i;
    Relative_List<Integer3>::Element e;
};

struct Integer4 {
    Integer4(int _i, int _s) : e((Integer4 *)_i, _s) {}
    
    Grouping_List<Integer4>::Element e;
};

int main()
{
    OStream cout;

    cout << "List Utility Test\n";

    List<Integer1> l1;
    Integer1 i1(1), i2(2), i3(3), i4(4);
    cout << "This is a list of integers:\n";
    cout << "Inserting the integer " << i1.i << " into the list.\n";
    l1.insert_tail(&i1.e);
    cout << "Inserting the integer " << i2.i << " into the list.\n";
    l1.insert_tail(&i2.e);
    cout << "Inserting the integer " << i3.i << " into the list.\n";
    l1.insert_tail(&i3.e);
    cout << "Inserting the integer " << i4.i << " into the list.\n";
    l1.insert_tail(&i4.e);
    cout << "The list has now " << l1.size() << " elements.\n";
    cout << "Removing the element whose value is " << i2.i << "(" 
	 << l1.remove(&i2)->object()->i << ")" << " from the list.\n";
    cout << "Removing the list's head (" << l1.remove_head()->object()->i 
	 << ")" << ".\n";
    cout << "Removing the element whose value is " << i4.i << "(" 
	 << l1.remove(&i4)->object()->i << ")" << " from the list.\n";
    cout << "Removing the list's tail (" << l1.remove_tail()->object()->i
	 << ")" << ".\n";
    cout << "The list has now " << l1.size() << " elements.\n";

    Ordered_List<Integer2> l2;
    Integer2 j1(1), j2(2), j3(3), j4(4);
    cout << "This is an ordered list of integers:\n";
    cout << "Inserting the integer " << j1.i 
	 << " into the list with order 2.\n";
    l2.insert(&j1.e, 2);
    cout << "Inserting the integer " << j2.i
	 << " into the list with order 3.\n";
    l2.insert(&j2.e, 3);
    cout << "Inserting the integer " << j3.i
	 << " into the list with order 4.\n";
    l2.insert(&j3.e, 4);
    cout << "Inserting the integer " << j4.i
	 << " into the list with order 1.\n";
    l2.insert(&j4.e, 1);
    cout << "The list has now " << l2.size() << " elements.\n";
    cout << "Removing the element whose value is " << j2.i << "(" 
	 << l2.remove(&j2)->object()->i << ")" << " from the list.\n";
    cout << "Removing the list's head (" << l2.remove_head()->object()->i 
	 << ")" << ".\n";
    cout << "Removing the list's head (" << l2.remove_head()->object()->i
	 << ")" << ".\n";
    cout << "Removing the list's tail (" << l2.remove_tail()->object()->i 
	 << ")" << " from the list.\n";
    cout << "The list has now " << l2.size() << " elements.\n";

    Relative_List<Integer3> l3;
    Integer3 k1(1), k2(2), k3(3), k4(4);
    cout << "This is an list of integers with relative ordering:\n";
    cout << "Inserting the integer " << k1.i 
	 << " into the list with order 2.\n";
    l3.insert(&k1.e, 2);
    cout << "Inserting the integer " << k2.i 
	 << " into the list with order 3.\n";
    l3.insert(&k2.e, 3);
    cout << "Inserting the integer " << k3.i
	 << " into the list with order 4.\n";
    l3.insert(&k3.e, 4);
    cout << "Inserting the integer " << k4.i
	 << " into the list with order 1.\n";
    l3.insert(&k4.e, 1);
    cout << "The list has now " << l3.size() << " elements.\n";
    cout << "Removing the element whose value is " << k2.i << "(" 
	 << l3.remove(&k2)->object()->i << ")" << " from the list.\n";
    cout << "Removing the list's head (" << l3.remove_head()->object()->i
	 << ")" << ".\n";
    cout << "Removing the list's head (" << l3.remove_head()->object()->i
	 << ")" << ".\n";
    cout << "Removing the list's tail (" << l3.remove_tail()->object()->i
	 << ")" << " from the list.\n";
    cout << "The list has now " << l3.size() << " elements.\n";

    Grouping_List<int> l4;
    Grouping_List<int>::Element m1((int *)0, 2), m2((int *)16, 2), m3((int *)8, 2), m4((int *)24, 2);
    Grouping_List<int>::Element * d1, * d2;
    cout << "This is a grouping list of integers:\n";
    cout << "Inserting the integer group beginning with " << m1.object()
	 << " and spanning " << m1.size() << " elements into the list.\n";
    l4.insert_merging(&m1, &d1, &d2);
    if(d1)
	cout << "Element whose valeu was " << d1->object() << " merged\n";
    if(d2)
	cout << "Element whose valeu was " << d2->object() << " merged\n";
    cout << "Inserting the integer group beginning with " << m2.object()
	 << " and spanning " << m2.size() << " elements into the list.\n";
    l4.insert_merging(&m2, &d1, &d2);
    if(d1)
	cout << "Element whose valeu was " << d1->object() << " merged\n";
    if(d2)
	cout << "Element whose valeu was " << d2->object() << " merged\n";
    cout << "Inserting the integer group beginning with " << m3.object()
	 << " and spanning " << m3.size() << " elements into the list.\n";
    l4.insert_merging(&m3, &d1, &d2);
    if(d1)
	cout << "Element whose valeu was " << d1->object() << " merged\n";
    if(d2)
	cout << "Element whose valeu was " << d2->object() << " merged\n";
    cout << "Inserting the integer group beginning with " << m4.object()
	 << " and spanning " << m4.size() << " elements into the list.\n";
    l4.insert_merging(&m4, &d1, &d2);
    if(d1)
	cout << "Element whose valeu was " << d1->object() << " merged\n";
    if(d2)
	cout << "Element whose valeu was " << d2->object() << " merged\n";
    cout << "The list has now " << l4.size() << " elements that group " 
	 << l4.grouped_size() << " elements in total.\n";
    cout << "Removing one element from the list: "; 
    d1 = l4.search_decrementing(1);
    cout << d1->object() + d1->size() << ".\n";
    if(!d1->size())
	cout << "Element whose valeu was " << d1->object() << " deleted\n";
    cout << "Allocating six more elements from the list: "; 
    d1 = l4.search_decrementing(6);
    cout << d1->object() + d1->size() << ".\n";
    if(!d1->size())
	cout << "Element whose valeu was " << d1->object() << " deleted\n";
    cout << "Allocating one element from the list: ";
    d1 = l4.search_decrementing(1);
    cout << d1->object() + d1->size() << ".\n";
    if(!d1->size())
	cout << "Element whose valeu was " << d1->object() << " deleted\n";
    cout << "The list has now " << l4.size() << " elements that group " 
	 << l4.grouped_size() << " elements in total.\n";

    return 0;
}
