#include "catch/catch_amalgamated.hpp"
#include "finder/finder.hpp"
#include "misc/misc.hpp"
#include <functional>
using namespace ns_finder;

TEST_CASE("File xxhash")
{
    Finder f;
    string expected = "12787885701654546906";
    hash_result result = f.calculate_xxhash("./README.md");
    REQUIRE(result.hash == expected);
}

TEST_CASE("MD5 vs xxHash")
{
    std::vector<std::string>
        files = {
            "Z:\\Binary Tree Questions for Technical Interviews - Google, Facebook, Amazon, Microsoft",
            "Z :\\Google Drive Videos\\IMG_4967.MOV",
            "Z :\\Google Drive Videos\\IMG_5359.MOV"};
    Finder finder;
    for (const string &f : files)
    {
        auto start2 = std::chrono::high_resolution_clock::now();
        auto result2 = finder.calculate_xxhash(f);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration2 = end2 - start2;
        std::cout << "XXHash Execution time: " << duration2.count() << " ms\n";
    }
}