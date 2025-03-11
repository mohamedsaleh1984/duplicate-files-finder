#ifndef _FINDER_H_
#define _FINDER_H_

// finder.hpp
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
    const bool DEBUG_MODE = true;
    const unsigned long int CHUNK_SIZE = 8192;

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
        void export_duplicate_files();
        string shorten_file_name(string fileNameWOExt);
        void printout_stat();
        int milliseconds_to_hours(unsigned long long milliseconds);
        int milliseconds_to_minutes(unsigned long long milliseconds);

    public:
        Finder();
        void start_search(fs::path root);
        void getDirectories(const fs::path &root, vector<fs::path> &dirsOut);
        vector<fs::path> getFiles(vector<fs::path> &dirs);
        struct hash_result calculate_xxhash(const std::string &file_path);

    private:
        fs::path _root;
        vector<fs::path> _files;
        map<string, vector<fs::path>> _findings;
    };
}

#endif