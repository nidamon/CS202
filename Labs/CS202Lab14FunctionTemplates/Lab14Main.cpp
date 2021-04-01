/*Lab14Main.cpp
Nathan Damon
CS 202
4/1/2021
This is the main file for lab 14
*/

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

template<typename T>
T twice(T x) { return x + x; }

string twice(const char* x)
{
	return string(x) + string(x);
}

int main()
{
	cout << twice(2) << endl;
	cout << twice(2.3) << endl;
	cout << twice(string("Hello")) << endl;
	cout << twice("World") << endl;
	return 0;
}