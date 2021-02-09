/*Tests.cpp
Nathan Damon
CS 202
2/9/2021
This is the file that will contain the tests for Lab 6
*/

#include "catch.hpp"
#include "Vector3f.h"

bool operator==(const Vector3f& a, const Vector3f& b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
bool operator!=(const Vector3f& a, const Vector3f& b) { return (a.x != b.x) || (a.y != b.y) || (a.z != b.z); }



TEST_CASE("Vector3f default constructor test", "[Vector3f]") {
	Vector3f a;
	REQUIRE(a.x == 0.0f);
	REQUIRE(a.y == 0.0f);
	REQUIRE(a.z == 0.0f);
}

float tester1 = 12.3f;
float tester2 = 54.259f;
float tester3 = 4.332f;

TEST_CASE("Vector3f user input constructor test", "[Vector3f]") {
	Vector3f b(tester1, tester2, tester3);
	REQUIRE(b.x == tester1);
	REQUIRE(b.y == tester2);
	REQUIRE(b.z == tester3);
}

TEST_CASE("Vector3f copy constructor test", "[Vector3f]") {
	Vector3f b(tester1, tester2, tester3);
	Vector3f c(b);
	REQUIRE(c == b);
}

TEST_CASE("Operator test equality", "[Operator]") {
	REQUIRE(Vector3f(tester3, tester1, tester2) == Vector3f(tester3, tester1, tester2));
}

TEST_CASE("Operator test inequality", "[Operator]") {
	REQUIRE(Vector3f(tester3, tester3, tester3) != Vector3f(tester1, tester1, tester1));
}