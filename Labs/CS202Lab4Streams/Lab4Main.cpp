/*Lab4Main.cpp
Nathan Damon
CS 202
2/2/2021
This is the main file for lab4.
*/


#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
using std::getline;
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::ios;



int main()
{
	ifstream fileInput("FileToRead.txt");
	if (!fileInput)
	{
		cout << "Did not open the file" << endl;
		return 0;
	}
	else
	{
		while (true)
		{
			string line;
			getline(fileInput, line);
			if (!fileInput)
			{
				if (fileInput.eof())
				{
					cout << "End of file." << endl;
					break;
				}
				else
				{
					cout << "Error reading file." << endl;
					break;
				}
			}
			else
				cout << line << endl;
		}
	}

	string str;
	int n;
	cout << endl;
	while (true)
	{
		cout << "Enter a number n and then a line of text to be appended into the file n times: ";
		getline(cin, str);
		istringstream instream(str);
		instream >> n;
		if (instream)
			if (n > -1)
				if (n < 10) // Don't want to add too many copies
					break;
		cout << "You need to enter an integer 1-10." << endl;
	}

	ofstream fileOutput("FileToRead.txt", ios::app);
	if (!fileOutput)
	{
		cout << "Error opening file" << endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			fileOutput << str << endl;
		}
	}

	cout << "Program end";
	cin >> n;
}