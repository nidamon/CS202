/*Money.hpp
Nathan Damon
2/23/2021
This is the header file for the Money Class
*/

#ifndef MONEY_HPP
#define MONEY_HPP

class Money
{
    friend bool operator==(const Money& lhs, const Money& rhs);
    friend bool operator>(const Money& lhs, const Money& rhs);
    friend bool operator+(const Money& lhs, const Money& rhs);

public:
    Money(); // $0.00
    Money(int dollars, int cents);
    Money(double cash);

    bool operator+=(const Money& rhs);

private:
    int _totalInCents;
};

bool operator<(const Money& lhs, const Money& rhs);
bool operator>=(const Money& lhs, const Money& rhs);
bool operator<=(const Money& lhs, const Money& rhs);
bool operator!=(const Money& lhs, const Money& rhs);

#endif // !MONEY_HPP

