/*StopWatch.cpp
Nathan Damon
CS 202
1/28/2021
This is the cpp file for the StopWatch class.
*/

#include "StopWatch.h"

StopWatch::StopWatch() : _timeStart{ steady_clock::now() }
{

}

// Restarts the clock
void StopWatch::Start()
{
	cout << "Restarting the clock... " << endl;
	_timeStart = steady_clock::now();
}

// Prints the time in seconds as a double
void StopWatch::ReportSec()
{
	steady_clock::time_point checkTime = steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(checkTime - _timeStart);
	cout << "StopWatch Report: " << time_span.count() << " sec." << endl;
}