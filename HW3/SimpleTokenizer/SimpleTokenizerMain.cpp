/*SimpleTokenizerMain.cpp
Nathan Damon
CS 202
2/21/2021
This is the Main file for the Simple Tokenizer program
*/

#include "SimpleTokenizer.h"

int main()
{

	auto vec = lineToTokens("This     is a test of the      lineToToken function.");

	for (auto& i : vec)
	{
		cout << i << endl;
	}

	cout << endl;

	return 0;
}