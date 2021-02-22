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

// Takes an istream and returns a vector of tokens and their positions
vector<TokenAndPosition> readLines(istream& is)
{
	vector<TokenAndPosition> tokenPos;
	int lineCount = 0;
	while (true)
	{
		lineCount++;

		string line;
		getline(is, line);
		if (!is) // Check istream
			break;
		vector<string> tokens = lineToTokens(line);
		for (auto& token : tokens)
		{
			TokenAndPosition temp;
			temp._token = token;
			temp._line = lineCount;
			temp._column = line.find(token) + 1; // Find column where token starts
			tokenPos.push_back(temp);
		}
	}
	return tokenPos;
}	

// Prints the tokens and the line and column where they are located
void printTokens(ostream& os, const vector<TokenAndPosition>& tokens)
{
	for (auto& token : tokens)
		os << " Line " << setw(3) << token._line << ", Column " << setw(3) << token._column << ": \"" << token._token << "\"\n";
}