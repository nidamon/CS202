/*StopWatch.cpp
Nathan Damon
CS 202
1/28/2021
This is the cpp file for the StopWatch class.
*/

#include "StopWatch.h"

StopWatch::StopWatch() : _timeStart{ steady_clock::now() }, _timeSpan{ 0.0 }
{

}

// Restarts the clock
void StopWatch::Start()
{
	cout << "Restarting the clock... " << endl;
	_timeStart = steady_clock::now();
}

// Records the end time for an event
void StopWatch::Stop()
{
	steady_clock::time_point checkTime = steady_clock::now();
	_timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(checkTime - _timeStart);
}

// Prints the time in seconds as a double
void StopWatch::ReportSec()
{
	if (_timeSpan.count() == 0.0)
		Stop();
	cout << "StopWatch Report: " << _timeSpan.count() << " sec." << endl;
}

// Prints the time in milliseconds as a double
void StopWatch::ReportMilliSec()
{
	if (_timeSpan.count() == 0.0)
		Stop();
	cout << "StopWatch Report: " << (_timeSpan.count() * 1000.0) << " millisec." << endl;
}