/*Money.cpp
Nathan Damon
2/23/2021
This is the cpp file for the Money Class
*/

#include "Money.hpp"

Money::Money() : _totalInCents(0) // $0.00
{}

Money::Money(int dollars, int cents) : _totalInCents(dollars * 100 + cents)
{}

Money::Money(double cash) // Rounded to nearest cent via truncation
{
	if (cash < 0.0)
		_totalInCents = (cash * 100 - 0.5);
	else
		_totalInCents = (cash * 100 + 0.5);
}



// OPERATORS BELOW 

// Friends
bool operator==(const Money& lhs, const Money& rhs)
{
	return lhs._totalInCents == rhs._totalInCents;
}

bool operator>(const Money& lhs, const Money& rhs)
{
	return lhs._totalInCents > rhs._totalInCents;
}

Money operator+(const Money& lhs, const Money& rhs)
{
	auto temp(lhs);
	temp += rhs;
	return temp;
}

Money operator-(const Money& rhs)
{
	return (-rhs._totalInCents);
}






// Class Public
Money& Money::operator+=(const Money& rhs)
{
	_totalInCents += rhs._totalInCents;
	return *this;
}

Money& Money::operator-=(const Money& rhs)
{
	_totalInCents += -rhs._totalInCents;
	return *this;
}

Money& Money::operator*=(const double rhs)
{
	double temp = double(_totalInCents) * rhs; // Multiply into a double
	if (temp < 0) // Check positive or negative
		_totalInCents = (temp - 0.5); // Round
	else
		_totalInCents = (temp + 0.5);
	return *this;
}

Money& Money::operator/=(const double rhs)
{
	_totalInCents /= rhs;
	return *this;
}



// Global

	// Booleans
bool operator<(const Money& lhs, const Money& rhs)
{
	return rhs > lhs;
}

bool operator>=(const Money& lhs, const Money& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const Money& lhs, const Money& rhs)
{
	return !(lhs > rhs);
}

bool operator!=(const Money& lhs, const Money& rhs)
{
	return !(lhs == rhs);
}


	// Arithmetic
Money operator-(const Money& lhs, const Money& rhs)
{
	auto temp(lhs);
	temp -= rhs;
	return temp;
}

Money operator*(Money lhs, double rhs)
{
	return lhs *= rhs;
}

Money operator*(const double lhs, Money rhs)
{
	return rhs * lhs;
}

Money operator/(Money lhs, const double rhs)
{
	return lhs /= rhs;
}

	// Stream
std::ostream& operator<<(std::ostream & os, const Money& rhs)
{
	double temp = double(rhs._totalInCents) / 100.0;
	if (rhs._totalInCents < 0)
	{
		os << "-";
		temp *= -1; // Make temp positive for output
	}
	if (rhs._totalInCents != 0)
		os << "$" << temp;
	else
		os << "$0.00";
	return os;
}