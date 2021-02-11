/*Main.cpp
Nathan Damon
CS 202
2/10/2021
This is the main file for Memory Layout
*/

#include <iostream>
using std::cout;
using std::endl;

void printPointer(int i);

int main()
{
	int x = 5;
	printPointer(x);
	return 0;
}

// Prints the value and location in memory of the variable passed to it
void printPointer(int i) 
{
	int* iptr = &i;
	// The unary * operator dereferences the pointer
	std::cout << "i  = " << *iptr << endl;
	std::cout << "&i = " << iptr << endl;
}