/*Lab9Main.cpp
Nathan Damon
CS 202
2/18/2021
This is the main file for lab 9
*/

#include "complex.hpp"

int main()
{
	Complex num(5.25, 2.1);
	std::cout << "(" << num << ") + (";
	Complex value(8.2, -3);
	num += value;
	std::cout << value << ") = (" << num << ")" << std::endl;
	std::cout << 1 + Complex(2, 3) << std::endl;
	return 0;
}