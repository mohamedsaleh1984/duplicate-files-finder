#ifndef __FILE_HELPER__
#define __FILE_HELPER__

// filehlper.hpp
// author: mohamed.saleh2@snhu.edu
// date: 03/02/2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include <filesystem>
#include <vector>
#include <string>
using namespace std;
namespace fs = std::filesystem;

namespace ns_fileHelper
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

    /// @brief Helper class to perform basic functions on files, directories
    class FileHelper
    {
    public:
        /// @brief Calculate MD5 has for file
        static struct md5_hash_result calculate_md5_hash(const std::string &file_path);
        /// @brief Printout directiorys for desired path
        /// @param path
        static void print_directories(const fs::path &path);

        /// @brief Get directories in root
        /// @param root
        /// @param dirsOut
        static void getDirectories(const fs::path &root, vector<fs::path> &dirsOut);

        /// @brief Printout file in specific dirs.
        /// @param dirs
        static void print_files(vector<fs::path> &dirs);

        /// @brief Return list of files in Dirs directories
        /// @param dirs
        /// @return
        static vector<fs::path> getFiles(vector<fs::path> &dirs);
    };
}

#endif