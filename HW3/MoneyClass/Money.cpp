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