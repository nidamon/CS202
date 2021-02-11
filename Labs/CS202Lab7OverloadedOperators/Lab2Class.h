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
#include <ostream>
using std::ostream;

class Lab2
{
	friend ostream& operator<<(ostream& os, const Lab2& lab);
public:
	Lab2();
	Lab2(string str);
	Lab2(string str, double value);
	Lab2(const Lab2& orig);
	~Lab2();

	void printStuff(); // Prints some text
	double getData() const;


	Lab2 operator+ (const Lab2& rhs) const;





	string _name;
private:
	double _data = 0.0;

};

ostream& operator<<(ostream& os, const Lab2& lab);

#endif
