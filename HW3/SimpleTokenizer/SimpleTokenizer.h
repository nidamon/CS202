/*SimpleTokenizer.h
Nathan Damon
CS 202
2/21/2021
This is the header file for the SimpleTokenizer program
*/

#ifndef SIMPLETOKENIZER_HPP
#define SIMPLETOKENIZER_HPP

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <vector>
using std::vector;
#include <istream>
using std::istream;
using std::ostream;
#include <sstream>
using std::istringstream;
using std::stringstream;
#include <iomanip>
using std::setw;
#include <fstream>
using std::ifstream;


struct TokenAndPosition
{
	string _token;
	int _line;
	unsigned int _column;
};

// Splits line into tokens
vector<string> lineToTokens(const string& line);

// Takes an istream and returns a vector of tokens and their positions
vector<TokenAndPosition> readLines(istream& is);

// Prints the tokens and the line and column where they are located
void printTokens(ostream& os, const vector<TokenAndPosition>& tokens);

#endif // !SIMPLETOKENIZER_HPP

