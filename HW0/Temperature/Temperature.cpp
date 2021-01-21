/*Temperature.cpp
Nathan Damon
CS 202
1/20/2021
This program will convert temperature from degrees Fahrenheit to degrees Celsius.
*/

#include <string>
using std::string;
#include <iostream>

double cpp_ftoc(const char* str);
double c_ctof(const char* str);

int main(int argc, const char** argv)
{
	if (argc >= 2 && argv[1] == string("--ftoc"))
	{
		double c = cpp_ftoc(argv[2]);
		printf("In degrees Celcius %f.\n", c);
	}

	if (argc >= 2 && argv[1] == string("--ctof"))
	{
		double f = c_ctof(argv[2]);
		printf("In degrees Fahrenheit %f.\n", f);
	}
}


// Converts from degrees Fahrenheit to degrees Celsius (stod)
double cpp_ftoc(const char* str)
{
	double celcius = (std::stod(str) - 32) * (5/9);
	return celcius;
}

// Converts from degrees Celsius to degrees Fahrenheit (strtod)
double c_ctof(const char* str)
{
	double fahrenheit = strtod(str, NULL) * (9/5) + 32;
	return fahrenheit;
}