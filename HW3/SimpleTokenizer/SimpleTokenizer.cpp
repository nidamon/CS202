/*SimpleTokenizer.cpp
Nathan Damon
CS 202
2/21/2021
This is the cpp file for the SimpleTokenizer header
*/

#include "SimpleTokenizer.h"

// Splits line into tokens
vector<string> lineToTokens(const string& line)
{
	vector<string> tokens;
	stringstream check(line);
	string str;
	while (getline(check, str, ' '))
	{
		if (str[0] != '\0') // Prevents the extra spaces from being passed to tokens
			tokens.push_back(str);
	}
	return tokens;
}