/*Lab8Main.cpp
Nathan Damon
CS 202
2/16/2021
This is the main file for lab8.
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "Lab2Class.h"

void FunctionThatUsesAStaticVariable();

int main()
{
	// #1
	for (int i = 0; i < 10; i++)
		FunctionThatUsesAStaticVariable();
	cout << endl;

	// #3 - > See lab7

	// #4
	Lab2 room1;
	Lab2::getNumOfObjects();

	Lab2 room2("Named Lab");
	Lab2::getNumOfObjects();

	Lab2 room3("Third Room", 6.5);
	Lab2::getNumOfObjects();

	Lab2 room4(room3);
	Lab2::getNumOfObjects();
}

// Local Static variable
void FunctionThatUsesAStaticVariable() 
{
	static float localStatVar = 0.0f;
	localStatVar += 0.3f;
	cout << "localStatVar =  " << localStatVar << endl;
}