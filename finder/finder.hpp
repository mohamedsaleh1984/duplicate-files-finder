#ifndef _FINDER_H_
#define _FINDER_H_

// filehlper.hpp
// author: mohamed.saleh2@snhu.edu
// date: 03/03/2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <sys/stat.h>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include "../xxhash/xxhash.h"
using namespace std;
namespace fs = std::filesystem;

namespace ns_finder
{
    const unsigned long int CHUNK_SIZE = 8192;
    const unsigned long int BUFFER_SIZE = 4096;
    /// @brief Retain error information.
    struct hash_result
    {
        // mdf hash value
        string hash;
        // error message if there has error
        string error_message;
        // error indicator
        bool has_error = false;
    };

    class Finder
    {
    private:
        int total_files();
        unsigned long long total_files_size();
        unsigned long int total_duplicate_files_count();
        unsigned long long total_duplicate_files_size();
        void delete_duplicate_files();
        void post_search();
        void pre_search();
        std::string bytesToSize(unsigned long long bytes);

    public:
        Finder();
        /// @brief Search
        /// @param root
        void start_search(fs::path root);

        /// @brief Get directories in root
        /// @param root
        /// @param dirsOut
        void getDirectories(const fs::path &root, vector<fs::path> &dirsOut);

        /// @brief Return list of files in Dirs directories
        /// @param dirs
        /// @return
        vector<fs::path> getFiles(vector<fs::path> &dirs);

        struct hash_result calculate_xxhash(const std::string &file_path);

    private:
        fs::path _root;
        vector<fs::path> _files;
        map<string, vector<fs::path>> _findings;
    };
}

#endif