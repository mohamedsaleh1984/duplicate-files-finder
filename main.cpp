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
#define RELEASE

int main(int argc, char **argv)
{
#ifdef DEBUG
    Finder fin;
    fs::path root = "D:\\____c";
    fin.start_search(root);
#endif

#ifdef RELEASE
    bool bfetch = true;

    while (bfetch)
    {
        if (argc == 2)
        {
            bfetch = false;
            string programName = argv[0];
            string location = argv[1];

            Finder fin;
            fs::path root = argv[1];
            fin.start_search(root);
        }
        else
        {
            std::cerr << "Usage: ./main.exe dir_location\n";
            bfetch = false;
        }
    }
#endif

    return 0;
}
