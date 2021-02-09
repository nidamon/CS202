/*Ball.h
Nathan Damon
CS 202
2/9/2021
This is the header file the ball class
*/

#ifndef BALL_HPP
#define BALL_HPP


#include <string>
using std::string;

class Ball // Because we are going to "catch" it
{
public:
	Ball();
	Ball(const string name, const string mainColor, const string secondaryColor, const string highlightColor,
		const double radiusCm, const double weightKg, const double priceUsd, const double HMO);

	string _name;
	string _mainColor;
	string _secondaryColor;
	string _highlightColor;

	double _radiusCm;
	double _weightKg;
	double _priceUsd;
	double _HMO; // How Much Ouch

};

#endif
