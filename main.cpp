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

string file_path = "";

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
    struct hash_result result = f.calculate_md5_hash(file_path);
    return result.hash;
}

int main(int argc, char **argv)
{

    return 0;
}
