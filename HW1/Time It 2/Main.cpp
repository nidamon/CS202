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
	StopWatch Timer;

	vector<string> vWords;


	ifstream fin("The Strange Case Of Dr. Jekyll And Mr. Hyde, by Robert Louis Stevenson.txt");
	if (!fin)
	{
		cout << "Did not open the file" << endl;
		return 0;
	}
	else
	{
		string word; // Used for getting and storing words into the container
		int count = 20;	
		
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
					{
						vWords.push_back(word);
						cout << vWords.back() << " " ;
					}
					else
						break;
				}
			}
			cout << endl;
			count--;
			if (count <= 0)
				break;
			
		}
	}

	Timer.Stop();
	Timer.ReportMilliSec();
	cout << vWords.size() << endl;

	return 0;
}