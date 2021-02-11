/*Main.cpp
Nathan Damon
CS 202
2/10/2021
This is the main file for Memory Layout
*/

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

void printPointer(int& i);
void dataCompare(const string& type, int& one, int& two, int& three, int& four);

int main()
{
	// Looking at the static storage
	static int tic1 = 1;
	static int tic2 = 2;
	static int tic3 = 3;
	static int tic4 = 4;
	dataCompare("Static", tic1, tic2, tic3, tic4);

	return 0;
}

// Prints the value and location in memory of the variable passed to it
void printPointer(int& i) 
{
	int* iptr = &i;
	// The unary * operator dereferences the pointer
	std::cout << "i  = " << *iptr << endl;
	std::cout << "&i = " << iptr << endl;
}

void dataCompare(const string & type, int& one, int& two, int& three, int& four)
{
	cout << type << " moves ";
	if (&one < &two && &two < &three && &three < &four)
		cout << "in ascending order";
	else if (&one > & two&&& two > & three&&& three > & four)
		cout << "in descending order";
	else
		cout << "in an unexpected way";
	cout << " in memory." << endl;

	printPointer(one);
	printPointer(two);
	printPointer(three);
	printPointer(four);
}