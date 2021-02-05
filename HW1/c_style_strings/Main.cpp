/*Main.cpp
Nathan Damon
CS 202
2/4/2021
This is the Main.cpp file for the c_style_strings program.
*/

#include "c_style_strings.cpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	const char* string = "Happy Program";
	auto copy = strdups(string);

	cout << string << endl;
	cout << endl;
	cout << copy << endl;
	delete copy;

	return 0;
}