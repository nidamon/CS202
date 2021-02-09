/*Tests.cpp
Nathan Damon
CS 202
2/9/2021
This is the file that will contain the tests for Lab 6
*/

#include "catch.hpp"

unsigned int factorial(unsigned int number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
};
