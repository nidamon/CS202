/*main.cpp
Nathan Damon
CS 202
1/28/2021
This is the main.cpp file for the Time It 1 program.
*/

#include "StopWatch.h"
#include <algorithm>
#include <string>
using std::string;
#include <random>
#include <vector>
using std::vector;

void runFive(StopWatch & Timer, const int range, const vector<int>& container, const int searchType, const vector<int> goal);

int main()
{
	std::random_device r;
	std::mt19937 gen(r());

	int range = 10000;
	vector<int> container(range);
	std::uniform_int_distribution<> dis(1, range);

	cout << "Filling the vector with random values after timer start." << endl;
	StopWatch Timer;
	for (int i = 0; i < (int)container.size(); i++)
		container[i] = dis(gen); // Fill with values between 1 and range

	Timer.ReportMilliSec(); // Get the time it takes to create the container
	cout << endl;

	Timer.Start(); 
	std::sort(container.begin(), container.end());
	Timer.Stop();
	Timer.ReportMilliSec(); // Get the time it takes to sort the container
	cout << endl;

	int valueToFind = container[dis(gen)];

	vector<string> types = { "Search", "Binary_search", "Find", "Include" };
	for (int searchType = 1; searchType < 5; searchType++)
	{
		cout << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << types[searchType - 1] << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << endl;
		runFive(Timer, range, container, searchType, { valueToFind });
	}

	cout << endl;
	return 0;
}

// Uses the specified algorithm to search through the container 5 times and displays the average time
void runFive(StopWatch& Timer, const int range, const vector<int>& container, const int searchType, const vector<int> goal)
{
	double timeCounted = 0.0;
	bool found = false;

	for (int i = 0; i < 5; i++)
	{
		switch (searchType)
		{
		case 1: // Search
			Timer.Start();
			found = (std::search(container.begin(), container.end(), goal.begin(), goal.end()) != container.end());
			Timer.Stop();
			break;

		case 2: // Binary_search
			Timer.Start();
			found = std::binary_search(container.begin(), container.end(), goal[0]);
			Timer.Stop();
			break;

		case 3: // Find
			Timer.Start();
			found = (std::find(container.begin(), container.end(), goal[0]) != container.end());
			Timer.Stop();
			break;

		case 4: // Include
			Timer.Start();
			found = std::includes(container.begin(), container.end(), goal.begin(), goal.end());
			Timer.Stop();
			break;
		default:
			break;
		}

		if (found)
		{
			cout << "Found the item: " << goal[0] << endl;
		}
		else
		{
			cout << "Did not find the item: " << goal[0] << endl;
		}	

		timeCounted += Timer.ReportMilliSec();
		cout << endl;
	}

	double avergeTime = timeCounted / 5.0;
	cout << "Average time taken = " << avergeTime << " millisec." << endl;
}