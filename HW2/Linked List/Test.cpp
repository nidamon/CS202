/*Test.cpp
Nathan Damon
CS 202
2/9/2021
This is the file that will contain the tests for Linked List
*/

#include "../../Labs/CS202Lab6Catch2/catch.hpp"
#include "Ball.h"
#include <list>
#include <random>
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

Ball getRandomBall(std::mt19937& gen);

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

// Test getRandomBall
TEST_CASE("get Random Ball test", "[Ball]") {
	std::random_device r;
	std::mt19937 gen(r());

	Ball one = getRandomBall(gen);
	cout << one._name << endl;
	cout << one._mainColor << endl;
	cout << one._secondaryColor << endl;
	cout << one._highlightColor << endl;
	cout << one._radiusCm << endl;
	cout << one._weightKg << endl;
	cout << one._priceUsd << endl;
	cout << one._HMO << endl;
	cout << endl;

	Ball two = getRandomBall(gen);
	cout << two._name << endl;
	cout << two._mainColor << endl;
	cout << two._secondaryColor << endl;
	cout << two._highlightColor << endl;
	cout << two._radiusCm << endl;
	cout << two._weightKg << endl;
	cout << two._priceUsd << endl;
	cout << two._HMO << endl;
}













// Returns a random ball
Ball getRandomBall(std::mt19937& gen)
{
	// For the types of the ball pitch
	vector<string> names = { "Changeup", "Curveball", "Cutter", "Eephus", "Forkball", "Four-Seam Fastball", "Knuckleball", "Knuckle-curve", "Screwball", "Sinker", "Slider", "Splitter", "Two-Seam Fastball" };
	std::uniform_int_distribution<> nameDis(0, names.size() - 1);

	// Color selection of primary, secondary, tertiary, and 4 metals: gold, silver, copper, bronze
	vector<string> colors = { "Red", "Blue", "Yellow", "Purple", "Green", "Orange", "Red-Purple", "Blue-Purple", "Blue-Green", "Yellow-Green", "Red-Orange", "Yellow-Orange", "Gold", "Silver", "Copper", "Bronze" };
	std::uniform_int_distribution<> colorDis(0, names.size() - 1);

	std::uniform_int_distribution<> radiusDis(100, 1000); // Radius range
	std::uniform_int_distribution<> weightDis(10, 1000); // Weight range
	std::uniform_int_distribution<> priceDis(50, 10000); // Price range
	std::uniform_int_distribution<> HMODis(1, 100); // Pain range
	
	return Ball(names[nameDis(gen)], colors[colorDis(gen)], colors[colorDis(gen)], colors[colorDis(gen)], radiusDis(gen) / 100.0, weightDis(gen) / 100.0, priceDis(gen) / 100.0, HMODis(gen) / 10.0);
}
