#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "misc/misc.hpp"
#include "finder/finder.hpp"

using namespace std;
using namespace ns_finder;

int main()
{
    fs::path p("E:\\YouTube-Channels");
    Finder f;
    f.start_search(p);

    return 0;
}