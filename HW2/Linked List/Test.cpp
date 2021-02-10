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
#include <iomanip>
using std::setw;
using std::left;
using std::right;

bool operator==(const Ball& a, const Ball& b) {
	return (a._name == b._name) && (a._mainColor == b._mainColor) && (a._secondaryColor == b._secondaryColor)
		&& (a._highlightColor == b._highlightColor) && (a._radiusCm == b._radiusCm) && (a._weightKg == b._weightKg)
		&& (a._priceUsd == b._priceUsd) && (a._HMO == b._HMO);
}

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

// Test Queue: First-in First-out
TEST_CASE("Queue: First-in First-out", "[Queue]") {
	std::random_device r;
	std::mt19937 gen(r());

	// Create three random Balls
	Ball first = getRandomBall(gen);
	Ball second = getRandomBall(gen);
	Ball third = getRandomBall(gen);

	// Put the three balls in the list
	std::list<Ball> queue = { first, second, third };
	Ball originalLastBall = third;

	// This should push 2 new Balls into the queue while removing the first and second balls
	for (int i = 0; i < 2; i++)
	{
		Ball newball = getRandomBall(gen);
		// Push newball to the back of the queue
		queue.push_back(newball);
		REQUIRE(queue.back() == newball); // Test the push_back

		REQUIRE(queue.front() == first); // Check the front
		queue.pop_front();
		REQUIRE(queue.front() == second); // Test the pop_front
		REQUIRE(queue.back() == newball); // Check that the back is the same

		// Shift each ball to the appropriate variable and run again
		first = second;
		second = third;
		third = newball;
	}
	REQUIRE(queue.front() == originalLastBall); // Check that the first ball is now the original last ball
}

// Test Stack: Last-in First-out
TEST_CASE("Stack: Last-in First-out", "[Stack]") {
	std::random_device r;
	std::mt19937 gen(r());

	// Create three random Balls
	Ball first = getRandomBall(gen);
	Ball second = getRandomBall(gen);
	Ball third = getRandomBall(gen);

	// Put the three balls in the list
	std::list<Ball> stack = { first, second, third };

	// This should push 8 new Balls onto the stack
	for (int i = 0; i < 8; i++)
	{
		Ball newball = getRandomBall(gen);
		// Push newball onto the stack
		stack.push_back(newball);
		REQUIRE(stack.back() == newball); // Test the push_back
	}
	REQUIRE(stack.front() == first); // Check that the front is the same

	// This should pop 10 Balls off the stack
	for (int i = 0; i < 10; i++)
		stack.pop_back();

	REQUIRE(stack.back() == first); // Test the pop_back, we should now be looking at the first ball
	REQUIRE(stack.back() == stack.front()); // Check that the first and last item is the same as it should be at this point
}

// Test Insert and Find
TEST_CASE("Insert and Find", "[Insert and Find]") {
	std::random_device r;
	std::mt19937 gen(r());

	// Fill the list with several balls
	std::list<Ball> listing = { getRandomBall(gen), getRandomBall(gen), getRandomBall(gen),getRandomBall(gen), getRandomBall(gen), getRandomBall(gen), getRandomBall(gen), getRandomBall(gen), getRandomBall(gen) };

	for (const auto &i : listing)
	{
		cout << left << setw(20) << i._name
			<< "$" << setw(9) << i._priceUsd << setw(4)
			<< i._radiusCm << setw(6) << "cm"
			<< setw(5) << i._weightKg << setw(5) << "kg"
			<< setw(4) << i._HMO << "Ouch LVL" << endl;
	}

	// Custom sorting
	listing.sort([](const Ball& a, const Ball& b) {
		if (a._priceUsd != b._priceUsd)
			return a._priceUsd < b._priceUsd;
		if (a._radiusCm != b._radiusCm)
			return a._radiusCm < b._radiusCm;
		if (a._weightKg != b._weightKg)
			return a._weightKg < b._weightKg;
		if (a._HMO != b._HMO)
			return a._HMO < b._HMO;
		return a._HMO < b._HMO;
	});

	cout << endl;
	for (const auto& i : listing)
	{
		cout << left << setw(20) << i._name 
			<< "$" << setw(9) << i._priceUsd << setw(4) 
			<< i._radiusCm << setw(6) << "cm" 
			<< setw(5) << i._weightKg << setw(5) << "kg" 
			<< setw(4) << i._HMO << "Ouch LVL" << endl;
	}









	//// This should push 8 new Balls onto the stack
	//for (int i = 0; i < 8; i++)
	//{
	//	Ball newball = getRandomBall(gen);
	//	// Push newball onto the stack
	//	stack.push_back(newball);
	//	REQUIRE(stack.back() == newball); // Test the push_back
	//}
	//REQUIRE(stack.front() == first); // Check that the front is the same

	//// This should pop 10 Balls off the stack
	//for (int i = 0; i < 10; i++)
	//	stack.pop_back();

	//REQUIRE(stack.back() == first); // Test the pop_back, we should now be looking at the first ball
	//REQUIRE(stack.back() == stack.front()); // Check that the first and last item is the same as it should be at this point

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
