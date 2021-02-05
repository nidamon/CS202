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

	for (int containerType = 0; containerType < 3; containerType++)
	{
		cout << "------------------------------------------" << endl; // Adds a section title for each container type

		if (containerType == 0)
			cout << "ContainerType is vector." << endl;
		if (containerType == 1)
			cout << "ContainerType is list." << endl;
		if (containerType == 2)
			cout << "ContainerType is deque." << endl;

		cout << "------------------------------------------" << endl;


		for (int book = 0; book < 5; book++)
		{
			cout << endl;
			cout << "------------------------------------------------------------------------------------" << endl; // Adds a section title for each container type
			cout << vBooks[book] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;

			vector<string> vWords; // Initializing them all here so they are reinitialize each time.
			list<string> lWords;
			deque<string> dWords;

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
							{ // Fills a container based on the type specified by the outer most for loop
								if (containerType == 0)
									vWords.push_back(word);
								if (containerType == 1)
									lWords.push_back(word);
								if (containerType == 2)
									dWords.push_back(word);
							}
							else // If not instream, then end of line
								break;
						}
					}
				}
			}
			Timer.Stop();
			Timer.ReportMilliSec();
			cout << endl;

			bool found = false;
			string strToFind = "strToFind";
			// Gets a range based on the max of the sizes of the vector, list, and deque as only one should have more than zero
			std::uniform_int_distribution<> dis(0, (std::max(vWords.size(), std::max(lWords.size(), dWords.size())) - 1));

			if (containerType == 0) // Gets a range based on the vector's size
				strToFind = vWords[dis(gen)]; // Get a random word (string) from the vector

			if (containerType == 1) // Gets a range based on the list's size
			{
				int randValue = dis(gen);
				for (string word : lWords) // Get a random word (string) from the list
				{
					if (randValue == 0)
						strToFind = word;
					randValue--;
				}
			}

			if (containerType == 2) // Gets a range based on the deque's size
				strToFind = dWords[dis(gen)]; // Get a random word (string) from the deque

			

			cout << "Searching for the word: " << strToFind << endl;

			Timer.Start();

			if (containerType == 0) // Find in vector
				found = (std::find(vWords.begin(), vWords.end(), strToFind) != vWords.end());
			if (containerType == 1) // Find in list
				found = (std::find(lWords.begin(), lWords.end(), strToFind) != lWords.end());
			if (containerType == 2) // Find in deque
				found = (std::find(dWords.begin(), dWords.end(), strToFind) != dWords.end());

			Timer.Stop();
			Timer.ReportMilliSec();

			if (found)
				cout << "Found the word: " << strToFind << endl;
			else
				cout << "Did not find the word: " << strToFind << endl;
			cout << endl;


			cout << "Begining to sort." << endl;
			Timer.Start();

			if (containerType == 0) // Sort vector
				std::sort(vWords.begin(), vWords.end());
			if (containerType == 1) // Sort list
				lWords.sort();
			if (containerType == 2) // Sort deque
				std::sort(dWords.begin(), dWords.end());

			Timer.Stop();
			Timer.ReportMilliSec();
			cout << endl;

			cout << endl;
		}
	}

	return 0;
}