/*Test.cpp
Nathan Damon
CS 202
2/9/2021
This is the file that will contain the tests for Linked List
*/

#include "../../Labs/CS202Lab6Catch2/catch.hpp"
#include <list>
#include "Ball.h"

// Test default constructor
TEST_CASE("Ball default constructor test", "[Ball]") {
	Ball one;
	REQUIRE(one._name == "Default");
	REQUIRE(one._mainColor == "Red");
	REQUIRE(one._secondaryColor == "Blue");
	REQUIRE(one._highlightColor == "Yellow");
	REQUIRE(one._radiusCm == 3.2);
	REQUIRE(one._weightKg == 0.142);
	REQUIRE(one._priceUsd == 3.0);
	REQUIRE(one._HMO == 2.3);
}

// Test parameter input constructor
TEST_CASE("Ball user specified constructor test", "[Ball]") {
	Ball one("Fast Ball", "Yellow", "Pink", "Green", 5.13, 0.098, 5.99, 6.4);
	REQUIRE(one._name == "Fast Ball");
	REQUIRE(one._mainColor == "Yellow");
	REQUIRE(one._secondaryColor == "Pink");
	REQUIRE(one._highlightColor == "Green");
	REQUIRE(one._radiusCm == 5.13);
	REQUIRE(one._weightKg == 0.098);
	REQUIRE(one._priceUsd == 5.99);
	REQUIRE(one._HMO == 6.4);
}
