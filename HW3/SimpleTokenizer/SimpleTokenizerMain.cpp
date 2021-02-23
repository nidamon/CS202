/*SimpleTokenizerMain.cpp
Nathan Damon
CS 202
2/21/2021
This is the Main file for the Simple Tokenizer program
*/

#include "SimpleTokenizer.h"

int main(int argc, const char* argv[])
{
	if (argc >= 2)
	{
		ifstream fileIn(argv[1]); // Enter file name via command line
		if (!fileIn)
		{
			cout << "Did not open the file" << endl;
			return 0;
		}
		else
		{
			while (true)
			{
				string line;
				getline(fileIn, line);
				if (!fileIn)
				{
					if (fileIn.eof())
					{
						cout << "End of file." << endl;
						break;
					}
					else
					{
						cout << "Error reading file." << endl;
						break;
					}
				}

				auto vecOfTokens = readLines(fileIn);

				if (argc >= 3 && argv[2] == string("--lineonly"))
				{} // Nothing to do here
				else
					printTokens(std::cout, vecOfTokens);
			}
		}
	}
	return 0;
}