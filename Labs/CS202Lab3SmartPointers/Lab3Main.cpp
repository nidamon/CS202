/*Lab3Main.cpp
Nathan Damon
CS 202
1/26/2021
This the third lab of CS 202 that will make use of pointers.
*/

#include "Lab2Class.h"
#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

int main()
{
	cout << "Creating raw pointer." << endl;
	Lab2 *p = new Lab2("RawPtr");
	delete p;

	cout << endl;
	cout << "Creating unique_ptr." << endl;
	unique_ptr<Lab2> uLab1 = make_unique<Lab2>("Uni");

	cout << endl;
	cout << "Transferring ownership of \"Uni\" to a new unique_ptr." << endl;
	unique_ptr<Lab2> uLab2 = std::move(uLab1);

	cout << endl;
	cout << "Calling member function \"printStuff\"." << endl;
	uLab2->printStuff();

	cout << endl;
	cout << "Creating shared_ptr." << endl;
	shared_ptr<Lab2> sLab1 = make_shared<Lab2>("Duo");

	cout << endl;
	cout << "Creating another shared_ptr to the same object." << endl;
	shared_ptr<Lab2> sLab2(sLab1);



	cout << endl;
}