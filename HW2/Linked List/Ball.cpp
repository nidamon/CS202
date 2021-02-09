/*Ball.cpp
Nathan Damon
CS 202
2/9/2021
This is the header file the ball class
*/

#include "Ball.h"

// Default Constructor
Ball::Ball()
	: _name{ "Default" },
	_mainColor{ "Red" },
	_secondaryColor{ "Blue" },
	_highlightColor{ "Yellow" },
	_radiusCm{ 3.2 },
	_weightKg{ 0.142 },
	_priceUsd{ 3.00 },
	_HMO{ 2.3 }
{}

// Parameter specification constructor
Ball::Ball(const string name, const string mainColor, const string secondaryColor, const string highlightColor,
	const double radiusCm, const double weightKg, const double priceUsd, const double HMO)
	: _name{ name },
	_mainColor{ mainColor },
	_secondaryColor{ secondaryColor },
	_highlightColor{ highlightColor },
	_radiusCm{ radiusCm },
	_weightKg{ weightKg },
	_priceUsd{ priceUsd },
	_HMO{ HMO }
{}