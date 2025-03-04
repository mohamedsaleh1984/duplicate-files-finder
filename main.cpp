#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <functional>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include "misc/misc.hpp"
#include "finder/finder.hpp"
#include "xxhash/xxhash.h"

using namespace std;
using namespace ns_finder;
#define CHUNK_SIZE 8192

string file_path = "../CS330Content.zip";

// string file_path = "/home/moe/Videos/Fight-Club.mp4";

/*
Fight-Club.mp4 = 1.6 GB
Time taken for hash_file 1442163047 nanoseconds - Md5
Time taken for hash_file 5467367895 nanoseconds - xxHash

TEST_FILE_DELETE_AFTER_500MB-CZIPtestfile.org.zip = 534 MB
Time taken for hash_file 268907650 nanoseconds - Md5
Time taken for hash_file 1947042984 nanoseconds - xxHash

CS330Content.zip = 34.3 MB
Time taken for hash_file 55736638 nanoseconds - Md5
Time taken for hash_file 130292498 nanoseconds - xxHash
 */

string hash_file()
{
    const char *p = file_path.c_str();
    FILE *file = fopen(p, "rb");
    if (!file)
    {
        perror("Failed to open file");
        exit(1);
    }

    XXH64_state_t *state = XXH64_createState();
    XXH64_reset(state, 0); // Seed = 0

    unsigned char buffer[CHUNK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0)
    {
        XXH64_update(state, buffer, bytes_read);
    }

    fclose(file);
    XXH64_hash_t hash = XXH64_digest(state);
    XXH64_freeState(state);

    return to_string(hash);
}

string hash_file_md5()
{
    Finder f;
    struct md5_hash_result result = f.calculate_md5_hash(file_path);
    return result.md5_hash;
}

int main(int argc, char **argv)
{
    std::vector<std::string> files = {
        "Z:\\Binary Tree Questions for Technical Interviews - Google, Facebook, Amazon, Microsoft",
        "Z :\\Google Drive Videos\\IMG_4967.MOV",
        "Z :\\Google Drive Videos\\IMG_5359.MOV",
    };

    for (auto f : files)
    {
        file_path = f;
        auto r1 = measureExecutionTime(hash_file_md5);
        cout << "Time taken for hash_file " << r1.second.count() << " nanoseconds - Md5" << endl;
        auto r2 = measureExecutionTime(hash_file);
        cout << "Time taken for hash_file " << r2.second.count() << " nanoseconds - xxHash" << endl;
    }

    return 0;
}
