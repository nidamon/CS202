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
#include <vector>
using std::vector;

class Lab2
{
public:
	Lab2();
	Lab2(int x);
	Lab2(const Lab2& orig);
	~Lab2();

	vector<int> _values;
private:

};

#endif