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
#include <iomanip>
#include <random>
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

    struct search_result
    {
        vector<fs::path> files;
        map<string, vector<fs::path>> findings;
        int last_processed_index;
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
        string write_temp_file(fs::path file_path);
        string generate_guid_pseudorandom();
        string generate_hash_big_files(fs::path file_path);

    public:
        Finder();
        void start_search(fs::path root);
        void getDirectories(const fs::path &root, vector<fs::path> &dirsOut);
        vector<fs::path> getFiles(vector<fs::path> &dirs);
        struct hash_result calculate_xxhash(const std::string file_path);
        bool write_search_results();
        void set_last_processed_file_index(int index);
        int get_last_processed_file_index();
        struct search_result read_search_result(string outfile);

    private:
        fs::path _root;
        vector<fs::path> _files;
        map<string, vector<fs::path>> _findings;
        int _last_proc_index;
    };
}

#endif