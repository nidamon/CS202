/*Test.cpp
Nathan Damon
CS 202
2/9/2021
This is the file that will contain the tests for Linked List
*/

#include "../../Labs/CS202Lab6Catch2/catch.hpp"
#include <list>
#include "Ball.h"

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


