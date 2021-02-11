/*Lab7Main.cpp
Nathan Damon
CS 202
2/11/2021
This is the main file for lab 7
*/

#include "../CS202Lab3SmartPointers/Lab2Class.h"
#include <ostream>
using std::ostream; 

int main()
{
	const Lab2 lab("Lab7", 3.14);
	cout << lab << endl;

	return 0;
}