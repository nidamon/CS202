/*Lab15Main.cpp
Nathan Damon
CS 202
4/6/2021
This is the main file for lab 15
*/

#include <sstream>
#include "Wrapper.h"


int main()
{
	Wrapper<int> w{ 2 };
	Wrapper<string>  s{ "Hello world!" };
	cout << w << " " << s << endl;
	return 0;
}