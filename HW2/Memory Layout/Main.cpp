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
	static int static1 = 1;
	static int static2 = 12;
	static int static3 = 3;
	static int static4 = 14;
	dataCompare("Static", static1, static2, static3, static4);

	// Looking at the stack storage
	int stack1 = 5;
	int stack2 = 16;
	int stack3 = 7;
	int stack4 = 18;
	dataCompare("Stack", stack1, stack2, stack3, stack4);

	// Looking at the free store / heap
	auto freeStore1 = new int(9);
	auto freeStore2 = new int(110);
	auto freeStore3 = new int(11);
	auto freeStore4 = new int(112);
	dataCompare("Free store / heap", *freeStore1, *freeStore2, *freeStore3, *freeStore4);
	delete freeStore1;
	delete freeStore2;
	delete freeStore3;
	delete freeStore4;

	// Looking at the free store / heap making an array
	auto freeStoreArray = new int[4]{ 13 , 114, 15, 116 };
	dataCompare("Free store / heap", freeStoreArray[0], freeStoreArray[1], freeStoreArray[2], freeStoreArray[3]);
	delete[] freeStoreArray;


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
	cout << endl;
}