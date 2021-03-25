/*Lab10Main.cpp
Nathan Damon
CS 202
3/18/2021
This is the main file for lab 10
*/

#include "Lab2Class.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>

void functionC() {
    //your code here
    throw std::runtime_error{ "functionC() threw std::runtime_error" };
}

void functionB() {
    // your code here
    Lab2 lab("Physics 212");
    cout << "Starting functionB()" << endl;
    functionC();
    cout << "Ending functionB()" << endl;
}

void functionA() {
    try {
        functionB();
    }
    // your code here
    catch (const std::exception & e) {
        cout << "Caught an exception: " << e.what() << endl;
    }
    // your code here
}
int main() {
    cout << "Starting main()" << endl;
    functionA();
    cout << "Ended normally." << endl;

    cout << endl;
    try {
        std::vector<Lab2> lab2Vector(10);
    }
    catch (const std::exception & e) {
        cout << "Caught an exception: " << e.what() << endl;
    }
    return 0;
}