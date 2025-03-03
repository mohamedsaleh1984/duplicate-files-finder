#include "catch/catch_amalgamated.hpp"
#include "finder/finder.hpp"
using namespace ns_finder;

TEST_CASE("File MD5")
{
    string expected = "d41d8cd98f00b204e9800998ecf8427e";
    Finder f;
    string result = f.calculate_hash("./README.md");
    REQUIRE(result == expected);
}
