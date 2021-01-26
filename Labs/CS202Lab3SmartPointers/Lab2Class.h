/*Lab2.h
Nathan Damon
CS 202
1/19/2021
This is the header file for the lab2 class
*/

#ifndef LAB_HPP
#define LAB_HPP

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

class Lab2
{
public:
	Lab2();
	Lab2(string str);
	Lab2(const Lab2& orig);
	~Lab2();

	void printStuff(); // Prints some text

	string _name;
private:

};

#endif
