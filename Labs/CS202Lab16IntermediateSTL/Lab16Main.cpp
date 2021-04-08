/*Lab16Main.cpp
Nathan Damon
CS 202
4/8/2021
This is the main file for lab 16
*/

#include <algorithm>
#include <vector>
using std::vector;
#include <random>
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <iterator>

struct v3 {
	int x = 0;
	int y = 0;
	int z = 0;

	friend bool operator==(const v3& a, const v3& b) {
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
};

int main()
{
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<int> dis(0, 100);

	vector<v3> vec(15);

	std::generate(begin(vec), end(vec),
		[gen, dis]() mutable {
			return v3{ dis(gen), dis(gen), 0 };
		});

	for (const auto& i : vec)
	{
		cout << setw(2) << i.x << ", "
			<< setw(2) << i.y << ", "
			<< setw(2) << i.z << " " << endl;
	}

	cout << endl;
	cout << "Sampled vector:" << endl;

	for (int i = 0; i < 10; i++)
	{
		vector<v3> vecSample;
		std::sample(begin(vec), end(vec), std::back_inserter(vecSample), 4, gen);

		for (auto& i : vecSample)
		{
			cout << setw(2) << i.x << ", "
				<< setw(2) << i.y << ", "
				<< setw(2) << i.z << " " << endl;

			v3 temp = i;
			temp.z++;
			std::replace(vec.begin(), vec.end(), i, temp);
		}
	}

	cout << endl;
	cout << "Vector with sampled counts:" << endl;

	for (const auto& i : vec)
	{
		cout << setw(2) << i.x << ", "
			<< setw(2) << i.y << ", "
			<< setw(2) << i.z << " " << endl;
	}

	return 0;
}