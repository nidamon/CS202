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

bool operator==(const Money& lhs, const Money& rhs)
{
	return lhs._totalInCents == rhs._totalInCents;
}

bool operator>(const Money& lhs, const Money& rhs)
{
	return lhs._totalInCents > rhs._totalInCents;
}

bool operator<(const Money& lhs, const Money& rhs)
{
	return rhs < lhs;
}