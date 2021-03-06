/*Main.cpp
Nathan Damon
CS 202
2/11/2021
This program will replace all the uppercase characters in the c-style 
string s with their lowercase equivalents.
*/

#include "../../HW1/c_style_strings/c_style_strings.cpp"
#include <iostream>
using std::cout;
using std::endl;

void to_lower(char* s);

int main()
{
	auto cString = strdups("Happy Program!");

	cout << cString << endl;
	to_lower(cString);
	cout << "Modified: " << cString << endl;
	cout << endl;
	delete cString;

	auto cStr1 = strdups("NO MORE ALL CAPITALIZATIONS!");
	auto cStr2 = strdups("There is no need for such LOUD YELLING!");
	auto cStr3 = strdups("i DoN't KnOw HoW tO tYpE wItHoUt AlTeRnAtInG cApS lOcK.");

	cout << cStr1 << endl;
	to_lower(cStr1);
	cout << "Modified: " << cStr1 << endl;
	cout << endl;

	cout << cStr2 << endl;
	to_lower(cStr2);
	cout << "Modified: " << cStr2 << endl;
	cout << endl;

	cout << cStr3 << endl;
	to_lower(cStr3);
	cout << "Modified: " << cStr3 << endl;
	cout << endl;

	delete cStr1;
	delete cStr2;
	delete cStr3;

	return 0;
}



// Makes all uppercase characters into lowercase
void to_lower(char* s)
{
	int index = 0;
	while (true) // Move through char* s and check if elements are in the range of uppercase characters
	{
		if (s[index] >= 'A' && s[index] <= 'Z')
		{
			s[index] += 32; // Shift to the lowercase character
		}
		if (s[index] == '\0') // End of the given string
			return;
		else
			index++;
	}
}