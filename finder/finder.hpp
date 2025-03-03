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
    const unsigned long int BUFFER_SIZE = 4096;
    /// @brief Retain error information.
    struct md5_hash_result
    {
        // mdf hash value
        string md5_hash;
        // error message if there has error
        string error_message;
        // error indicator
        bool has_error = false;
    };

    class Finder
    {
    public:
        Finder();
        void start_search(fs::path root);
        void post_search();
        void pre_search();
        /// @brief Calculate MD5 has for file
        struct md5_hash_result calculate_md5_hash(const std::string &file_path);
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
        vector<fs::path> getFiles(vector<fs::path> &dirs);

    private:
        fs::path _root;
        vector<fs::path> _files;
        map<string, vector<fs::path>> _findings;
    };
}

#endif