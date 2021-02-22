/*SimpleTokenizerMain.cpp
Nathan Damon
CS 202
2/21/2021
This is the Main file for the Simple Tokenizer program
*/

#include "SimpleTokenizer.h"

int main()
{
	bool bfileInput = false;

	if (bfileInput)
	{
		// Read file
	}
	else
	{
		string line;
		getline(std::cin, line);
		istringstream stream(line);

		auto vecOfTokens = readLines(stream);
		printTokens(std::cout, vecOfTokens);
	}
	return 0;
}