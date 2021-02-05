/*Main.cpp
Nathan Damon
CS 202
2/4/2021
This is the Main.cpp file for the c_style_strings program.
*/

#include "c_style_strings.cpp"
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

int main()
{
	vector<const char*> wordsAndSentences= {
		"Long before Bering or Amundsen, long before Franklin or Shackleton, there was William Barents, in many ways the greatest polar explorer of them all.",
		"This is one reason that some experts believe there may have been many other big bangs, perhaps trillions and trillions of them, spread through the mighty span of eternity, and that the reason we exist in this particular one is that this is one we could exist in.",
		"Winebibber",
		"circumlocution",
		"accoutrements"
	};

	const char* string = "Happy Program";
	auto copy = strdups(string);

	cout << string << endl; // Prints the original
	cout << copy << endl; // Prints the copy
	delete copy;
	cout << endl;

	auto lettersToFind = strdups("particular");
	auto word = findx(wordsAndSentences[1], lettersToFind); // Looks for the lettersToFind
	delete lettersToFind;

	cout << word << endl; // Prints the word the was found or prints "Not present"
	delete word;

	return 0;
}