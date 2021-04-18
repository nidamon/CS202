/*Recursion.h
Nathan Damon
CS 202
4/17/2021
This is the header file for the recursion functions.
*/
#ifndef RECURSION_HPP
#define RECURSION_HPP

#include <iostream>
using std::cout;
using std::endl;

// Returns the nth number in the Fibonacci sequence using recursion
int fib(int n);

// Returns the nth number in the Fibonacci sequence using a loop
int fib_loop(int n);

// Returns Ackermann's number
int ack(int m, int n);

#endif // !RECURSION_HPP
