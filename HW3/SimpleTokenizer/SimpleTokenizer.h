/*SimpleTokenizer.h
Nathan Damon
CS 202
2/21/2021
This is the header file for the SimpleTokenizer program
*/

#ifndef SIMPLETOKENIZER_HPP
#define SIMPLETOKENIZER_HPP

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <istream>
using std::istream;
using std::ostream;

struct TokenAndPosition
{
	string _token;
	int _line;
	unsigned int _column;
};

vector<string> lineToTokens(const string& line);
vector<TokenAndPosition> readLines(istream& is);
void printTokens(ostream& os, const vector<TokenAndPosition>& tokens);

#endif // !SIMPLETOKENIZER_HPP

