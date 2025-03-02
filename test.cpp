#include "catch/catch_amalgamated.hpp"
#include "filehelper/fileHelper.hpp"
using namespace ns_fileHelper;

TEST_CASE("File MD5")
{
    string expected = "d41d8cd98f00b204e9800998ecf8427e";
    md5_hash_result result = FileHelper::calculate_md5_hash("test.txt");
    REQUIRE(result.md5_hash == expected);
}
