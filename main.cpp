/*
    Copyright © 2025 Mohamed Saleh. All Rights Reserved.

    This software and its source code are the exclusive property of Mohamed Saleh.
    Unauthorized copying, modification, distribution, or use of this software,
    in whole or in part, is strictly prohibited.

    For licensing inquiries, please contact mohamedsaleh1984@hotmail.com.

*/

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
#include "finder/finder.hpp"
#include "xxhash/xxhash.h"
using namespace std;
using namespace ns_finder;

int main(int argc, char **argv)
{
    if (ns_finder::DEBUG_MODE)
    {
        Finder fin;
        fs::path root = "D:\\Personal";
        fin.start_search(root);
    }

    if (!ns_finder::DEBUG_MODE)
    {
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
    }

    return 0;
}
