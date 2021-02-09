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
