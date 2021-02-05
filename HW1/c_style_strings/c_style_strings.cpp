/*Main.cpp
Nathan Damon
CS 202
2/4/2021
This is the c_style_strings.cpp file for the c_style_strings program.
*/

//#include <iostream>
//using std::cout;
//using std::endl;

// Copies a C-style string into memory it allocates dynamically (using new)
inline char* strdups(const char* s)
{
	int index = 0;
	while (true) // Get the size of the C string
	{
		if (s[index] == '\0')
			break;
		else
			index++;
	}
	char* duplicate = new char[index + 1];

	index = 0; // Reset the count
	while (true) // Copy letters to duplicate C string
	{
		duplicate[index] = s[index]; // Copy the chars one at a time
		if (s[index] == '\0')
			break;
		else
			index++;
	}

	return duplicate;
}

//// Finds the first occurrence of the C-style string x in s.
//char* findx(const char* s, char* x)
//{
//	
//}