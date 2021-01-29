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

void runFive(const int range, const vector<int>& container, const int searchType, std::mt19937& gen);

int main()
{
	std::random_device r;
	std::mt19937 gen(r());

	int range = 10000;
	vector<int> container(range);
	for (int i = 0; i < container.size(); i++)
		container[i] = i + 1;

	int searchType = 2; // Specifies the algorithm used to search

	runFive(range, container, searchType, gen);

	return 0;
}

// Uses the specified algorithm to search through the container 5 times and displays the average time
void runFive(const int range, const vector<int>& container, const int searchType, std::mt19937& gen)
{
	StopWatch Timer;

	std::uniform_int_distribution<> dis(1, range);
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
			if (std::binary_search(container.begin(), container.end(), dis(gen)));

			Timer.Stop();

			timeCounted += Timer.ReportMilliSec();
		}
	default:
		break;
	}

	double avergeTime = timeCounted / 5.0;
	cout << "Average time taken = " << avergeTime << endl;
}