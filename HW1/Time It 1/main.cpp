/*main.cpp
Nathan Damon
CS 202
1/28/2021
This is the main.cpp file for the Time It 1 program.
*/

#include "StopWatch.h"
#include <algorithm>
//#include <string>
//#include <functional>
#include <random>
#include <vector>
using std::vector;

void runFive(StopWatch & Timer, const int range, const vector<int>& container, const int searchType, const int goal);

int main()
{
	std::random_device r;
	std::mt19937 gen(r());

	int range = 10000;
	vector<int> container(range);
	std::uniform_int_distribution<> dis(1, range);

	cout << "Filling the vector with random values after timer start." << endl;
	StopWatch Timer;
	for (int i = 0; i < container.size(); i++)
		container[i] = dis(gen); // Fill with values between 1 and range

	Timer.ReportMilliSec();
	cout << endl;

	Timer.Start();
	std::sort(container.begin(), container.end());
	Timer.Stop();
	Timer.ReportMilliSec();
	cout << endl;

	int searchType = 2; // Specifies the algorithm used to search

	runFive(Timer, range, container, searchType, dis(gen));

	return 0;
}

// Uses the specified algorithm to search through the container 5 times and displays the average time
void runFive(StopWatch& Timer, const int range, const vector<int>& container, const int searchType, const int goal)
{
	double timeCounted = 0.0;

	switch (searchType)
	{
	//case 1:
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if ()
	//	}
	case 2:
		for (int i = 0; i < 5; i++)
		{
			Timer.Start();
			if (std::binary_search(container.begin(), container.end(), goal))
			{
				Timer.Stop();
				cout << "Found the item." << endl;
			}
			else
			{
				Timer.Stop();
				cout << "Did not find the item." << endl;
			}

			timeCounted += Timer.ReportMilliSec();
		}
	default:
		break;
	}

	double avergeTime = timeCounted / 5.0;
	cout << "Average time taken = " << avergeTime << endl;
}