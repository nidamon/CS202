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
	Lab2 lab;
	Lab2* p = &lab;

	std::unique_ptr<Lab2> uLab(new Lab2("Uni"));

}