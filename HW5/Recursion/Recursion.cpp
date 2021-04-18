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

// Returns the nth number in the Fibonacci sequence using a loop
int fib_loop(int n)
{
	int n_1 = 0;
	int n_2 = 1;
	int fibValue = 0;

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int nCount = 0;
	while (nCount != n)
	{
		fibValue = n_1 + n_2;
		n_2 = n_1;
		n_1 = fibValue;

		nCount++;
	}
	return fibValue;
}

// Returns Ackermann's number
int ack(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (m > 0 && n == 0)
		return ack(m - 1, 1);
	else if (m > 0 && n > 0)
		return ack(m - 1, ack(m, n - 1));
}