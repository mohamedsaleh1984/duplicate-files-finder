#ifndef _FINDER_H_
#define _FINDER_H_

// filehlper.hpp
// author: mohamed.saleh2@snhu.edu
// date: 03/03/2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

class Finder
{
public:
    Finder(fs::path root) : _root(root)
    {
    }
    void start_search();
    void post_search();
    void pre_search();

private:
    fs::path _root;
    map<string, vector<fs::path>> _findings;
};

#endif