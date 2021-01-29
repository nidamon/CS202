/*main.cpp
Nathan Damon
CS 202
1/28/2021
This is the main.cpp file for the Time It 1 program.
*/

#include "StopWatch.h"
#include <algorithm>
#include <random>
#include <vector>
using std::vector;

int main()
{
	StopWatch timer;

	std::random_device r;
	std::mt19937 gen(r());

	timer.Start();
	std::uniform_int_distribution<> dis10(1, 10);
	vector<int> container10(10);
	for (int i = 0; i < container10.size(); i++)
		container10[i] = i + 1;

	timer.Stop();
	timer.ReportMilliSec();
	cout << endl;

	timer.Start();
	std::uniform_int_distribution<> dis10000(1, 10000);
	vector<int> container10000(10000);
	for (int i = 0; i < container10000.size(); i++)
		container10000[i] = i + 1;

	timer.Stop();
	timer.ReportMilliSec();
	cout << endl;

	return 0;
}