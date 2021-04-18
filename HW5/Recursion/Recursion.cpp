/*Recursion.cpp
Nathan Damon
CS 202
4/17/2021
This is the cpp file for the recursion functions.
*/

#include "Recursion.h"

// Returns the nth number in the Fibonacci sequence
int fib(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	return fib(n - 1) + fib(n - 2);
}
