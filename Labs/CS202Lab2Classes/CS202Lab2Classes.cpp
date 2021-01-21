/*CS202Lab2Classes.cpp
Nathan Damon
CS 202
1/19/2021
This the second lab of CS 202 that will make use of classes
*/

#include "Lab2.h"

void passObjectV(Lab2 Lab); // Pass by value
void passObjectR(Lab2& Lab); // Pass by reference
void passObjectRC(const Lab2& Lab); // Pass by reference to const
Lab2 returnByValue(); // Return an object by value

int main()
{
	Lab2 L;

	Lab2 K(L);

	Lab2 J(5); // Gives J a vector of 5 zeros

	cout << endl;

	passObjectV(L);

	cout << endl;

	passObjectR(L);

	cout << endl;

	passObjectRC(K);

	cout << endl;

	L = returnByValue();

	cout << endl;

	vector<Lab2> labVector;
	labVector.reserve(5);

	Lab2 m;
	for (int i = 0; i < 5; i++)
	{
		labVector.push_back(m);
	}

	cout << endl;

	cout << "labVector's size: " << labVector.size() << endl;

	int end;
	std::cin >> end;
	return 0;
}

// Pass by value
void passObjectV(Lab2 Lab)
{
	cout << "Pass by value" << endl;
}

// Pass by reference
void passObjectR(Lab2& Lab)
{
	cout << "Pass by reference" << endl;
}

// Pass by reference to const
void passObjectRC(const Lab2& Lab)
{
	cout << "Pass by reference to const" << endl;
}

// Return an object by value
Lab2 returnByValue()
{
	Lab2 Lab;
	cout << "Return By Value" << endl;
	return Lab;
}