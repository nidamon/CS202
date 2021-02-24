/*Money.hpp
Nathan Damon
2/23/2021
This is the header file for the Money Class
*/

#ifndef MONEY_HPP
#define MONEY_HPP

#include <sstream>

class Money
{
    friend bool operator==(const Money& lhs, const Money& rhs);
    friend bool operator>(const Money& lhs, const Money& rhs);
    friend Money operator+(const Money& lhs, const Money& rhs);
    friend Money operator-(const Money& rhs);
    friend std::ostream& operator<<(std::ostream & os, const Money& rhs);

public:
    Money(); // $0.00
    Money(int dollars, int cents);
    Money(double cash);

    Money& operator+=(const Money& rhs);
    Money& operator-=(const Money& rhs);
    Money& operator*=(const double rhs);
    Money& operator/=(const double rhs);

private:
    int _totalInCents;
};

bool operator<(const Money& lhs, const Money& rhs);
bool operator>=(const Money& lhs, const Money& rhs);
bool operator<=(const Money& lhs, const Money& rhs);
bool operator!=(const Money& lhs, const Money& rhs);

Money operator-(const Money& lhs, const Money& rhs);
Money operator*(Money lhs, double rhs);
Money operator*(const double lhs, Money rhs);
Money operator/(Money lhs, const double rhs);

#endif // !MONEY_HPP

