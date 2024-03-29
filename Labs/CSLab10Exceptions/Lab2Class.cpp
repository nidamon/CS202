/*Lab2Class.cpp
Nathan Damon
CS 202
2/16/2021
This is the cpp file for the lab2 class
*/

#include "Lab2Class.h"

int Lab2::_numLab2Objects = 0; // Definition of static variable

void Lab2::getNumOfObjects()
{
	cout << _numLab2Objects << endl;
}

Lab2::Lab2() : _name("default")
{
	cout << "Called Lab2 default constructor." << endl;
	_numLab2Objects += 1;
	if(_numLab2Objects > 5)
		throw std::runtime_error{ "Lab2() threw std::runtime_error" };
}

Lab2::Lab2(const Lab2& orig) : _name(orig._name), _data(orig._data)
{
	cout << "Called Lab2 copy constructor." << endl;
	_numLab2Objects += 1;
}

Lab2::Lab2(string str) : _name(str)
{
	cout << "Called Lab2 name constructor. Name is \"" << _name << "\"." << endl;
	_numLab2Objects += 1;
}

Lab2::Lab2(string str, double value) : _name(str), _data(value)
{
	cout << "Called Lab2 data constructor. Name is \"" << _name << "\" and data is \"" << _data << "\"." << endl;
	_numLab2Objects += 1;
}

Lab2::~Lab2()
{
	cout << "Called Lab2 destructor. Goodbye \"" << _name << "\"." << endl;
	_numLab2Objects -= 1;
	cout << "numLab2Objects = " << _numLab2Objects << endl;
}

void Lab2::printStuff()
{
	cout << "\"Stuff\" has been printed." << endl;
}

double Lab2::getData() const
{
	return _data;
}

ostream& operator<<(ostream& os, const Lab2& lab)
{
	return os << "This is the name and data of the lab: \"" << lab._name << "\" " << lab._data;
}

Lab2 Lab2::operator+ (const Lab2& rhs) const
{
	return Lab2("return", _data + rhs.getData());
}