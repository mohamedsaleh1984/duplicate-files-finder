#include "catch/catch_amalgamated.hpp"
#include "finder/finder.hpp"
#include "misc/misc.hpp"
#include <functional>
using namespace ns_finder;

TEST_CASE("File MD5 hash")
{
    Finder f;
    string expected = "d41d8cd98f00b204e9800998ecf8427e";
    hash_result result = f.calculate_md5_hash("./README.md");
    REQUIRE(result.hash == expected);
}

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
        auto start = std::chrono::high_resolution_clock::now();
        auto result = finder.calculate_md5_hash(f);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "MD5 Execution time: " << duration.count() << " ms\n";

        auto start2 = std::chrono::high_resolution_clock::now();
        auto result2 = finder.calculate_xxhash(f);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration2 = end2 - start2;
        std::cout << "XXHash Execution time: " << duration2.count() << " ms\n";
    }
}