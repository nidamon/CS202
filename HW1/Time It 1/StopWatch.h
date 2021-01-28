/*StopWatch.h
Nathan Damon
CS 202
1/28/2021
This is the hpp file for the StopWatch class.
*/

#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;

class StopWatch
{
public:
	StopWatch(); // Starts the clock

	//void Start(); // Restarts the clock
	//void Stop(); // Records the end time for an event

	//void ReportSec(); // Prints the time in seconds as a double
	//void ReportMilliSec(); // Prints the time in milliseconds as a double
private:
	steady_clock::time_point _timeStart;
};


#endif