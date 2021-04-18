/*RecursionMain.cpp
Nathan Damon
CS 202
4/17/2021
This is the main file for the recursion program.
*/

#include "Recursion.h"


int main()
{
	cout << "Fibonacci with recursion: ";
	for (int n = 0; n < 20; n++)
		cout << fib(n) << " ";
	cout << endl;
	cout << "Fibonacci with loop:      ";
	for (int n = 0; n < 20; n++)
		cout << fib_loop(n) << " ";
	cout << endl;

	cout << "Ackermanns number with recursion: ";
	for (int m = 0; m < 4; m++)
		for (int n = 0; n < 4; n++)
			cout << ack(m, n) << " ";
	cout << endl;
}