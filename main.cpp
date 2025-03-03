#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <functional>
#include <climits>
#include <algorithm>
#include <cassert>
#include "misc/misc.hpp"
#include "finder/finder.hpp"
#include "xxhash/xxhash.h"

using namespace std;
using namespace ns_finder;
#define CHUNK_SIZE 8192

string file_path = "../TEST_FILE_DELETE_AFTER_500MB-CZIPtestfile.org.zip";

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
    auto r1 = measureExecutionTime(hash_file);
    cout << "Time taken for hash_file " << r1.second.count() << " nanoseconds - Md5" << endl;
    auto r2 = measureExecutionTime(hash_file_md5);
    cout << "Time taken for hash_file " << r2.second.count() << " nanoseconds - xxHash" << endl;
    
    return 0;
}

void temp()
{
    // Finder f;

    // struct md5_hash_result result = f.calculate_md5_hash(file_path);
    // if (result.has_error)
    // {
    //     cout << result.error_message << endl;
    // }
    // else
    // {
    //     cout << result.md5_hash << endl;
    // }

    // string shash = hash_file(file_path);
    // cout << shash << endl;
}
