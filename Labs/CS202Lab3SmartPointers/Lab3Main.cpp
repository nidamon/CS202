/*Lab3Main.cpp
Nathan Damon
CS 202
1/26/2021
This the third lab of CS 202 that will make use of pointers.
*/

#include "Lab2Class.h"
#include <memory>

int main()
{
	cout << "Raw pointer... " << endl;
	Lab2 lab;
	Lab2* p = &lab;

	cout << endl;
	cout << "Unique pointer... " << endl;
	std::unique_ptr<Lab2> uLab1(new Lab2("Uni"));

	cout << endl;
	cout << "Created Unique pointer #2" << endl;
	std::unique_ptr<Lab2> uLab2;

	cout << endl;
	cout << "Transferring ownership of \"Uni\" to Unique pointer #2" << endl;
	uLab2 = std::move(uLab1);
}