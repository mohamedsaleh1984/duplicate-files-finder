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
    Finder f;
    fs::path f1 = "./test.cpp";
    fs::path f2 = "./test copy.cpp";

    std::cout << "Hash of path '" << f1 << "': "
              << std::hex << std::uppercase << std::setw(16)
              << fs::hash_value(f1) << std::endl;

    std::cout << "Hash of path '" << f2 << "': "
              << std::hex << std::uppercase << std::setw(16)
              << fs::hash_value(f2) << std::endl;
    // cout << f.calculate_hash(f1.generic_string()) << endl;
    // cout << f.calculate_hash(f2.generic_string()) << endl;

    // fs::path p("Z:\\z");
    // f.start_search(p);

    return 0;
}