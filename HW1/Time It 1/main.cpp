/*main.cpp
Nathan Damon
CS 202
1/28/2021
This is the main.cpp file for the Time It 1 program.
*/

#include "StopWatch.h"

int main()
{
	StopWatch timer;

	for (int i = 0; i < 1000; i++)
		cout << "#";

	cout << endl;

	timer.Stop();


	timer.ReportSec();
	timer.ReportMilliSec();

	return 0;
}