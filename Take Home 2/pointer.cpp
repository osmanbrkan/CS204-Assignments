1#include <iostream>

using namespace std;

/*
  Author: Dilara Akdogan
  Date: Feb. 2014 
  Modified: Kamer Kaya, Sept., 2014
*/

int main()
{
	cout << "-------------------------------------------------" << endl;
	int * p_int, x;    // pointer with no memory allocation // x is an integer not a pointer

	p_int = new int;	// memory allocation
	*p_int = 1;		// change content of pointer
	cout << "Address that p_int contains (points to): " << p_int << endl;	    // address
	cout << "The content at the address " << *p_int << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int * p_int2 = new int; // new pointer memory allocation
	*p_int2 = 2;
	cout << "Address that p_int2 contains (points to): " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

		
	p_int2 = p_int; // assign one pointer to another
	cout << "p_int2 = p_int " << endl;
	cout << "Address that p_int2 contains (points to): " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int myInt = 3;
	p_int2 = &myInt;  // assign address of a variable to a pointer
	cout << "after p_int2 = &myInt (myInt = 3)" << endl;
	cout << "Address that p_int2 contains (points to): " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int myInt2 = 4; 
	*p_int2 = myInt2; // change content of pointer
	cout << "*p_int2 = myInt2 (myInt2 = 4) " << endl;
	cout << "Address that p_int2 contains (points to) " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content	
	cout << "-------------------------------------------------" << endl;
	return 0;
}
