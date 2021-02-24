/*Money.hpp
Nathan Damon
2/23/2021
This is the header file for the Money Class
*/

#ifndef MONEY_HPP
#define MONEY_HPP

class Money
{
public:
    Money(); // $0.00
    Money(int dollars, int cents);
    Money(double cash);

private:
    int _totalInCents;
};


#endif // !MONEY_HPP

