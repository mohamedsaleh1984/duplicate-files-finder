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
    // fs::path p("E:\\YouTube-Channels");
    // Finder f;
    // f.start_search(p);

    Finder f;
    string result = f.calculate_hash("./README.md");
    cout << result << endl;

    return 0;
}