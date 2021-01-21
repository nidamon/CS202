/*CS 202 Lab 1.cpp
Nathan Damon
CS 202
1/14/2021
This the first lab of CS 202 that will use several control structures
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <random>
using std::random_device;


void randomize(int& variable, random_device& r, int range);


int main()
{
	random_device r;

	int value = 0;
	randomize(value, r, 15);

	cout << "If statement" << endl;
	if (value - 10 < 0)
		cout << "value is less than 10" << endl;
	else
		cout << "value is greater than 10" << endl;
	cout << endl;

	cout << "Switch" << endl;
	switch (value/5) // changes variable value
	{
	case -2:
		value += 10;
		break;
	case -1:
		value += 5;
		break;
	case 0:
		// value does not change here
		break;
	case 1:
		value -= 5;
		break;
	default:
		cout << "Something is not quite right with this switch..." << endl;
		break;
	}
	cout << endl;

	cout << "Do while" << endl;
	do
	{
		value++;
		cout << " value = " << value << endl;
	} while (value % 5 != 0);
	cout << endl;

	cout << "value is now " << value << endl;

	int bigRand = 0;

	randomize(bigRand, r, 1000);

	cout << "A new variable bigRand is " << bigRand << endl;

	cout << "For loop" << endl;
	for (int i = 1; i < 5; i++)
	{
		value *= i;
		cout << "value is " << value << endl;
	}
	cout << endl;

	vector<int> box;

	cout << "While loop" << endl;
	int numLeft = value * bigRand;
	while (numLeft > 2)
	{
		box.push_back(numLeft);
		numLeft -= (numLeft / 2);
	}
	cout << endl;
	
	cout << "Range based for loop" << endl;
	for (auto i : box)
		cout << i << " ";
	cout << endl;

}



void randomize(int& variable, random_device& r, int range)
{
	cout << "function randomize called" << endl;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, range);
	variable = uniform_dist(e1);
	cout << endl;
}
