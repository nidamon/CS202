/*Main.cpp
Nathan Damon
CS 202
2/4/2021
This is the c_style_strings.cpp file for the c_style_strings program.
*/

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

// Finds the first occurrence of the C-style string x in s.
inline char* findx(const char* s, char* x)
{
	int index = 0;
	int subIndex = 0;
	while (true) // Move through const char* s and check if elements are equal to char* x
	{
		if (s[index] == x[subIndex])
		{
			if (x[subIndex + 1] == '\0') // Check if char* x is null terminated on the next char -> means that x is in s
				return strdups(x);
			subIndex++;
		}
		else
			subIndex = 0; // Reset subIndex when elements not equal

		if (s[index] == '\0') // End of the given string
			break;
		else
			index++;
	}

	return strdups("Not present");
}