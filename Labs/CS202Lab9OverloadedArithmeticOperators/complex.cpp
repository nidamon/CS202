/*complex.cpp
Nathan Damon
CS 202
2/18/2021
This is the cpp file for the complex class
*/

#include "complex.hpp"

Complex::Complex(double real, double imag) : _real(real), _imag(imag) 
{

}

std::ostream& operator<<(std::ostream& os, const Complex& rhs)
{
	return os << rhs._real << " + " << rhs._imag << "i";
}

Complex& Complex::operator+=(const Complex& rhs)
{
	_real += rhs._real;
	_imag += rhs._imag;
	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex Temp = lhs;
	Temp += rhs;
	return Temp;
}