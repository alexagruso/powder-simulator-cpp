#include <catch2/catch_test_macros.hpp>

uint factorial(uint value)
{
    if (value <= 1)
        return 1;

    return value * factorial(value - 1);
}

TEST_CASE("Test Success")
{
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(4) == 24);
}

TEST_CASE("Test Fail")
{
    REQUIRE(factorial(5) == 100);
}
