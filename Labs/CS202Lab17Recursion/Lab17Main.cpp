/*Lab17Main.cpp
Nathan Damon
CS 202
4/15/2021
This is the main file for lab 17
*/

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

template <typename Iterator>
void printReversed(Iterator theBegin, Iterator theEnd) {
    if (theEnd == theBegin)
        return;
    theEnd--;
    cout << *theEnd << " ";
    printReversed(theBegin, theEnd);
}

int main() {
    string s("Hello World!");
    printReversed(begin(s), end(s));
    cout << "\n";
    vector<int> primes{ 2,3,5,7,11,13,17 };
    printReversed(begin(primes), end(primes));
    cout << "\n";
    return 0;
}