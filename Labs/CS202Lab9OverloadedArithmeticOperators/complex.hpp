/*complex.hpp
Nathan Damon
CS 202
2/18/2021
This is the header file for the complex class
*/

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex
{
	friend std::ostream& operator<<(std::ostream&, const Complex& rhs);
	friend Complex operator+(const Complex& lhs, const Complex& rhs);

public:
	Complex(double real, double imag = 0);

	Complex& operator+=(const Complex& rhs);

private:
	double _real;
	double _imag;
};

#endif
