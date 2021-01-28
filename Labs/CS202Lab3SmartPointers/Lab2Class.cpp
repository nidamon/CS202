/*Lab2Class.cpp
Nathan Damon
CS 202
1/19/2021
This is the cpp file for the lab2 class
*/

#include "Lab2Class.h"

Lab2::Lab2() : _name("default")
{
	cout << "Called Lab2 default constructor." << endl;
}

Lab2::Lab2(const Lab2& orig)
{
	cout << "Called Lab2 copy constructor." << endl;
}

Lab2::Lab2(string str) : _name(str)
{
	cout << "Called Lab2 name constructor. Name is \"" << _name << "\"." << endl;
}

Lab2::~Lab2()
{
	cout << "Called Lab2 destructor. Goodbye \"" << _name << "\"." << endl;
}

void Lab2::printStuff()
{
	cout << "\"Stuff\" has been printed." << endl;
}