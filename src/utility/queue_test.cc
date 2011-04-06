// EPOS-- Queue Utility Test Program

// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

#include <utility/ostream.h>
#include <utility/queue.h>

__USING_SYS;

struct Integer1 {
    Integer1(int _i) : i(_i), e(this) {}
    
    int i;
    Queue<Integer1>::Element e;
};

struct Integer2 {
    Integer2(int _i) : i(_i), e(this) {}
    
    int i;
    Ordered_Queue<Integer2>::Element e;
};

struct Integer3 {
    Integer3(int _i) : i(_i), e(this) {}
    
    int i;
    Relative_Queue<Integer3>::Element e;
};

int main()
{
    OStream cout;

    cout << "Queue Utility Test\n";

    Integer1 i1(1), i2(2), i3(3), i4(4);
    Integer2 j1(1), j2(2), j3(3), j4(4);
    Integer3 k1(1), k2(2), k3(3), k4(4);
    
    cout << "This is an integer queue:\n";
    Queue<Integer1> q1;
    cout << "Inserting the integer " << i1.i << " into the queue.\n";
    q1.insert(&i1.e);
    cout << "Inserting the integer " << i2.i << " into the queue.\n";
    q1.insert(&i2.e);
    cout << "Inserting the integer " << i3.i << " into the queue.\n";
    q1.insert(&i3.e);
    cout << "Inserting the integer " << i4.i << " into the queue.\n";
    q1.insert(&i4.e);
    cout << "The queue has now " << q1.size() << " elements.\n";
    cout << "Removing the element whose value is " << i2.i << "(" 
	 << q1.remove(&i2)->object()->i << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q1.remove()->object()->i 
	 << ")" << " from the queue.\n";
    cout << "Removing the element whose value is " << i4.i << "(" 
	 << q1.remove(&i4)->object()->i << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q1.remove()->object()->i
	 << ")" << " from the queue.\n";
    cout << "The queue has now " << q1.size() << " elements.\n";

    cout << "This is an ordered integer queue:\n";
    Ordered_Queue<Integer2> q2;
    cout << "Inserting the integer " << j1.i 
	 << " into the queue with order 2.\n";
    q2.insert(&j1.e, 2);
    cout << "Inserting the integer " << j2.i
	 << " into the queue with order 3.\n";
    q2.insert(&j2.e, 3);
    cout << "Inserting the integer " << j3.i
	 << " into the queue with order 4.\n";
    q2.insert(&j3.e, 4);
    cout << "Inserting the integer " << j4.i
	 << " into the queue with order 1.\n";
    q2.insert(&j4.e, 1);
    cout << "The queue has now " << q2.size() << " elements.\n";
    cout << "Removing the element whose value is " << j2.i << "(" 
	 << q2.remove(&j2)->object()->i << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q2.remove()->object()->i 
	 << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q2.remove()->object()->i
	 << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q2.remove()->object()->i 
	 << ")" << " from the queue.\n";
    cout << "The queue has now " << q2.size() << " elements.\n";

    cout << "This is an integer queue with relative ordering:\n";
    Relative_Queue<Integer3> q3;
    cout << "Inserting the integer " << j1.i 
	 << " into the queue with relative order 2.\n";
    q3.insert(&k1.e, 2);
    cout << "Inserting the integer " << j2.i 
	 << " into the queue with relative order 3.\n";
    q3.insert(&k2.e, 3);
    cout << "Inserting the integer " << j3.i
	 << " into the queue with relative order 4.\n";
    q3.insert(&k3.e, 4);
    cout << "Inserting the integer " << j4.i
	 << " into the queue with relative order 1.\n";
    q3.insert(&k4.e, 1);
    cout << "The queue has now " << q3.size() << " elements.\n";
    cout << "Removing the element whose value is " << j2.i << "(" 
	 << q3.remove(&k2)->object()->i << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q3.remove()->object()->i
	 << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q3.remove()->object()->i
	 << ")" << " from the queue.\n";
    cout << "Removing the queue's head (" << q3.remove()->object()->i
	 << ")" << " from the queue.\n";
    cout << "The queue has now " << q3.size() << " elements.\n";

    return 0;
}
