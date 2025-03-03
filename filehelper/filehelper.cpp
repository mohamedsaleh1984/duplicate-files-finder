// filehelper.ccp
// author: mohamed.saleh2@snhu.edu
// date: 03/02/2025

#include "fileHelper.hpp"

using namespace ns_fileHelper;

/// @brief Calculate MD5 has for file
struct md5_hash_result FileHelper::
    calculate_md5_hash(const std::string &file_path)
{
    struct md5_hash_result res;
    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    // read file content
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open())
    {
        res.has_error = true;
        res.error_message = "Error opening file.";
        return res;
    }

    char buffer[BUFFER_SIZE];
    while (file.read(buffer, sizeof(buffer)))
    {
        MD5_Update(&md5Context, buffer, file.gcount());
    }

    if (file.fail() && !file.eof())
    {
        res.has_error = true;
        res.error_message = "Error read file.";
        return res;
    }

    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5_Final(hash, &md5Context);

    std::stringstream ss;
    for (unsigned char i : hash)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);

    if (ss.str().length() == 0)
    {
        res.has_error = true;
        res.error_message = "Error calculating MD5 hash";
        return res;
    }

    res.md5_hash = ss.str();
    return res;
}

/// @brief Printout directiorys for desired path
/// @param path
void FileHelper::print_directories(const fs::path &path)
{
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry))
        {
            std::cout << entry.path() << std::endl;
            FileHelper::print_directories(entry.path()); // Recursive call for subdirectories
        }
    }
}

/// @brief Get directories in root
/// @param root
/// @param dirsOut
void FileHelper::getDirectories(const fs::path &root, vector<fs::path> &dirsOut)
{
    for (const auto &entry : fs::directory_iterator(root))
    {
        if (fs::is_directory(entry))
        {
            dirsOut.push_back(entry.path());
            getDirectories(entry.path(), dirsOut);
        }
    }
}

/// @brief Printout file in specific dirs.
/// @param dirs
void FileHelper::print_files(vector<fs::path> &dirs)
{
    vector<fs::path> files;

    for (const auto &entry : dirs)
    {
        for (const auto &entry : fs::directory_iterator(entry))
        {
            if (fs::is_regular_file(entry))
            {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    }
}

/// @brief Return list of files in Dirs directories
/// @param dirs
/// @return
vector<fs::path> FileHelper::getFiles(vector<fs::path> &dirs)
{
    vector<fs::path> files;

    for (const auto &entry : dirs)
    {
        for (const auto &entry : fs::directory_iterator(entry))
        {
            if (fs::is_regular_file(entry))
                files.push_back(entry.path());
        }
    }
    return files;
}
