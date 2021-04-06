/*Lab15Main.cpp
Nathan Damon
CS 202
4/6/2021
This is the Wrapper.h file for lab 15
*/

#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

template<typename T>
class Wrapper
{
public:
	Wrapper(T value);

	T getValue();

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Wrapper<T>& rhs);

private:
	T _variable;
};

template<typename T>
Wrapper<T>::Wrapper(T value) : _variable{ value } {}

template<typename T>
T Wrapper<T>::getValue() { return _variable; }

template<typename T>
std::ostream& operator<<(std::ostream& os, const Wrapper<T>& rhs)
{
	return os << rhs._variable;
}

