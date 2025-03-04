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
#include <sys/stat.h>
#include <stdexcept>
#include <thread>
#include <chrono>
using namespace std;
namespace fs = std::filesystem;

namespace ns_finder
{
    class Finder
    {
    public:
        Finder();
        void start_search(fs::path root);
        void post_search();
        void pre_search();
        /// @brief Calculate MD5 has for file
        string calculate_hash(const std::string &file_path);
        /// @brief Printout directiorys for desired path
        /// @param path
        void print_directories(const fs::path &path);

        /// @brief Get directories in root
        /// @param root
        /// @param dirsOut
        void getDirectories(const fs::path &root, vector<fs::path> &dirsOut);

        /// @brief Printout file in specific dirs.
        /// @param dirs
        void print_files(vector<fs::path> &dirs);

        /// @brief Return list of files in Dirs directories
        /// @param dirs
        /// @return
        void getFiles(vector<fs::path> &dirs);

    private:
        fs::path _root;
        vector<fs::path> _files;
        map<string, vector<fs::path>> _findings;
        bool _searchStarted;
    };
}

#endif