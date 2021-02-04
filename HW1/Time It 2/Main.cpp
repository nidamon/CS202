/*Main.cpp
Nathan Damon
CS 202
2/3/2021
This the file that will contain main() for the Time It II program.
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
using std::getline;
#include <fstream>
using std::ifstream;
using std::ios;
#include <random>
#include <algorithm>

#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
	
#include "../Time It 1/StopWatch.h"
#include "../Time It 1/StopWatch.cpp"

int main()
{
	// Contains the five books to read through
	vector<string> vBooks = {
		"Alice’s Adventures in Wonderland, by Lewis Carroll.txt",
		"The Call of the Wild, by Jack London.txt",
		"The Strange Case Of Dr. Jekyll And Mr. Hyde, by Robert Louis Stevenson.txt",
		"The Time Machine, by H. G. Wells.txt",
		"The Yellow Wallpaper, by Charlotte Perkins Gilman.txt"
	};

	std::random_device r;
	std::mt19937 gen(r());

	StopWatch Timer;


	for (int book = 4; book < 5; book++)
	{
		vector<string> vWords;
		ifstream fin(vBooks[book]);
		if (!fin)
		{
			cout << "Did not open the file" << endl;
			return 0;
		}
		else
		{
			string word; // Used for getting and storing words into the container

			Timer.Start();
			while (true)
			{
				string line;
				getline(fin, line);
				if (!fin)
				{
					if (fin.eof())
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
				else
				{
					istringstream instream(line);
					while (true) // Break the line into words and fill the container
					{
						instream >> word;
						if (instream)
							vWords.push_back(word);
						else
							break;
					}
				}
			}
		}
		Timer.Stop();
		Timer.ReportMilliSec();
		cout << endl;

		bool found = false;
		std::uniform_int_distribution<> dis(0, vWords.size() - 1);
		string strToFind = vWords[dis(gen)]; // Get a random word (string) from the vector
		cout << "Searching for the word: " << strToFind << endl;

		Timer.Start();
		found = (std::find(vWords.begin(), vWords.end(), strToFind) != vWords.end());
		Timer.Stop();
		Timer.ReportMilliSec();

		if (found)
			cout << "Found the word: " << strToFind << endl;
		else
			cout << "Did not find the word: " << strToFind << endl;
		cout << endl;

		cout << "Begining to sort." << endl;
		Timer.Start();
		std::sort(vWords.begin(), vWords.end());
		Timer.Stop();
		Timer.ReportMilliSec();
		cout << endl;

		cout << endl;
	}

	return 0;
}