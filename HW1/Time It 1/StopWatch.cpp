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