/*Lab5Main.cpp
Nathan Damon
CS 202
2/4/2021
This is the main file for lab5.
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ios;


int main()
{
	int i = 0;
	int numInt = 0;
	int sum = 0;
	double average = 0.0;
	ifstream fin("data.dat", ios::binary | ios::in);
	if (!fin)
	{
		cout << "Did not open the file" << endl;
		return 0;
	}
	else
	{
		while (true)
		{
			fin.read(reinterpret_cast<char*>(&i), sizeof(i));
			if (!fin)
			{
				if (fin.eof())
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

			numInt++;
			sum += i;
		}
		average = (double)sum / (double)numInt;
	}

	cout << "Number of integers: " << numInt << endl;
	cout << "Sum: " << sum << endl;
	cout << "Average: " << average << endl;


	cout << endl;
	cout << "Program end";
	cin >> i;
}