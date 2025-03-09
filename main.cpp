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

int main(int argc, char **argv)
{
    Finder fin;
    fs::path root = "D:\\TEMP_DUP_DATA";
    fin.start_search(root);

    return 0;
}
